# Authors: Philipp Harzig, Christoph Lassner.
from TypeTranslations import _dtype_c_translation, _dtype_str_translation,\
  _matlab_cpp_translation, _cpp_matlab_translation
from collections import namedtuple
import re

class FertilizedClass(object):
    r"""Describes a class in the fertilized library with its possible templated
    values.
    
    Parameters
    ==========

    classType : CppType
      The type of this class.

    supportedTypes : InstantiationTypes
      Instantiations of this class that are generated (e.g. <int, uint>)

    methods : list(WrappedMethods)
      List of class functions to wrap.

    package : string
      Name of the containing subfolder.

    specialConstructor : string or None
      If None, use the default constructor. Otherwise use the specified method
      as constructor.

    dummyClass : Bool
      Whether this class is not part of the library, but a generated dummy
      object.
    """
    def __init__(self,
                 classType,
                 supportedTypes,
                 methods,
                 package,
                 specialConstructor=None,
                 dummyClass=False,
                 isAbstract=False,
                 declarationMethod='class',
                 templatingString='',
                 exclusiveSoilUsage=None,
                 documentations={'C++':'',
                                 'Python':'',
                                 'Matlab':''},
                 inherits=None,
                 constructors=None,
                 defining_header=None):
        self.ClassName = classType.TypeString
        self.ClassType = classType
        self.IsAbstract = isAbstract
        self.DeclarationMethod = declarationMethod
        self.TemplatingString = templatingString
        self.ExclusiveSoilUsage = exclusiveSoilUsage
        self.Documentations = documentations
        self.Inherits = inherits
        self.Constructors = constructors
        self.DefiningHeader = defining_header
         
        if supportedTypes == []:
            self.SupportedTypes = None
        else:
            self.SupportedTypes = supportedTypes
        # An array [] of methods that should be implemented by this class.
        # e.g. [predictMethod, fitMethod] where those methods are of class
        # type WrappedMethod
        self.Methods = methods
        # the package the class should go into
        self.Package = package
        self.SpecialConstuctor = specialConstructor
        self.DummyClass = dummyClass
        # if the fit methods have a different name format put it here... 
        # (e.g. RegressionForest needs different methods to fit and predict 
        # trees than normal forests...)
        # TODO: check if still necessary.
        self.DifferentFitPredictMethodNames = None

    def getOperatorEQ(self):
        matches = [m for m in self.Methods if m.FunctionPrefix.replace(" ", "") == 'operator==']
        if len(matches) == 0:
          return None
        else:
          return matches[0]

    def lackingOperatorNE(self):
        has_operatorEQ = len([m for m in self.Methods if m.FunctionPrefix.replace(" ", "") == 'operator==']) > 0
        has_operatorNE = len([m for m in self.Methods if m.FunctionPrefix.replace(" ", "") == 'operator!=']) > 0
        return has_operatorEQ and not has_operatorNE

    def getSampleInstantiationTypes(self):
        if self.SupportedTypes is None or len(self.SupportedTypes) == 0:
          return None
        else:
          return self.SupportedTypes[0]

    def getExclusiveSoilUsageAbbreviation(self):
        parts = []
        inside_count = 0
        last_part_end = 0
        for index in xrange(len(self.ExclusiveSoilUsage)):
          if self.ExclusiveSoilUsage[index] == ',' and inside_count == 0:
            parts.append(self.ExclusiveSoilUsage[last_part_end:index].strip())
            last_part_end = index
          elif self.ExclusiveSoilUsage[index] in ['(', '<']:
            inside_count += 1
          elif self.ExclusiveSoilUsage[index] in [')', '>']:
            inside_count -= 1
          elif index == len(self.ExclusiveSoilUsage) - 1:
            if not inside_count == 0:
              raise Exception("Error parsing exclusive soil usage!")
            if not last_part_end == index:
              parts.append(self.ExclusiveSoilUsage[last_part_end:index+1].strip())
        translated_parts = []
        for part in parts:
          if _dtype_str_translation.has_key(part):
            translated_parts.append(_dtype_str_translation[part])
          else:
            translated_parts.append(part)
        abbr = '_'.join(translated_parts)
        return abbr

    def getVectorizedTypes(self, int_lang=None):
        r"""Returns vectorized types in arguments as well as return values."""
        vec_types = set()
        if int_lang is None or 'Python' in self.AvailableIn:
          for func in self.Methods:
            vec_types.update(func.getVectorizedTypes(int_lang))
        return vec_types

    def getConstructor(self):
        length = 0
        if not self.ClassType.TemplateParams == None:            
            length = len(self.ClassType.TemplateParams)
        if self.SpecialConstuctor == None:
            return [length, self.ClassName]
        else:
            return [length, self.SpecialConstuctor]

    def hasParameterlessConstructor(self, language = None):
        return not self.Constructors is None and \
          len([cons for cons in self.getConstructorsFor(language) if len(cons.Arguments) == 0]) > 0

    def isSerializable(self):
        return len([method for method in self.Methods if \
                    method.FunctionPrefix == 'serialize']) > 0 or \
               len([method for method in self.Methods if \
                    method.FunctionPrefix == 'load']) > 0 and \
               len([method for method in self.Methods if \
                    method.FunctionPrefix == 'save']) > 0 # Boost split member.

    def getConstructorsFor(self, language):
        if language is None:
          return self.Constructors
        else:
          return [cons for cons in self.Constructors if language in cons.AvailableIn]

class RstDocProvider(object):
  def __init__(self, doxy_str):
      self.Doxy_str = doxy_str

  def render_at(self, indents,
                      newline_str='\n',
                      escape=[],
                      string_enclosure=True,
                      prepend='',
                      docstarter=''):
      indents = "".join(indents * [" "])
      if prepend.endswith("*/"):
        prepend = prepend[:-3]
      lines = (prepend+self.Doxy_str[5:]).split("\n*")
      # Iterate over the lines ones and convert them.
      params_started = False
      param_desc_started = False
      in_list = False
      convlines = []
      for lineidx, line in enumerate(lines):
        # Last line.
        if lineidx == len(lines) - 1:
          if string_enclosure:
            convlines.append(indents + 'r"""')
          continue
        # In between...
        stripped_line = line.strip()
        # Treat the \brief and first line specials.
        if lineidx == 0:
          str_start = 'r"""' if string_enclosure else ''
          if stripped_line.startswith(r"\param") and string_enclosure:
            convlines.append(indents + str_start)
          else:
            stripped_line = str_start + stripped_line
        # \brief
        stripped_line = stripped_line.replace(r"\brief ", "")
        # \ref
        stripped_line = stripped_line.replace(r"\ref ", "")
        # Parameter descriptions.
        if stripped_line.startswith(r'\param'):
          if not params_started:
            convlines.append(indents + docstarter + 'Parameters')
            convlines.append(indents + docstarter + '==========')
            params_started = True
            assert not param_desc_started
          param_desc_started = True
          convlines.append(indents + docstarter)
          stripped_line = stripped_line[7:] # Remove \param 
          # Insert :
          if " " in stripped_line:
            spindex = stripped_line.index(" ")
            stripped_line = stripped_line[:spindex+1] + ":" + stripped_line[spindex:]
        elif param_desc_started:
          if stripped_line == "":
            param_desc_started = False
          else:
            stripped_line = "  " + stripped_line
        # List treatment.
        if stripped_line.startswith("- "):
          if not in_list:
            convlines.append(indents + docstarter)
            in_list = True
        if stripped_line == '.':
          stripped_line = ''
          in_list = False
        # Group specifier treatment.
        if stripped_line.startswith('\ingroup '):
          continue
        # Separator treatment.
        if stripped_line == '-----':
          stripped_line += "\n"
          if not docstarter is None and docstarter != '':
            stripped_line += indents + docstarter
        # Math replacements.
        inline_splits = stripped_line.split(r'\f$')
        if len(inline_splits) % 2 == 0:
          raise Exception("Malformed doxygen inline formula! Inline formulas must be on one line!")
        starts_joined = [inline_splits[i]+":math:`"+inline_splits[i+1] for i in xrange(0,len(inline_splits)-1,2)] + [inline_splits[-1]]
        stripped_line = "`".join(starts_joined)
        stripped_line = stripped_line.replace(r'\f[', '\n%s.. math::\n%s  ' % (indents + docstarter, indents + docstarter))
        stripped_line = stripped_line.replace(r'\f]', '\n%s' % (indents + docstarter))
        # Finalize.
        stripped_line = indents + docstarter + stripped_line
        convlines.extend(stripped_line.split('\n'))
      # Iterate over the converted lines and apply the escapes.
      for lineidx in xrange(len(convlines)):
        for escape_str in escape:
          convlines[lineidx] = convlines[lineidx].replace(escape_str, '\\' + escape_str)
      return newline_str.join(convlines)

class InstantiationTypes(object):
    r"""
    The instantiation types of one templated object instantiation.
    
    Parameters
    ==========

    types : list(string)
      The C++ template arguments as strings.
    """
    def __init__(self, types):
        self.Types = types
        self.TypesString = "_".join([_dtype_str_translation[type.strip().replace(" ", "").replace("\r","").replace("\n","")] \
                                      for type in types])
    def __eq__(self, other):
        return self.TypesString == other.TypesString

    def __ne__(self, other):
        return not self == other

    def __str__(self):
        return self.TypesString

    def __repr__(self):
        return self.TypesString

    def __hash__(self):
        return hash(self.TypesString)

class CppType(object):
    r"""
    Describes a C++ type.

    Parameters
    ==========
    typeString : string
      The type name.

    isClass : bool
      Whether the type must be stored as void* in C (for the Matlab interface).

    templateParams : list(string)
      The names of all template parameters.

    isVectorOfType : bool
      If the C++ type represents a vector of objects.

    isVectorTypeShared : bool
      If the C++ type represents a vector of shared objects.
    """
    def __init__(self,
                 typeString,
                 isClass = False,
                 templateParams = None,
                 isVectorOfType = False,
                 isVectorTypeShared = True,
                 usedByPointer = False,
                 usedByReference = False,
                 isConst = False):
        self.TypeString = typeString.strip()
        if self.TypeString.startswith("DllExport "):
          self.TypeString = self.TypeString[10:]
        self.IsPtr = isClass       
        self.TemplateParams = templateParams
        self.IsVectorOfType = isVectorOfType
        self.IsVectorTypeShared = isVectorTypeShared
        self.UsedByPointer = usedByPointer
        self.UsedByReference = usedByReference
        self.IsConst = isConst

    def isMxArrayType(self):
        r"""
        Is true, if the type translates into a mxArray in C.
        """
        shortTypeString = self.TypeString.replace('fertilized::', '')
        return shortTypeString.startswith("Array<")

    def getTemplateParamStandardPositions(self):
        ret = []
        if self.TemplateParams is None:
          return ret
        if 'input_dtype' in self.TemplateParams:
          ret.append(0)
        if 'feature_dtype' in self.TemplateParams:
          ret.append(1)
        if 'annotation_dtype' in self.TemplateParams:
          ret.append(2)
        if 'leaf_return_dtype' in self.TemplateParams:
          ret.append(3)
        if 'forest_return_dtype' in self.TemplateParams:
          ret.append(4)
        return ret

    def getMxArrayTemplateName(self, get_ndim=False):
        r"""
        Gets the template argument of the mxarray (equals a ndarray in cpp: Array<..>)
        """
        shortTypeString = self.TypeString.replace('fertilized::', '')
        regex = re.compile("Array<(?:const|)\s*([a-zA-Z\d:_]*?)\s*(?:const|)\s*,\s*(\d+)\s*,\s*(\d+)\s*>")
        match = regex.match(shortTypeString)
        if not match == None:
            if get_ndim:
              return match.group(1), match.group(3)
            else:
              return match.group(1)
        else:
            raise Exception("Cant parse array!")

    def renderConversionCode(self,
                             language,
                             argname,
                             instantiation_types=None,
                             template_params=None):
        r"""
        Renders conversion C++ code.
        """
        assert self.needsConversion()
        assert language == 'Matlab', 'Conversions only implemented for Matlab!'
        if template_params is None:
          template_params = self.TemplateParams
        if self.isMxArrayType() and not self.IsVectorOfType:
          arraytype = self.getMxArrayTemplateName().strip()
          if not instantiation_types is None and not template_params is None:
            for idx, tprm in enumerate(template_params):
              if arraytype == tprm:
                arraytype = instantiation_types.Types[idx]
          if not argname is None:
            code = r"""
    fertilized::Array<{dtype}, {ndim}, {ndim}> __converted_{argname};
    {{
      const mwSize _matlab_ndim = mxGetNumberOfDimensions({argname});
      const mxClassID _matlab_dtid = mxGetClassID({argname});
      const mwSize* _matlab_shape = mxGetDimensions({argname});
      // Dimensionality check.
      if (_matlab_ndim != {ndim}) {{
        mexErrMsgTxt(("Expected {ndim} dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }}
      // Dtype check.
      if (_matlab_dtid != {matlab_dtype}) {{
        mexErrMsgTxt("Wrong MATLAB datatype of argument {argname}!");
      }}
      Vector<std::size_t, {ndim}> shape;
      for (int i = 0; i < {ndim}; ++i) {{
        shape[i] = _matlab_shape[i];
      }}
      __converted_{argname} = allocate(shape);
      mwIndex _idx [{ndim}];
      for (int i = 0; i < {ndim}; ++i) {{
        _idx[i] = 0;
      }}
      int dimidx;
      {dtype} *_dptr = __converted_{argname}.getData();
      {dtype} *_iptr = reinterpret_cast<{dtype}*>(mxGetData({argname}));
      for (std::size_t i = 0; i < shape.product(); ++i) {{
        _dptr[i] = _iptr[mxCalcSingleSubscript({argname}, _matlab_ndim, _idx)];
        dimidx = {ndim}-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {{
          _idx[dimidx] = 0;
          dimidx -= 1;
        }}
        _idx[dimidx]++;
      }}
    }}""".format(**{'argname':argname,
                   'matlab_dtype':_cpp_matlab_translation[arraytype],
                   'dtype':arraytype,
                   'ndim':self.getMxArrayTemplateName(True)[1]})
            return code
          else:
            code = r"""
    mxArray *__converted_return_value;
    {{
      // Create array.
      mwSize ndim = {ndim};
      mwSize shape[ {ndim} ];
      auto cpparray_shape = libfunc_result.getShape();
      for (int i = 0; i < {ndim}; ++i) {{
        shape[i] = cpparray_shape[i];
      }}
      mxClassID classid = {matlab_dtype};
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [{ndim}];
      for (int i = 0; i < {ndim}; ++i) {{
        _idx[i] = 0;
      }}
      int dimidx;
      {dtype} *_dptr = libfunc_result.getData();
      {dtype} *_iptr = reinterpret_cast<{dtype}*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < cpparray_shape.product(); ++i) {{
        _iptr[mxCalcSingleSubscript(__converted_return_value, {ndim}, _idx)] = _dptr[i];
        dimidx = {ndim}-1;
        while (_idx[dimidx] == shape[dimidx]-1) {{
          _idx[dimidx] = 0;
          dimidx -= 1;
        }}
        _idx[dimidx]++;
      }}
    }}""".format(**{'matlab_dtype':_cpp_matlab_translation[arraytype],
                    'dtype':arraytype,
                    'ndim':self.getMxArrayTemplateName(True)[1]})
            return code
        elif self.isFertilizedObjectInMatlab():
          if not argname is None:
            if not self.IsVectorTypeShared:
              dereference = ''
              if not self.UsedByPointer:
                dereference = '*'
              reference = ''
              if self.UsedByReference:
                reference = '&'
              return r"""
    auto __shptr_{argname} = *reinterpret_cast<std::shared_ptr<{TypeString}>*>({argname});
    auto {reference}__converted_{argname} = {dereference}(__shptr_{argname}.get());
            """.format(**{'TypeString':self.render(instantiation_types, omit_shared=True, omit_reference=True, omit_pointer=True, omit_const=True, template_params=template_params, omit_typename=True),
                          'argname':argname,
                          'reference':reference,
                          'dereference': dereference})
            else:
              if not self.TemplateParams is None and len(self.TemplateParams) > 0:
                assert not instantiation_types is None and len(instantiation_types.Types) > 0,\
                  "The type %s has template params and I don't know how to instantiate them!" % \
                  (self.render())
              code = r"""
    auto __converted_{argname} = *reinterpret_cast<std::shared_ptr<{TypeString}>*>({argname});
              """.format(**{'TypeString':self.render(instantiation_types, omit_shared=True, template_params=template_params, omit_typename=True),
                            'argname':argname})
              return code
          else:
            assert self.IsVectorTypeShared, \
              "Library objects must be passed to the interface in shared pointers! (%s)" % (self.TypeString)
            code = r"""
    void * __converted_return_value = copy_to_heap(libfunc_result);
    """
            return code
        elif self.IsVectorOfType:
          contained_type = self.render(instantiation_types,
                                       template_params=template_params,
                                       omit_vector=True,
                                       omit_typename=True)
          if not argname is None:
            # To C++ converters.
            if self.isFertilizedObjectInMatlab(allow_vector_of=True, instantiation_types=instantiation_types, template_params=template_params):
              return r"""
    {vec_cpp_type} __converted_{argname};
    {{
      std::vector<void*> carryvec = *reinterpret_cast<std::vector<void*>*>({argname});
      __converted_{argname} = recover_vec_types<{vec_inner_type}>(carryvec);
    }}
              """.format(**{'vec_cpp_type':self.render(instantiation_types, template_params=template_params, omit_reference=True, omit_pointer=True, omit_const=True, omit_typename=True),
                            'vec_inner_type': contained_type,
                            'argname':argname})
            elif contained_type in _cpp_matlab_translation.keys():
              return r"""
    {vec_cpp_type} __converted_{argname};
    {{
      const mwSize _matlab_ndim = mxGetNumberOfDimensions({argname});
      const mxClassID _matlab_dtid = mxGetClassID({argname});
      const mwSize* _matlab_shape = mxGetDimensions({argname});
      // Dimensionality check.
      if (_matlab_ndim != {ndim}) {{
        mexErrMsgTxt(("Expected {ndim} dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }}
      // Dtype check.
      if (_matlab_dtid != {matlab_dtype}) {{
        mexErrMsgTxt("Wrong MATLAB datatype of argument {argname}!");
      }}
      // Shape check.
      if (_matlab_shape[0] != 1) {{
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector!");
      }}
      __converted_{argname} = {vec_cpp_type}(_matlab_shape[1]);
      mwIndex _idx [{ndim}];
      for (std::size_t i = 0; i < {ndim}; ++i) {{
        _idx[i] = 0;
      }}
      int dimidx;
      {dtype} *_iptr = reinterpret_cast<{dtype}*>(mxGetData({argname}));
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {{
        __converted_{argname}[i] = _iptr[mxCalcSingleSubscript({argname}, _matlab_ndim, _idx)];
        dimidx = {ndim}-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {{
          _idx[dimidx] = 0;
          dimidx -= 1;
        }}
        _idx[dimidx]++;
      }}
    }}""".format(**{'argname':argname,
                    'matlab_dtype':_cpp_matlab_translation[contained_type],
                    'dtype':contained_type,
                    'ndim': '2',
                    'vec_cpp_type':self.render(instantiation_types, template_params=template_params, omit_reference=True, omit_pointer=True, omit_const=True, omit_typename=True)})
            elif self.isMxArrayType():
              dtype = contained_type[contained_type.index("<")+1:contained_type.index(",")].replace('const ', '').strip()
              return r"""
   {vec_cpp_type} __converted_{argname};
   {{
      const mwSize _matlab_ndim = mxGetNumberOfDimensions({argname});
      const mxClassID _matlab_dtid = mxGetClassID({argname});
      const mwSize* _matlab_shape = mxGetDimensions({argname});
      // Dimensionality check.
      if (_matlab_ndim != 2) {{
        mexErrMsgTxt(("Expected 2 dimensions of the cell array, received " +
          std::to_string(_matlab_ndim) + " ({argname})").c_str());
      }}
      // Dtype check.
      if (_matlab_dtid != mxCELL_CLASS) {{
        mexErrMsgTxt("Wrong MATLAB datatype of argument {argname}! Cell array of arrays required.");
      }}
      // Shape check.
      if (_matlab_shape[0] != 1) {{
        mexErrMsgTxt("Wrong Vector shape! Expecting a row vector ({argname}!");
      }}
      __converted_{argname} = {vec_cpp_type}(_matlab_shape[1]);
      for (std::size_t i = 0; i < _matlab_shape[1]; ++i) {{
        mxArray * cell = mxGetCell({argname}, i);
        const mwSize _cell_ndim = mxGetNumberOfDimensions(cell);
        const mxClassID _cell_dtid = mxGetClassID(cell);
        const mwSize* _cell_shape = mxGetDimensions(cell);
        // Dimensionality check.
        if (_cell_ndim != {ndim}) {{
          mexErrMsgTxt(("Expected {ndim} dimensions of each cell, received " +
            std::to_string(_cell_ndim)).c_str());
        }}
        // Dtype check.
        if (_cell_dtid != {matlab_dtype}) {{
          mexErrMsgTxt("Wrong MATLAB datatype while parsing cells of {argname}!");
        }}
        Vector<std::size_t, {ndim}> shape;
        for (std::size_t j = 0; j < {ndim}; ++j) {{
          shape[j] = _cell_shape[j];
        }}
        Array<{dtype}, {ndim}, {ndim}> __converted_cell = allocate(shape);
        mwIndex _idx [{ndim}];
        for (std::size_t j = 0; j < {ndim}; ++j) {{
          _idx[j] = 0;
        }}
        int dimidx;
        {dtype} *_dptr = __converted_cell.getData();
        {dtype} *_iptr = reinterpret_cast<{dtype}*>(mxGetData(cell));
        for (std::size_t j = 0; j < shape.product(); ++j) {{
          _dptr[j] = _iptr[mxCalcSingleSubscript(cell, _cell_ndim, _idx)];
          dimidx = {ndim}-1;
          while (_idx[dimidx] == _cell_shape[dimidx]-1) {{
            _idx[dimidx] = 0;
            dimidx -= 1;
          }}
          _idx[dimidx]++;
        }}
        __converted_{argname}.push_back(__converted_cell);
      }}
   }}""".format(**{'argname': argname,
                   'matlab_dtype': _cpp_matlab_translation[dtype],
                   'ndim': contained_type[contained_type.rindex(",")+1:contained_type.rindex(">")],
                   'dtype': dtype,
                   'vec_cpp_type': self.render(instantiation_types, template_params=template_params, omit_reference=True, omit_pointer=True, omit_const=True, omit_typename=True)})
            elif contained_type == 'std::string':
              return r"""
    std::vector<std::string> __converted_{argname} = *reinterpret_cast<std::vector<std::string>*>({argname});
              """.format(**{'argname':argname})
            else:
              raise Exception("Unknown to-vector conversion required!");
          else:
            # To Matlab converters.
            if self.isFertilizedObjectInMatlab(allow_vector_of=True, instantiation_types=instantiation_types, template_params=template_params):
              raise Exception("No 'vector of library type' converters to Matlab are available (yet).")
            elif contained_type in _cpp_matlab_translation.keys():
              return r"""
    mxArray *__converted_return_value;
    {{
      // Create array.
      mwSize ndim = 2;
      mwSize shape[ 2 ];
      shape[0] = 1;
      shape[1] = libfunc_result.size();
      mxClassID classid = {matlab_dtype};
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      {dtype} *_dptr = &(libfunc_result[0]);
      {dtype} *_iptr = reinterpret_cast<{dtype}*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < libfunc_result.size(); ++i) {{
        _iptr[i] = _dptr[i];
      }}
    }}        """.format(**{'matlab_dtype':_cpp_matlab_translation[contained_type],
                            'dtype': contained_type})
            elif self.isMxArrayType():
              raise Exception("No 'vector of array' converters to Matlab are available (yet).")
            else:
              raise Exception("Unknown vector conversion required!")
        raise Exception('Unknown dtype to convert!')

    def needsConversion(self, allow_vector_of=False,
                              instantiation_types=None,
                              template_params=None):
        r"""
        Is true, if the type is not a C type or in a vector.
        """
        lookupstr = self.render(instantiation_types, template_params=template_params, omit_vector=allow_vector_of, omit_typename=True, omit_const=True, omit_pointer=True, omit_reference=True)
        return (not _dtype_c_translation.has_key(lookupstr)) or \
               self.IsVectorOfType and not allow_vector_of
    
    def isFertilizedObjectInMatlab(self, allow_vector_of=False,
                                         instantiation_types=None,
                                         template_params=None):
        r"""
        Is true, if it is a plain (not a vector of) object that is not a C type.
        """
        return self.needsConversion(allow_vector_of, instantiation_types, template_params) and \
               (not self.IsVectorOfType or allow_vector_of) and \
               not self.isMxArrayType()

    def getCType(self, is_return_type=False, template_params=None, instantiation_types=None):
        r"""
        Returns the representing C type representation of the object.

        If the object is not representable in C, returns void(*).
        """
        ctype = ''
        if self.IsVectorOfType:
          if self.isFertilizedObjectInMatlab(allow_vector_of=True, instantiation_types=instantiation_types, template_params=template_params):
            return 'void *'
          elif self.TypeString == 'std::string':
            return 'void *'
          else:
            return 'mxArray *'
        if not self.needsConversion():
            ctype = _dtype_c_translation.get(self.TypeString)
        elif self.isMxArrayType():
            ctype = 'mxArray'
        else:
            ctype = 'void *'
        if not ctype == 'void *' and (self.IsPtr or is_return_type or self.isMxArrayType()) and self.needsConversion():
            ctype += ' *'
        return ctype

    def getClassName(self, remove_qualifier=False):
        ret_name = self.TypeString
        if remove_qualifier and "::" in ret_name:
          ret_name = ret_name[ret_name.index("::")+2:]
        if "<" in ret_name:
          ret_name = ret_name[:ret_name.index("<")]
        return ret_name

    def render(self, instantiation_types=None,
                     omit_shared=False,
                     template_params=None,
                     omit_typename=False,
                     omit_vector=False,
                     omit_const=False,
                     omit_pointer=False,
                     omit_reference=False):
        r"""
        Returns a full string representation of this type.
        """
        typestring = self.TypeString[:]
        if omit_typename and typestring.startswith('typename '):
          typestring = typestring[9:]
        if not instantiation_types is None and not self.TemplateParams is None and len(self.TemplateParams) > 0:
          if template_params is None:
            template_params = self.TemplateParams
          if not template_params is None:
            if '<' in typestring or any([tp in typestring for tp in template_params]):
              for tplidx, tplname in enumerate(template_params):
                typestring = typestring.replace(tplname, instantiation_types.Types[tplidx])
            else:
              # The class was parsed as raw object. Append...
              typestring += '<' + ','.join(instantiation_types.Types) + '>'
        if self.IsVectorOfType and not omit_vector:
          typestring = 'std::vector<%s>' % (typestring)
        elif self.IsVectorTypeShared and not omit_shared:
          typestring = 'std::shared_ptr<%s>' % (typestring)
        if self.IsConst and not omit_const and not (self.IsVectorOfType and omit_vector) and not (self.IsVectorTypeShared and omit_shared):
          typestring = 'const ' + typestring
        if self.UsedByPointer and not omit_pointer and not (self.IsVectorOfType and omit_vector) and not (self.IsVectorTypeShared and omit_shared):
          typestring += " *"
        elif self.UsedByReference and not omit_reference and not (self.IsVectorOfType and omit_vector) and not (self.IsVectorTypeShared and omit_shared):
          typestring += " &"
        return typestring


class Argument(object):
    def __init__(self,
                 type=None,
                 name=None,
                 defaultvalue=None,
                 typestring=None):
        self.type=type
        self.name=name
        self.defaultvalue=defaultvalue
        self.typestring=typestring

    def renderDefaultPython(self):
        if self.defaultvalue.startswith("static_cast<"):
            return self.defaultvalue[self.defaultvalue.index(">(")+2:self.defaultvalue.index(")")]
        else:
            return self.defaultvalue

    def renderDefaultMatlab(self, obj_name='Soil'):
        rendval = ''
        if self.defaultvalue.strip().startswith("_"):
          rendval = self.defaultvalue.strip().lstrip("_")
          rendval = obj_name + '.' + rendval
        else:
          rendval = self.defaultvalue.strip()
        return rendval.replace('"', "'")

class WrappedMethod(object):
    r"""
    Describes a method to be wrapped.
    """
    def __init__(self,
                 functionPrefix,
                 nameFormat,
                 returnType,
                 arguments,
                 supportedTypes,
                 functionTemplate,
                 availableIn,
                 implementBaseMethod=True,
                 templateArguments=[],
                 templateString='',
                 documentations={'C++':'',
                                 'Python':'',
                                 'Matlab':''},
                 const=False,
                 parentClassParam=None,
                 defining_header=None,
                 exportedName=None,
                 exclusiveSoilUsage=None,
                 isConstructor=False):
        r"""
        Parameters
        ==========

        functionPrefix : string
          The prefix for the exported name.

        nameFormat : string
          Format string to create the method name (two string parameters 
          required, one for class name and one for instantiation suffix).

        returnType : CppType
          The type of the return value.

        arguments : list(Argument)
          The list of method arguments with type, name and default values.

        supportedTypes : InstantiationTypes
          Instantiations of this class that are generated (e.g. <int, uint>)

        functionTemplate : string
          Jinja template filename to generate the export.
          
        availableIn : list(string)
          Defines in which interfaces the method should be available.

        implementBaseMethod : bool
          If True, generate a helper base method or not.
        """
        self.FunctionPrefix = functionPrefix
        self.NameFormat = nameFormat
        self.ReturnType = returnType
        self.Arguments = arguments
        self.SupportedTypes = supportedTypes
        self.FunctionTemplate = functionTemplate
        self.ImplementBaseMethod = implementBaseMethod
        self.AvailableIn = availableIn
        self.TemplateArguments = templateArguments
        self.TemplateString = templateString
        self.Documentations = documentations
        self.Const = const
        self.ParentClassParam = parentClassParam
        self.DefiningHeader = defining_header
        self.ExportedName = exportedName
        self.ExclusiveSoilUsage = exclusiveSoilUsage
        self.ParentClass = None
        self.IsConstructor = isConstructor

    def getTemplateArgumentsLength(self):
        length = 0
        if not self.TemplateArguments == None:            
            length = len(self.TemplateArguments)
        return length

    def getSampleInstantiationTypes(self):
        if self.SupportedTypes is None or len(self.SupportedTypes) == 0:
          return None
        else:
          return self.SupportedTypes[0]

    def num_default_arguments(self):
        return len([arg for arg in self.Arguments if not arg.defaultvalue is None])

    def getVectorizedTypes(self, int_lang=None):
        r"""Returns vectorized types in arguments as well as return values."""
        vec_types = set()
        if int_lang is None or 'Python' in self.AvailableIn:
          for arg in self.Arguments:
            if arg.type.IsVectorOfType:
              vec_types.add(arg.type.TypeString)
          if self.ReturnType.IsVectorOfType:
            vec_types.add(self.ReturnType.TypeString)
        if (self.TemplateArguments is None or len(self.TemplateArguments) == 0) and \
           (self.ParentClass is None or self.ParentClass.ClassType.TemplateParams is None or len(self.ParentClass.ClassType.TemplateParams) == 0):
          return vec_types
        else:
          inst_vec_types = set()
          for vec_type in vec_types:
            tokens = tokenize(vec_type)
            if not self.ParentClass is None and \
               not self.ParentClass.SupportedTypes is None and \
               not len(self.ParentClass.SupportedTypes) == 0:
              for insttypes in self.ParentClass.SupportedTypes:
                tmp_tokens = tokens[:]
                for en_ind, token in enumerate(tmp_tokens):
                  for child_ind, tparam in enumerate(self.ParentClass.ClassType.TemplateParams):
                    if tparam in token:
                      tmp_tokens[en_ind] = tmp_tokens[en_ind].replace(tparam, insttypes.Types[child_ind])
                if not self.TemplateArguments is None and \
                   not len(self.TemplateArguments) == 0 and \
                   not self.SupportedTypes is None and \
                   not len(self.SupportedTypes) == 0:
                  for finsttypes in self.SupportedTypes:
                    for en_ind, token in enumerate(tokens):
                      for child_ind, tparam in enumerate(self.TemplateArguments):
                        if tparam in token:
                          tmp_tokens[en_ind] = token[en_ind].replace(tparam, finsttypes.Types[child_ind])
                    inst_vec_types.add(reassemble(vec_type, tmp_tokens))
                else:
                  inst_vec_types.add(reassemble(vec_type, tmp_tokens))
            elif not self.TemplateArguments is None and \
                 not self.SupportedTypes is None and \
                 not len(self.SupportedTypes) == 0:
              tmp_tokens = tokens[:]
              for finsttypes in self.SupportedTypes:
                for en_ind, token in enumerate(tokens):
                  for child_ind, tparam in enumerate(self.TemplateArguments):
                    if tparam in token:
                      tmp_tokens[en_ind] = token[en_ind].replace(tparam, finsttypes.Types[child_ind])
                inst_vec_types.add(reassemble(vec_type, tmp_tokens))
        return inst_vec_types

    def getExclusiveSoilUsageAbbreviation(self):
        parts = []
        inside_count = 0
        last_part_end = 0
        for index in xrange(len(self.ExclusiveSoilUsage)):
          if self.ExclusiveSoilUsage[index] == ',' and inside_count == 0:
            parts.append(self.ExclusiveSoilUsage[last_part_end:index].strip())
            last_part_end = index
          elif self.ExclusiveSoilUsage[index] in ['(', '<']:
            inside_count += 1
          elif self.ExclusiveSoilUsage[index] in [')', '>']:
            inside_count -= 1
          elif index == len(self.ExclusiveSoilUsage) - 1:
            if not inside_count == 0:
              raise Exception("Error parsing exclusive soil usage!")
            if not last_part_end == index:
              parts.append(self.ExclusiveSoilUsage[last_part_end:index+1].strip())
        translated_parts = []
        for part in parts:
          if _dtype_str_translation.has_key(part):
            translated_parts.append(_dtype_str_translation[part])
          else:
            translated_parts.append(part)
        abbr = '_'.join(translated_parts)
        return abbr

    def prefixForMatlab(self, pref):
        if pref == 'operator()':
          return 'apply'
        elif pref == 'operator==':
          return 'eq'
        else:
          return pref

def tokenize(str):
  if not '<' in str:
    return [str]
  child_inherits = str.strip()
  child_inherits = child_inherits[child_inherits.index("<")+1:child_inherits.rindex(">")]
  tokens = ['']
  token_id = 0
  inside_count = 0
  for chr in child_inherits:
    if chr in [',', '<', '(', ')', '>']:
      tokens.append('')
      token_id += 1
      continue
    if chr == '<' or chr == '(':
      inside_count += 1
    if chr == '>' or chr == ')':
      inside_count -= 1
    tokens[token_id] += chr
  assert inside_count == 0, '%s could not be parsed.' % (child_inherits)
  for tkidx in xrange(len(tokens)):
    tokens[tkidx] = tokens[tkidx].strip()
  return tokens

def reassemble(str, repl_tokens):
  if not '<' in str:
    return repl_tokens[0]
  reassembled = str[:str.index("<")+1]
  child_inherits = str.strip()
  child_inherits = child_inherits[child_inherits.index("<")+1:child_inherits.rindex(">")]
  tokens = ['']
  token_id = 0
  inside_count = 0
  for chr in child_inherits:
    if chr in [',', '<', '(', ')', '>']:
      reassembled += repl_tokens[token_id] + chr
      tokens.append('')
      token_id += 1
      continue
    if chr == '<' or chr == '(':
      inside_count += 1
    if chr == '>' or chr == ')':
      inside_count -= 1
    tokens[token_id] += chr
  assert inside_count == 0, '%s could not be parsed.' % (child_inherits)
  assert token_id == len(repl_tokens) - 1 or token_id == len(repl_tokens) - 1
  if token_id == len(repl_tokens) -1:
    reassembled += repl_tokens[-1]
  reassembled += str[str.rindex('>'):]
  return reassembled
