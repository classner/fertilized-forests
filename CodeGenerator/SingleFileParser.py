# Authors: Philipp Harzig, Christoph Lassner.
from TemplateParameterParser import *
from WrappedMethodCreator import *
from helper_classes import FertilizedClass, InstantiationTypes, RstDocProvider
import CppHeaderParser
import sys
import os
from DoxygenTypeExtractor import DoxygenTypeExtractor

class SingleFileParser(object):
    r"""
    Parses a cpp header file containng a fetilized class and wraps it into
    intermediate objects which can be used to automatically generate code for
    matlab wrapper classes etc.
    """
    def __init__(self, filename, package):
        self.Package = package
        self.Filename = filename
        try:
            CppHeaderParser.ignoreSymbols.append("BOOST_SERIALIZATION_SPLIT_MEMBER()")
            CppHeaderParser.ignoreSymbols.append("VIRTUAL()")
            self.CppHeader = CppHeaderParser.CppHeader(filename)
        except CppHeaderParser.CppParseError as e:
            print(e)
            sys.exit(1)

    def ParseToIntermediateObject(self):
        print("[started  parsing] " + self.Filename)
        classes = []
        functions = []
        for clsName in self.CppHeader.classes.keys():
            if clsName.startswith('_'):
              continue
            cls = self.CppHeader.classes[clsName]
            intermediateObject = self.ParseClass(cls)
            if not intermediateObject is None:
              classes.append(intermediateObject)
        for func in self.CppHeader.functions:
            intermediateObject = self.ParseFunction(func)
            functions.append(intermediateObject)
        included_obj_strings = []
        for include_stmt in self.CppHeader.includes:
          if not include_stmt.startswith('".') or \
             include_stmt[include_stmt.rindex("/")+1] == '_':
            continue
          if include_stmt.endswith('global.h"') or \
             include_stmt.endswith('util.h"') or \
             include_stmt.endswith('ndarray.h"') or \
             include_stmt.endswith('types.h"') or \
             include_stmt.endswith('serialization.h"') or \
             include_stmt.endswith('gil.hpp"') or \
             include_stmt.endswith('fertilized_fwd.h"') or \
             include_stmt.endswith('sampling.h"') or \
             include_stmt.endswith('mat.h"') or \
             include_stmt.endswith('checks.h"') or \
             include_stmt.endswith('exponentials.h"') or \
             include_stmt.endswith('argsort.h"') or \
             include_stmt.endswith('feature_value_selection.h"') or \
             include_stmt.endswith('default_values.h"'):
            continue
          included_obj_strings.append(include_stmt[include_stmt.rindex("/")+1:-3])
        using_rel_str = []
        for obj_str in included_obj_strings:
          for cls in classes:
            using_rel_str.append((cls.ClassName.lower(), obj_str))
        return classes, functions, using_rel_str

    def ParseClass(self, cls):
        # get class constructor for the standard get method
        constructors = [m for m in cls["methods"]["public"] if m["constructor"] == True]
        other_methods = [m for m in cls["methods"]["public"] if m["constructor"] != True]
        wrappedMethods = []

        # Parse inheritance.
        # CPPHeaderParser fails sometimes to parse correctly, so jump in.
        inherits = None
        if len(cls['inherits']) > 0:
          with open(self.Filename, 'r') as def_file:
            lines = [line for line in def_file]
          inheritstr = ''
          linenr = cls['line_number']-1
          while not ':' in lines[linenr]:
            linenr += 1
          fromstart = lines[linenr].index(":")
          lines[linenr] = lines[linenr][fromstart+1:]
          while lines[linenr].strip() == '':
            linenr += 1
          if lines[linenr].strip().startswith("public"):
            lines[linenr] = lines[linenr][lines[linenr].index("public")+7:]
            completed = False
            while linenr < len(lines) and not completed:
              if "public " in lines[linenr]:
                raise Exception("Multiple inheritance not supported.")
              if "{" in lines[linenr]:
                endpos = lines[linenr].index("{")
                completed = True
              else:
                endpos = len(lines[linenr])
              inheritstr += lines[linenr][:endpos]
              linenr += 1
            inherits = inheritstr
        # extract types from doxygen comment
        dte = DoxygenTypeExtractor(cls.get("doxygen"))
        availableIn, types, soilUsage = dte.Extract()
        if types == None:
            print("[WARNING]    no type comment for class " +  cls["name"])
        # get classes template params
        classDefLineNumber = cls["line_number"]
        tpp = TemplateParameterParser(self.Filename, classDefLineNumber)
        # Determine whether split_member is used.
        used_split_member = False
        with open(self.Filename, 'r') as f:
          for line in f:
            if 'BOOST_SERIALIZATION_SPLIT_MEMBER()' in line:
              used_split_member = True
              break
        typenames, templateParamStr = tpp.RetrieveTemplateParameters()
        parsed_constructors = []
        for constructor in constructors:
            constructorParams = constructor["parameters"]
            # Retrieve parameters of the constructor and wrap them into the intermediate structure

            # change signature of constructor method in c api
            # if more than one constructor is available,
            # because c doesn't support overloading of methods
            nameFormat = "{0}{1}"

            dne = DoxygenTypeExtractor(constructor.get("doxygen"))
            methodAvailableIn, exportedName = dne.ExtractExportedName()

            if not exportedName == None:
                nameFormat = exportedName + "{1}"

            wmc = WrappedMethodCreator(constructor,
                                       "get",
                                       nameFormat,
                                       types,
                                       "get_method.jinja",
                                       methodAvailableIn,
                                       self.Filename)
            method = wmc.CreateWrappedMethod(typenames, cls)
            method.ExportedName = exportedName
            method.IsConstructor = True
            wrappedMethods.append(method)
            parsed_constructors.append(method)
        # This is more reliable for this library than the CppHeaderParser ["abstract"]
        isAbstract = cls["name"].startswith('I') and \
                     cls["name"][1].upper() == cls["name"][1]
        for method in other_methods:
            if '~' in method['debug']:
              # Destructor
              continue
            wrappedMethods.append(self.ParseFunction(method, typenames, cls, isAbstract, used_split_member))
        if wrappedMethods.count == 0 or wrappedMethods == [] and not isAbstract:
            print("[WARNING]    no constructor found for class " +  cls["name"])
            return None
        cppdoc = cls['doxygen'] if cls.has_key('doxygen') else ''
        wrappedClass = FertilizedClass(CppType(cls["name"], True, typenames),
                                        types,
                                        wrappedMethods,
                                        self.Package,
                                        specialConstructor = None,
                                        dummyClass = False,
                                        isAbstract=isAbstract,
                                        declarationMethod=cls["declaration_method"],
                                        templatingString=templateParamStr,
                                        exclusiveSoilUsage=soilUsage,
                                        documentations={'C++':cppdoc,
                                                        'Python': RstDocProvider(cppdoc),
                                                        'Matlab': RstDocProvider(cppdoc)},
                                        inherits = inherits,
                                        constructors = parsed_constructors,
                                        defining_header=self.Filename)
        for method in wrappedMethods:
          method.ParentClass = wrappedClass
        wrappedClass.AvailableIn = availableIn
        return wrappedClass

    def ParseFunction(self, func, clstypenames=None, cls=None, isAbstract=False, used_split_member=False):
        # get classes template params
        classDefLineNumber = func["line_number"]
        tpp = TemplateParameterParser(self.Filename, classDefLineNumber)
        typenames, templateParamStr = tpp.RetrieveTemplateParameters()
        # extract types from doxygen comment
        dte = DoxygenTypeExtractor(func.get("doxygen"))
        availableIn, types, soilUsage = dte.Extract()
        methodAvailableIn, exportedName = dte.ExtractExportedName()
        if types == None and \
           not func['name'] == 'serialize' and \
           not isAbstract and \
           not (func['name'] in ['save', 'load'] and used_split_member):
            print("[WARNING]    no type comment for function " +  func["name"])

        nameFormat = "{0}{1}"

        if not exportedName == None:
            nameFormat = exportedName + "{1}"

        # Retrieve parameters of the constructor and wrap them into the intermediate structure
        wmc = WrappedMethodCreator(func,
                                   func["name"],
                                   nameFormat,
                                   types,
                                   "standard_method.jinja",
                                   availableIn,
                                   self.Filename)
        method = wmc.CreateWrappedMethod(clstypenames, cls)
        method.ExportedName = exportedName

        if not func.get('parent') == None:
            # get parent type (because it is a instance method, which can't be called instant-wise in the c api :(
            parent = func['parent'] # is now a cppheaderparser class obj

            # get classes template params
            classDefLineNumber = parent["line_number"]
            tpp = TemplateParameterParser(self.Filename, classDefLineNumber)
            typenames, templateParamStr = tpp.RetrieveTemplateParameters()

            if typenames == None:
                typestr = parent['name']
            else:
                typestr = parent['name'] + '<' + ', '.join(typenames) + '>'
            type = CppType(typestr, True)
            firstParam = Argument(type, parent['name'].lower(), None, typestr)
            method.ParentClassParam = firstParam
        if clstypenames is None:
          method.TemplateArguments = typenames
          method.TemplateString = templateParamStr
        return method
