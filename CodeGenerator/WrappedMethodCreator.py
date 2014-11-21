# Authors: Philipp Harzig, Christoph Lassner.
import re
from helper_classes import CppType, WrappedMethod, Argument, RstDocProvider
from ParameterWrapper import ParameterWrapper, parse_raw_type

class WrappedMethodCreator(object):
    """Uses a raw cpp header method (from CppHeaderParser) to create a WrapperMethod object,
       which is required to generate the matlab wrapper interface"""

    def __init__(self,
                 method,
                 functionPrefix,
                 nameFormat,
                 instantiationTypes,
                 functionTemplate,                 
                 availableIn,
                 filename):   
        r"""
        Parameters
        ==========
        method : CppHeaderParser method dictionary
          The method to wrap.
        functionPrefix : string
          The prefix for the exported name.
        nameFormat : string
          Format string to create the method name (two string parameters 
          required, one for class name and one for instantiation suffix).
        instantiationTypes : list(InstantiationType)
          All types for which this method should be instantiated.
        functionTemplate : string
          Jinja template filename to generate the export.
        availableIn : list(string)
          Defines in which interfaces the method should be available.
        """
        self.Method = method
        self.FunctionPrefix = functionPrefix
        self.NameFormat = nameFormat
        self.InstantiationTypes = instantiationTypes
        self.AvailableIn = availableIn
        self.FunctionTemplate = functionTemplate
        self.Filename = filename

    def CreateWrappedMethod(self, cls_template_params, cls = None):
        #cls = method[parent]

        wrappedParams = []
        for p in self.Method["parameters"]:
            pw = ParameterWrapper(p, cls_template_params, cls)
            wrappedParam = pw.wrap()
            if wrappedParam == None:
                break
            wrappedParams.append(wrappedParam)
        ret_type = CppType("void", True)
        if self.FunctionPrefix != 'get':
          # self.Method['returns_unknown'] == true if a unknown reurn type exists ==> class ??
          isClass = False
          if not self.Method.get('returns_unknown') == None:
              isClass = self.Method['returns_unknown']
          ret_type_str, retVectorOfTypeVar, retVectorTypeSharedVar, retIsPtr =\
             parse_raw_type(self.Method['returns'],
                            [],
                            cls,
                            cls_template_params) #CppType(self.Method['returns'], isClass)
          if retVectorTypeSharedVar or retIsPtr:
              isClass = True
          ret_type = CppType(ret_type_str,
                             isClass,
                             None,
                             retVectorOfTypeVar,
                             retVectorTypeSharedVar,
                             self.Method['returns_pointer'],
                             self.Method['returns_reference'],
                             (self.Method.has_key('returns_const') and self.Method['returns_const']))
        cppdoc = self.Method['doxygen'] if self.Method.has_key('doxygen') else ''
        method = WrappedMethod(self.FunctionPrefix,
                               self.NameFormat,
                               ret_type,
                               wrappedParams,
                               self.InstantiationTypes,                              
                               self.FunctionTemplate,                               
                               self.AvailableIn,
                               documentations={'C++':cppdoc,
                                               'Python':RstDocProvider(cppdoc),
                                               'Matlab':RstDocProvider(cppdoc)},
                               const=self.Method['const'],
                               defining_header=self.Filename)
        return method

    def PostprocessDefaultValue(self, defaultValue):
        if not defaultValue == None:
            return defaultValue \
                    .replace("false", "0") \
                    .replace("true", "1") \
                    .replace(" ", "") \
                    .replace("f", "")
        else:
            return None

    def ExpandTypes(self, type, typedef_names, cls, cls_template_params):
        if cls == None:
            print "warning: handle unforseen cases??"
            return type

        # check if type contains a public typedef
        for tn in typedef_names:
            rc = re.compile('[\s,<]+'+tn+'[\s,>]+')
            m = rc.search(type)
            if m or tn == type:
                replacement = 'typename fertilized::' + cls["name"] + "<" + ", ".join(cls_template_params) + ">::" + tn
                type = type.replace(tn, replacement)
        return type