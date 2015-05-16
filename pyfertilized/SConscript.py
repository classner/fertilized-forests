# -*- python -*-
# Author: Christoph Lassner.
import os
import platform
Import("env", "bn_module", "lib", 'PY_SUFFIX', 'lib_lnk')

# Create a temporary environment to be able to modify it locally.
pyfertilized_lib_env = env.Clone()
if pyfertilized_lib_env['CC'] == 'cl':
  pyfertilized_lib_env.AppendUnique(CPPFLAGS='/W3')

# Copy the library files to the pyfertilized directory for linking.
bn_link = bn_module[0]
bn_link = pyfertilized_lib_env.Install('#', bn_link)[0]
bn_rt = pyfertilized_lib_env.Install(Dir('./fertilized').srcnode(), bn_module[0])
lib_rt = pyfertilized_lib_env.Install(Dir('./fertilized').srcnode(), lib[0])
# Enable same directory search path for platform independent library layout.
if pyfertilized_lib_env['CC'] not in ['cl', 'icl'] and os.name != 'nt':
  pyfertilized_lib_env.Append(LINKFLAGS = Split('-z origin') )
  pyfertilized_lib_env.Append(RPATH = env.Literal(os.path.join('\\$$ORIGIN')))
# Add dependencies.
pyfertilized_lib_env.AppendUnique(LIBS=[lib_lnk, bn_link])
pyfertilized_lib_env.AppendUnique(LIBPATH=[os.path.dirname(lib_lnk.abspath)])
# Create the build file list.
file_list = Glob('pyfertilized.cpp') + \
            Glob('./exporters/*.cpp') + \
            Glob('./exporters_vec_types/*.cpp')
file_list_mf = Glob('pyfertilized_mf.cpp') + \
               Glob('./exporters_mod_funcs/*.cpp') + \
               Glob('./exporters_vec_types/*.cpp')
# The libraries.
pylib = pyfertilized_lib_env.SharedLibrary('pyfertilized', file_list)
pylib_mf = pyfertilized_lib_env.SharedLibrary('pyfertilized_mf', file_list_mf)
# Install.
lib_file = pyfertilized_lib_env.Command(os.path.join(Dir('.').srcnode().abspath,
                                                     'fertilized',
                                                     'pyfertilized') + PY_SUFFIX,
                                        pylib[0],
                                        Copy("$TARGET", "$SOURCE"))
lib_file_mf = pyfertilized_lib_env.Command(os.path.join(Dir('.').srcnode().abspath,
                                                        'fertilized',
                                                        'pyfertilized_mf') + PY_SUFFIX,
                                           pylib_mf[0],
                                           Copy("$TARGET", "$SOURCE"))
# Binary dependencies.
if os.name == 'nt':
  if os.path.exists(Dir('#bindep').abspath):
    bindeps = Glob(os.path.join(Dir('#bindep').abspath, '*'))
    for bindep in bindeps:
      env.InstallAs(os.path.join(Dir('#pyfertilized/fertilized').abspath, os.path.basename(bindep.abspath)), bindep)
Return("lib_file", "lib_file_mf")

