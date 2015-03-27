# Authors: Philipp Harzig, Christoph Lassner.
# Load the jinja library's namespace into the current module.
from __future__ import print_function
import jinja2
import os
import shutil
import operator
import itertools
import glob
import sys
import traceback
from os.path import basename
from helper_classes import InstantiationTypes, Node
from TypeTranslations import _dtype_str_translation

print("Parsing source code...")
import ParseHeader
from helper_classes import FertilizedClass
using_rel_strs = ParseHeader.using_relations_str
classes = ParseHeader.parsed_classes
functions =  sorted(ParseHeader.parsed_functions, key=lambda x: x.FunctionPrefix)
lib_headers = ParseHeader.lib_headers

# Do some consistency checks.
print ("Consistency checks...")
# Create a class name -> class hash table.
defined_class_assocs = {}
for cls in classes:
  defined_class_assocs[cls.ClassName.lower()] = cls
using_relations = []
for child_str, parent_str in using_rel_strs:
  if not defined_class_assocs.has_key(child_str):
    raise Exception("During parsing, I determined that class %s is using " +\
     "class %s. However, class %s does not seem to be a library defined " +\
     "class. These using relations are determined just by the #include " +\
     "header names. If you are using an external header, simply blacklist " +\
     "it in the file CodeGenerator/SingleFileParser.py (list starting on " +\
     "line 46)." % (parent_str, child_str, child_str))
  if not defined_class_assocs.has_key(parent_str):
    raise Exception("During parsing, I determined that class %s is using " +\
     "class %s. However, class %s does not seem to be a library defined " +\
     "class. These using relations are determined just by the #include " +\
     "header names. If you are using an external header, simply blacklist " +\
     "it in the file CodeGenerator/SingleFileParser.py (list starting on " +\
     "line 46)." % (parent_str, child_str, parent_str))
  using_relations.append((defined_class_assocs[child_str],
                          defined_class_assocs[parent_str]))
# Parse inheritance.
inheritance_relations = []
for cls in classes:
  if not cls.Inherits is None and cls.Inherits != '':
    if not "<" in cls.Inherits:
      class_name = cls.Inherits.strip().lower()
    else:
      class_name = cls.Inherits[:cls.Inherits.index("<")].strip().lower()
    if class_name == 'std::exception':
      continue
    if defined_class_assocs.has_key(class_name):
      inheritance_relations.append((cls, defined_class_assocs[class_name]))
    else:
      raise Exception("No class names %s found, but required for inheritance!"\
        % (cls.Inherits))
print ("Created inheritance relations. Building inheritance graph...")
# Create a node for each class.
cls_nodes = dict()
for cls in classes:
  cls_nodes[cls] = Node(cls)
# Add the connections.
for rel in inheritance_relations:
  cls_nodes[rel[1]].add_incoming_from(cls_nodes[rel[0]])
# Assume correctness and do not search for loops!
# Order the nodes by depth.
depth_search_cls = classes[:]
depth_ordered_cls = []
depth = 0
while True:
  depth_ordered_cls.append([])
  for cls in depth_search_cls:
    if cls_nodes[cls].out_degree() == 0:
      depth_ordered_cls[depth].append(cls)
  assert len(depth_ordered_cls[-1]) != 0
  # Remove the classes from the 'todo list'.
  for cls in depth_ordered_cls[-1]:
    cls_nodes[cls].__del__()
    del cls_nodes[cls]
    depth_search_cls.remove(cls)
  if len(depth_search_cls) == 0:
    break
  depth += 1
for clslist in depth_ordered_cls:
  clslist.sort()
print ("Inheritance graph complete. Checking type availability...")
def parse_instantiations(relations):
  child_instantiation_sets = {}
  for (child, parent) in relations:
    if not parent.ClassType.TemplateParams is None and \
       len(parent.ClassType.TemplateParams) > 0:
      if not child_instantiation_sets.has_key(parent):
        child_instantiation_sets[parent] = set()
      child_inherits = child.Inherits.strip().replace(" ", "").replace("\r","").replace("\n","")
      child_inherits = child_inherits[child_inherits.index("<")+1:-1]
      tokens = ['']
      token_id = 0
      inside_count = 0
      for chr in child_inherits:
        if chr == ',' and inside_count == 0:
          tokens.append('')
          token_id += 1
          continue
        if chr == '<' or chr == '(':
          inside_count += 1
        if chr == '>' or chr == ')':
          inside_count -= 1
        tokens[token_id] += chr
      assert inside_count == 0, '%s could not be parsed.' % (child_inherits)
      if not child.SupportedTypes is None and len(child.SupportedTypes) > 0:
        for insttypes in child.SupportedTypes:
          tmp_tokens = tokens[:]
          for en_ind, token in enumerate(tmp_tokens):
            for child_ind, tparam in enumerate(child.ClassType.TemplateParams):
              if tparam in token:
                tmp_tokens[en_ind] = tmp_tokens[en_ind].replace(tparam, insttypes.Types[child_ind])
          try:
            child_instantiation_sets[parent].add(InstantiationTypes(tmp_tokens))
          except Exception as ex:
            print ("Exception parsing the template parameters for the " +\
                   child.ClassName + " - " + parent.ClassName + " relation")
            raise ex
      else:
        try:
          child_instantiation_sets[parent].add(InstantiationTypes(tokens))
        except Exception as ex:
          print ("Exception parsing the template parameters for the " +\
                 child.ClassName + " - " + parent.ClassName + " relation")
          raise ex
  return child_instantiation_sets

child_instantiation_sets = parse_instantiations(inheritance_relations)
for parent, inst_set in child_instantiation_sets.items():
  parent_set = set(parent.SupportedTypes)
  assert parent_set == inst_set, \
    "The sets of instantiation types for " + parent.ClassName + " and " +\
    "its inheritance children are unequal: " + str(parent_set) + \
    " (parent) " + str(inst_set) + " (children).\n\n" +\
    str(parent_set - inst_set) + " are only defined for the parent, while " +\
    str(inst_set - parent_set) + " are only defined for children."

def parse_using_instantiations(relations):
  child_instantiation_sets = {}
  exc = False
  for (child, parent) in relations:
    if child.ClassName == 'ThresholdDecider' and (parent.ClassName == 'DirectPatchDifferenceSurfCalculator' or parent.ClassName == 'DifferenceSurfaceCalculator') or\
       not parent.ExclusiveSoilUsage is None:
      continue
    if not parent.ClassType.TemplateParams is None and \
       len(parent.ClassType.TemplateParams) > 0:
      if not child_instantiation_sets.has_key(parent):
        child_instantiation_sets[parent] = set()
      tokens = child.ClassType.TemplateParams
      if not child.SupportedTypes is None and len(child.SupportedTypes) > 0:
        sel_par = []
        sel_ch = []
        for tokidx, token in enumerate(tokens):
          if token in parent.ClassType.TemplateParams:
            sel_ch.append(tokidx)
            sel_par.append(parent.ClassType.TemplateParams.index(token))
        assert len(sel_par) == len(sel_ch)
        if len(sel_par) == 0:
          continue
        for insttypes in child.SupportedTypes:
          projected = operator.itemgetter(*sel_ch)(insttypes.Types)
          par_proj = operator.itemgetter(*sel_par)
          if parent.SupportedTypes is None or \
             not projected in [par_proj(par_insttypes.Types) for par_insttypes in parent.SupportedTypes]:
            print ('%s using %s, and has instantiation %s, which is not present for parent!' \
                    % (child.ClassName, parent.ClassName, str(insttypes),))
            exc = True
  if exc:
    raise Exception("Errors validating relations: %s" % str(exc))
parse_using_instantiations(using_relations)
switched_using_relations = [(parent, child) for (parent, child) in using_relations]
parse_using_instantiations(switched_using_relations)

print("Patching ndarray...")
fileList = []
rootdir = os.path.abspath(os.path.join('..', 'fertilized', 'ndarray'))
for root, subFolders, files in os.walk(rootdir):
    for file in files:
        fileList.append(os.path.join(root,file))
fileList.append(os.path.join(rootdir, '..', 'ndarray_fwd.h'))
for file in fileList:
  # Read / patch.
  with open(file, 'r') as f:
    lines = [line for line in f]
    patched_lines = []
    for lineidx, line in enumerate(lines):
      line = line.replace('#include "ndarray/', '#include "fertilized/ndarray/')\
                 .replace('#include "ndarray.h"', '#include "fertilized/ndarray.h"')\
                 .replace('#include "ndarray_fwd.h"', '#include "fertilized/ndarray_fwd.h"')\
                 .replace('\\defgroup ', '')\
                 .replace('ingroup ndarrayMainGroup', 'ingroup ndarrayPackageGroup')\
                 .replace('ingroup ndarrayOpGroup', 'ingroup ndarrayPackageGroup')\
                 .replace('ingroup ndarrayVectorGroup', 'ingroup ndarrayPackageGroup')\
                 .replace('ingroup ndarrayInternalGroup', 'ingroup ndarrayPackageGroup')\
                 .replace('ingroup InternalGroup', 'ingroup ndarrayPackageGroup')\
                 .replace('ingroup MainGroup', 'ingroup ndarrayPackageGroup')\
                 .replace('addtogroup ndarrayOpGroup', 'addtogroup ndarrayPackageGroup')\
                 .replace('addtogroup ndarrayMainGroup', 'addtogroup ndarrayPackageGroup')\
                 .replace('addtogroup ndarrayVectorGroup', 'addtogroup ndarrayPackageGroup')\
                 .replace('addtogroup ndarrayInternalGroup', 'addtogroup ndarrayPackageGroup')\
                 .replace('addtogroup MainGroup', 'addtogroup ndarrayPackageGroup')\
                 .replace('@todo ', 'todo ')\
                 .replace('/todo ', 'todo ')
      if r'\defgroup ' in line and not 'ndarrayPackageGroup' in lines[lineidx+1]:
        patched_lines.append(line)
        patched_lines.append(line[:line.index('\\')] + '\\ingroup ndarrayPackageGroup%s' % (os.linesep))
      else:
        patched_lines.append(line)
  # Write.
  with open(file, 'w') as f:
    f.writelines(patched_lines)

print("Loading templates...")
# In this case, we will load templates off the filesystem.
# This means we must construct a FileSystemLoader object.
#
# The search path can be used to make finding templates by
#   relative paths much easier.  In this case, we are using
#   absolute paths and thus set it to the filesystem root.
currentDir = os.path.dirname(os.path.realpath(__file__));
templateLoader = jinja2.FileSystemLoader( searchpath=os.path.join(currentDir, 'templates'))

# An environment provides the data necessary to read and
#   parse our templates.  We pass in the loader object here.
templateEnv = jinja2.Environment( loader=templateLoader )

# redefine format function!
def myformat(value, *args):
    return value.format(*args)
templateEnv.filters['format'] = myformat

# remove new line whitespaces...
templateEnv.trim_blocks = True

# enable line statements := @ code instead of {% code %}
templateEnv.line_statement_prefix = '@'
templateEnv.line_comment_prefix = '##'

# Read the template file using the environment object.
# This also constructs our Template object.
header_tmpl = templateEnv.get_template("general_h.jinja")
cpp_tmpl = templateEnv.get_template("general_cpp.jinja")
function_header_tmpl = templateEnv.get_template("function_h.jinja")
function_cpp_tmpl = templateEnv.get_template("function_cpp.jinja")
matlab_fertilized_tmpl = templateEnv.get_template("matlab_fertilized.jinja")
soilm_tmpl = templateEnv.get_template("Soil_m.jinja")
matlabh_tmpl = templateEnv.get_template("matlab_h.jinja")
forward_tmpl = templateEnv.get_template("forward_declarations.jinja")
fertilized_h_tmpl = templateEnv.get_template("fertilized_h.jinja")
soil_cpp_tmpl = templateEnv.get_template("soil_cpp.jinja")
serialization_cpp_tmpl = templateEnv.get_template("serialization.jinja")
serialization_obj_cpp_h_tmpl = templateEnv.get_template("serialization_obj_cpp_h_tmpl.jinja")
serialization_obj_cpp_cpp_tmpl = templateEnv.get_template("serialization_obj_cpp_cpp_tmpl.jinja")
python_exporter_cpp_tmpl = templateEnv.get_template("python_exporter_cpp.jinja")
python_exporter_h_tmpl = templateEnv.get_template("python_exporter_h.jinja")
pyfertilized_cpp_tmpl = templateEnv.get_template("pyfertilized_cpp_tmpl.jinja")
python_export_module_functions_cpp_tmpl = templateEnv.get_template("python_export_module_functions_cpp.jinja")
python_soil_tmpl = templateEnv.get_template("python_soil_py.jinja")
array_exporter_tmpl = templateEnv.get_template("array_exporter_cpp.jinja")
tests_pickle_tmpl = templateEnv.get_template("tests_pickle.jinja")
python_export_module_functions_h_tmpl = templateEnv.get_template("export_module_functions_h.jinja")
vec_exporter_h_tmpl = templateEnv.get_template("vec_exporter_h.jinja")

print('Generating fertilized.h...')
templateVars = {"lib_headers" : lib_headers}
generated = fertilized_h_tmpl.render(templateVars)
with open(os.path.join('..', 'fertilized', 'fertilized.h'),'w') as fhfile:
  fhfile.write(generated)

print('Generating fertilized_fwd.h...')
templateVars = {"classes" : classes,
                "functions" : functions }
forwardText = forward_tmpl.render(templateVars)
with open(os.path.join('..','fertilized','fertilized_fwd.h'), 'w') as fwdfile:
  fwdfile.write(forwardText)

print('Generating soil.h...')
templateVars = {"classes" : classes,
                "functions" : functions }
generated = soil_cpp_tmpl.render(templateVars)
with open(os.path.join('..', 'fertilized', 'soil.h'), 'w') as soilfile:
  soilfile.write(generated)

print('Generating serialization classes...')
# Cleanup!
delfiles = glob.glob(os.path.join('..', 'fertilized', 'serialization', '__*'))
for delfile in delfiles:
    os.remove(delfile)
serialization_classes = [cls for cls in classes if cls.isSerializable()]
serialization_classes.sort(key=lambda x: (x.SerializationGeneration, \
                                          x.ClassName))
ser_insttypes_tpls = []
for cls in serialization_classes:
  if not cls.SupportedTypes is None:
    for insttypes in sorted(cls.SupportedTypes, key=lambda x: str(x)):
      ser_insttypes_tpls.append((cls, insttypes))
  else:
    ser_insttypes_tpls.append((cls, None))
for cls in serialization_classes:
  if not (cls.TemplatingString is None or \
           cls.TemplatingString == '') and \
     not cls.SupportedTypes is None and \
     len(cls.SupportedTypes) == 0:
    raise Exception("Class " + cls.ClassName + " is templated as " +\
                    cls.TemplatingString + " and " +\
                    "serializable, but has no specified supported types!")
templateVars = {"tplids" : xrange(len(ser_insttypes_tpls))}
generated = serialization_cpp_tmpl.render(templateVars)
with open(os.path.join('..',
                       'fertilized',
                       'serialization',
                       'serialization.cpp'), 'w') as serfile:
  serfile.write(generated)
for tplid, (cls, insttypes) in enumerate(ser_insttypes_tpls):
  templateVars = {"cls" : cls,
                  "insttypes": insttypes,
                  "tplid":tplid}
  generated = serialization_obj_cpp_cpp_tmpl.render(templateVars)
  with open(os.path.join('..',
                         'fertilized',
                         'serialization',
                         '__serialize_%d.cpp' % (tplid)), 'w') as serfile:
    serfile.write(generated)

print('Copying type translations...')
if not os.path.exists(os.path.join('..', 'pyfertilized', 'fertilized')):
    os.mkdir(os.path.join('..', 'pyfertilized', 'fertilized'))
shutil.copyfile('TypeTranslations.py', os.path.join('..',
                                                    'pyfertilized',
                                                    'fertilized',
                                                    'TypeTranslations.py'))

print('Generating python exporters...')
if not os.path.exists(os.path.join('..', 'pyfertilized', 'exporters')):
    os.mkdir(os.path.join('..', 'pyfertilized', 'exporters'))
else:
    # Cleanup!
    delfiles = glob.glob(os.path.join('..', 'pyfertilized', 'exporters', '__*'))
    for delfile in delfiles:
        os.remove(delfile)
python_exp_classes = [cls for cls in itertools.chain(*depth_ordered_cls) if 'Python' in cls.AvailableIn]
python_exp_functions = [func for func in functions if 'Python' in func.AvailableIn]
vec_types = set()
vec_headers = dict()
for func in python_exp_functions:
  func_vec_types = func.getVectorizedTypes('Python')
  for tp in func_vec_types:
    if not tp in vec_headers.keys():
      vec_headers[tp] = func.DefiningHeader
  vec_types.update(func_vec_types)
for cls in python_exp_classes:
  cls_vec_types = cls.getVectorizedTypes('Python')
  for tp in cls_vec_types:
    if not tp in vec_headers.keys():
      vec_headers[tp] = cls.DefiningHeader
  vec_types.update(cls_vec_types)
if 'uint' in vec_types:
  if 'fertilized::uint' in vec_types:
     vec_types.remove('uint')
func_inst_tpls = []
for func in python_exp_functions:
    if not func.SupportedTypes is None and not func.TemplateArguments is None and len(func.TemplateArguments) > 0:
        for insttypes in func.SupportedTypes:
            func_inst_tpls.append((func, insttypes))
    else:
        func_inst_tpls.append((func, None))
cls_inst_tpls = []
for cls in python_exp_classes:
    if not cls.SupportedTypes is None and not cls.TemplatingString is None and cls.TemplatingString != '':
        for insttypes in cls.SupportedTypes:
            cls_inst_tpls.append((cls, insttypes))
    else:
        cls_inst_tpls.append((cls, None))
pyfunc_export_dir = os.path.join('..', 'pyfertilized', 'exporters_mod_funcs')
templateVars = {"classes" : python_exp_classes,
                'nmfuncids':xrange(len(func_inst_tpls)),
                'tmplids':xrange(len(vec_types)),
                'clsids':xrange(len(cls_inst_tpls))}
generated = pyfertilized_cpp_tmpl.render(templateVars)
with open(os.path.join('..',
                       'pyfertilized',
                       'pyfertilized.cpp'), 'w') as expfile:
  expfile.write(generated)
# Cleanup!
delfiles = glob.glob(os.path.join('..', 'pyfertilized', 'exporters', '__*'))
for delfile in delfiles:
    os.remove(delfile)
for cls in python_exp_classes:
  templateVars = {"cls" : cls}
  generated = python_exporter_h_tmpl.render(templateVars)
  with open(os.path.join('..',
                         'pyfertilized',
                         'exporters',
                         '__%s_exporter.h' % (cls.ClassName)), 'w') as expfile:
    expfile.write(generated)
for clsid, (cls, insttypes) in enumerate(cls_inst_tpls):
  templateVars = {"cls" : cls,
                  "clsid" : clsid,
                  "insttypes" : insttypes}
  generated = python_exporter_cpp_tmpl.render(templateVars)
  with open(os.path.join('..',
                         'pyfertilized',
                         'exporters',
                         '__%d_exporter.cpp' % (clsid)), 'w') as expfile:
    expfile.write(generated)
if not os.path.exists(pyfunc_export_dir):
    os.mkdir(pyfunc_export_dir)
else:
    # Cleanup!
    delfiles = glob.glob(os.path.join(pyfunc_export_dir, '__*'))
    for delfile in delfiles:
        os.remove(delfile)
for func_ind, (func, insttp) in enumerate(func_inst_tpls):
    templateVars = {"func":func,
                    "header": func.DefiningHeader[3:].replace("/./", "/"),
                    "func_ind":func_ind,
                    "insttype":insttp}
    generated = python_export_module_functions_cpp_tmpl.render(templateVars)
    with open(os.path.join(pyfunc_export_dir, '__export_module_function_%d.cpp' % (func_ind)), 'w') as expfile:
      expfile.write(generated)
generated = python_export_module_functions_h_tmpl.render({'nmfuncids':xrange(len(func_inst_tpls))})
with open(os.path.join(pyfunc_export_dir, 'export_module_functions.h'), 'w') as expfile:
  expfile.write(generated)
templateVars = {"functions":python_exp_functions,
                "classes":python_exp_classes}
generated = python_soil_tmpl.render(templateVars)
with open(os.path.join('..',
                       'pyfertilized',
                       'fertilized',
                       '__init__.py'), 'w') as expfile:
  expfile.write(generated)
vec_export_dir = os.path.join('..', 'pyfertilized', 'exporters_vec_types')
if not os.path.exists(vec_export_dir):
  os.mkdir(vec_export_dir)
else:
    # Cleanup!
    delfiles = glob.glob(os.path.join(vec_export_dir, '__*'))
    for delfile in delfiles:
        os.remove(delfile)
for tpind, vec_type in enumerate(vec_types):
    generated = array_exporter_tmpl.render({'vec_type':vec_type,
                                            'tpind':tpind,
                                            'header':vec_headers[vec_type].replace('/./', '/').replace('../fertilized/', 'fertilized/')})
    with open(os.path.join(vec_export_dir,
                            '__vec_exporter_%d.cpp' % (tpind)), 'w') as expfile:
        expfile.write(generated)
generated = vec_exporter_h_tmpl.render({'tmplids':xrange(len(vec_types))})
with open(os.path.join(vec_export_dir,
                        'vec_exporter.h'), 'w') as expfile:
    expfile.write(generated)

generated = tests_pickle_tmpl.render({"classes" : python_exp_classes})
with open(os.path.join('..',
                       'pyfertilized',
                       'tests_pickle.py'), 'w') as expfile:
  expfile.write(generated)

print('Generating MATLAB interface...')
if not os.path.exists(os.path.join('..', 'matfertilized', 'exporters')):
    os.mkdir(os.path.join('..', 'matfertilized', 'exporters'))
else:
    # Cleanup!
    delfiles = glob.glob(os.path.join('..', 'matfertilized', 'exporters', '__*'))
    for delfile in delfiles:
        os.remove(delfile)
if not os.path.exists(os.path.join('..', 'matfertilized', 'fertilized', 'generated')):
    os.mkdir(os.path.join('..', 'matfertilized', 'fertilized', 'generated'))
else:
    # Cleanup!
    delfiles = glob.glob(os.path.join('..', 'matfertilized', 'fertilized', 'generated', '*'))
    for delfile in delfiles:
        os.remove(delfile)
if os.name == 'nt':
    export_macro = 'DllExport'
else:
    export_macro = ''
matlab_exp_classes = [cls for cls in classes if 'Matlab' in cls.AvailableIn]
matlab_exp_functions = [func for func in functions if 'Matlab' in func.AvailableIn]
matlab_header_files = []
classesGrouped = sorted((s for s in matlab_exp_classes), key=operator.attrgetter('Package'))
for key, group in itertools.groupby(classesGrouped, key=operator.attrgetter('Package')):
    # Specify any input variables to the template as a dictionary.
    grouplist = list(group)
    templateVars = { "classes" : grouplist,
                     "package" : key,
                     "export_macro" : export_macro}
    try:
      # Finally, process the template to produce our final text.
      outputText = header_tmpl.render( templateVars )
      with open(os.path.join('..', 'matfertilized', 'matlab_headers', '__' + key + '.h'), 'w') as f:
          f.write(outputText)
      matlab_header_files.append('__' + key + '.h')
    except Exception as ex:
      print('Exception rendering __%s.h: %s' % (key, str(ex)))
      ex_type, ex, tb = sys.exc_info()
      traceback.print_tb(tb)
      del tb
      sys.exit(1)
    for cls in grouplist:
      templateVars = {'cls':cls, 'classes':grouplist, 'package':key}
      outputText = matlab_fertilized_tmpl.render(templateVars)
      with open(os.path.join('..', 'matfertilized', 'fertilized', 'generated', cls.ClassName + '.m'), 'w') as f:
        f.write(outputText)
      if cls.ClassType.TemplateParams is None or len(cls.ClassType.TemplateParams) == 0:
        try:
          templateVars = {'class':cls, 'instantiation_types':None, 'classes':grouplist, 'package':key}
          outputText = cpp_tmpl.render( templateVars )
          with open(os.path.join('..', 'matfertilized', 'exporters', '__' + cls.ClassName + '.cpp'), 'w') as f:
            f.write(outputText)
        except Exception as ex:
          print('Exception rendering __%s.cpp: %s' % (cls.ClassName, str(ex)))
      else:
        inst_counter = 0
        for instantiation_types in cls.SupportedTypes:
          try:
            templateVars = {'class':cls, 'instantiation_types':instantiation_types, 'classes':grouplist, 'package':key}
            outputText = cpp_tmpl.render( templateVars )
            with open(os.path.join('..', 'matfertilized', 'exporters', '__' + cls.ClassName + '_' + str(inst_counter) + '.cpp'), 'w') as f:
              f.write(outputText)
          except Exception as ex:
            print('Exception rendering __%s_%d.cpp: %s' % (cls.ClassName, inst_counter, str(ex)))
            ex_type, ex, tb = sys.exc_info()
            traceback.print_tb(tb)
            del tb
            sys.exit(1)
          inst_counter += 1

# create functions (which are not inside of classes...)
fcsGrouped = sorted((s for s in matlab_exp_functions), key=operator.attrgetter('DefiningHeader'))
for key, group in itertools.groupby(fcsGrouped, key=operator.attrgetter('DefiningHeader')):
    # Specify any input variables to the template as a dictionary.
    pkg = basename(os.path.splitext(key)[0])
    function_list = list(group)
    templateVars = { "functions" : function_list,
                     "package" : pkg,
                     "export_macro" : export_macro }   
    try:
      # Finally, process the template to produce our final text.
      outputText = function_header_tmpl.render( templateVars )
      with open(os.path.join('..', 'matfertilized', 'matlab_headers', '__functions_' + pkg + '.h'), 'w') as f:
        f.write(outputText)
      matlab_header_files.append('__functions_' + pkg + '.h')
    except Exception as ex:
      print('Exception rendering %s.h: %s' % (pkg, str(ex)))
      ex_type, ex, tb = sys.exc_info()
      traceback.print_tb(tb)
      del tb
      sys.exit(1)
    # Finally, process the template to produce our final text.
    funcidx = 0
    for func in function_list:
      try:
        templateVars = dict(templateVars, **{'m':func})
        outputText = function_cpp_tmpl.render( templateVars )
        with open(os.path.join('..', 'matfertilized', 'exporters', '__functions_' + pkg + '_' + str(funcidx) + '.cpp'), 'w') as f:
          f.write(outputText)
      except Exception as ex:
        print('Exception rendering %s.cpp: %s' % (pkg, str(ex)))
      funcidx += 1

# get all packages and get a distinct list of them...
packages = sorted(s.Package for s in classes)
packages = list(set(packages))

# Specify any input variables to the template as a dictionary.
tmpl_soil_transl = {'input_dtype':'inp_str',
                    'feature_dtype':'feat_str',
                    'annotation_dtype':'ann_str',
                    'leaf_return_dtype':'tres',
                    'forest_return_dtype':'fres'}
templateVars = { "classes" : matlab_exp_classes,
                 "functions" : matlab_exp_functions,
                 "packages" : packages,
                 "translations" : _dtype_str_translation,
                 "matlab_header_files" : matlab_header_files,
                 "tmpl_soil_transl" : tmpl_soil_transl } 

if os.name != 'nt':
    nonmsvc_suffix = '-nonmsvc'
else:
    nonmsvc_suffix = ''
templateVars['nonmsvc_suffix'] = nonmsvc_suffix
# Render overall matlab include file
outputText = matlabh_tmpl.render( templateVars )
with open(os.path.join('..', 'matfertilized', 'matlab_headers', 'matlab.h'), 'w') as f:
    f.write(outputText)

# Generate matlab soil class, to easily call the library's functionos
outputText = soilm_tmpl.render( templateVars )
with open(os.path.join('..', 'matfertilized', 'fertilized', 'Soil.m'), 'w') as f:
    f.write(outputText)

print('Rendering complete.')
