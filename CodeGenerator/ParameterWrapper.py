# Authors: Philipp Harzig, Christoph Lassner.
import re
from helper_classes import Argument, CppType

def PostprocessDefaultValue(defaultValue):
    if not defaultValue == None:
        return defaultValue \
               .replace("false", "0") \
               .replace("true", "1") \
               .replace(" ", "") \
               .replace("f", "") # 0.1f -> 0.1
    else:
        return None

def ExpandTypes(type, typedef_names, cls, cls_template_params):
    if typedef_names is None:
        return type
    if cls is None:
        # Module function.
        # check if type contains a public typedef
        for tn in typedef_names:
            rc = re.compile('[\s,<]+'+tn+'[\s,>]+')
            m = rc.search(type)
            if m or tn == type:
                replacement = 'typename fertilized::' + tn
                type = type.replace(tn, replacement)
        print "warning: handle unforseen cases??"
        return type
    else:
        # check if type contains a public typedef
        for tn in typedef_names:
            rc = re.compile('[\s,<]+'+tn+'[\s,>]+')
            m = rc.search(' '+type+' ')
            if m or tn == type:
                replacement = 'typename fertilized::' + cls["name"] + "<" + ", ".join(cls_template_params) + ">::" + tn
                type = type.replace(tn, replacement)
    return type

def parse_raw_type(raw_type,
                   aliases,
                   cls,
                   cls_template_params):
    expandedType = None
    typedef_names = None
    if not cls == None:
        cls_public_typedefs = cls._public_typedefs
        typedef_names = cls_public_typedefs.keys()
        # Not all typenames are parsed properly: using declarations
        # can not be parsed (e.g. subsamplingdataprovider.h).
        # Collect these, too.
        typedef_names.extend([prop['name'] for prop in cls['properties']['public'] if\
                                prop['raw_type'].startswith('using typename ')])
        if len(aliases) > 0:
            expandedType = cls_public_typedefs.get(aliases[0])
    # expand typedefs:
    # e.g. one typedef may be: typedef std::shared_ptr<tree_t> tree_ptr_t;
    # and another is:          typedef Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype> tree_t;
    # 
    # so the first one should be expanded to: std::shared_ptr<Tree<input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype>>
    # also the typenames have to extracted: input_dtype, feature_dtype, annotation_dtype, leaf_return_dtype, forest_return_dtype
    isVectorOfTypeVar = False
    isVectorTypeSharedVar = False
    isPtr = False
    type = None
    # check if type is a vector of this specific type
    regex = re.compile("(?<!<)std::vector\s*<(.*?)>$")
    match = regex.match(raw_type)
    if match == None and not expandedType == None:
        match = regex.match(expandedType)
    if not match == None:
        type = ExpandTypes(match.group(1), typedef_names, cls, cls_template_params)
        isVectorOfTypeVar = True
        isVectorTypeSharedVar = False
        isPtr = True
    # check if type is a shared_ptr of this specific type
    regex = re.compile("(?<!<)std::shared_ptr\s*<(.*?)>$")
    match = regex.match(raw_type)
    if match == None and not expandedType == None:
        match = regex.match(expandedType)
    if not match == None:
        type = ExpandTypes(match.group(1), typedef_names, cls, cls_template_params)
        isVectorOfTypeVar = False
        isVectorTypeSharedVar = True
        isPtr = True
    # other cases: type isn't set yet!
    if type == None:            
        type = raw_type
        if type.startswith('fertilized::') and not ('<') in raw_type:
          # It has been matched with a typedef automatically by
          # CppHeaderParser. However, template parameters have been
          # omitted. Reconstruct.
          if cls_template_params != [] and not cls_template_params is None:
            type = 'typename fertilized::' + cls['name'] +\
                    '<' + ','.join(cls_template_params) + '>' +\
                    raw_type[raw_type.rfind('::'):]
    return type, isVectorOfTypeVar, isVectorTypeSharedVar, isPtr

class ParameterWrapper(object):
    """description of class"""

    def __init__(self, parameter, cls_template_params, cls = None):
        self.p = parameter
        self.cls_template_params = cls_template_params
        self.cls = cls

    def wrap(self):        
        name = self.p["name"]
        type, isVectorOfTypeVar, isVectorTypeSharedVar, isPtr = \
          parse_raw_type(self.p['raw_type'], self.p['aliases'], self.cls, self.cls_template_params)
        if isVectorOfTypeVar or isVectorTypeSharedVar:
            # set the default value to none, since some cpp default values like std::vector<>(0) can't be expressed in matlab
            if not (self.p.get("defaultValue") is None or \
                    self.p.get("defaultValue").strip().startswith("_")):
                raise Exception("std::vector<...> default values must be " +\
                  "initialized with a static variable starting with '_' " + \
                  "(variable %s in unknown method in class %s)!" % \
                  (self.p.get("name"), self.cls['name']))
        if not (type.startswith('fertilized::') or \
                type.startswith('std::') or \
                type.startswith('ndarray::')) and \
           not self.p['fundamental'] and \
           not type in ['unsigned int', 'float', 'size_t'] and \
           not type in ['input_dtype', 'feature_dtype', 'annotation_dtype', 'leaf_return_dtype', 'forest_return_dtype'] and \
           not type.startswith('typename'):
          if type.startswith("const "):
            type = "const fertilized::" + type[6:]
          else:
            type = 'fertilized::' + type
        # if no default value is set this will be None, just as desired by the jinja template :)
        defaultValue = PostprocessDefaultValue(self.p.get("defaultValue"))
        typestring = ''
        if self.p['constant']:
          typestring += 'const '
        if isVectorOfTypeVar:
          typestring += 'std::vector<%s>' % (type)
        elif isVectorTypeSharedVar:
          typestring += 'std::shared_ptr<%s>' % (type)
        else:
          typestring += type
        if self.p['reference']:
          typestring += ' &'
        if self.p['pointer']:
          typestring += ' *'
        # The type is a class / ptr. if ctypes_type ==  types.c_void_p ==> Set isPtr to true!
        if not self.p.get('ctypes_type') == None and self.p['ctypes_type'] == 'ctypes.c_void_p':
            isPtr = True
        tplparams = []
        if not self.cls_template_params is None:
          for tplparam in self.cls_template_params:
            if tplparam in typestring:
              tplparams.append(tplparam)
        wrappedParam = Argument(CppType(type,
                                        isPtr,
                                        templateParams = tplparams,
                                        isVectorOfType = isVectorOfTypeVar,
                                        isVectorTypeShared = isVectorTypeSharedVar,
                                        usedByPointer = self.p['pointer'],
                                        usedByReference = self.p['reference'],
                                        isConst = self.p['constant']),
                                name,
                                defaultValue,
                                typestring)
        return wrappedParam
