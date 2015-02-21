# -*- python -*-
# Author: Christoph Lassner.
import os
import platform
Import("env", "lib", "lib_lnk")

# Create a temporary environment to be able to modify it locally.
matfertilized_lib_env = env.Clone()
if matfertilized_lib_env['CC'] == 'cl':
  matfertilized_lib_env.AppendUnique(CPPFLAGS='/W3')
# Link statically against the C++ runtime to avoid problems with
# MATLAB.
matfertilized_lib_env.AppendUnique(LINKFLAGS=['-static-libstdc++'])

# Copy the library files to the matfertilized directory for linking.
lib_rt = matfertilized_lib_env.Install(Dir('./fertilized').srcnode(), lib[0])
# Enable same directory search path for platform independent library layout.
if matfertilized_lib_env['CC'] not in ['cl', 'icl'] and os.name != 'nt':
  matfertilized_lib_env.Append(LINKFLAGS = Split('-z origin') )
  matfertilized_lib_env.Append(RPATH = env.Literal(os.path.join('\\$$ORIGIN')))
# Add dependencies.
matfertilized_lib_env.AppendUnique(LIBS=[lib_lnk])
matfertilized_lib_env.AppendUnique(LIBPATH=[os.path.dirname(lib_lnk.abspath)])
matfertilized_lib_env.AppendUnique(CPPDEFINES=['__BUILD_MATFERTILIZED_LIBRARY'])
# Create the build file list.
file_list = Glob('exporters/*.cpp') + Glob('ObjectVector.cpp') + Glob('StringVector.cpp')

# The library.
matlib = matfertilized_lib_env.SharedLibrary('matfertilized', file_list)
matheaders = Glob('matlab_headers/*.h')
# Install.
lib_ext = os.path.splitext(str(matlib[0]))[1]

lib_file = matfertilized_lib_env.Command(os.path.join(Dir('.').srcnode().abspath,
                                                     'fertilized',
                                                     'matfertilized') + lib_ext,
                                        matlib[0],
                                        Copy("$TARGET", "$SOURCE"))
matfertilized_lib_env.Install(Dir('./fertilized/headers').srcnode(), matheaders)
# Binary dependencies.
if os.name == 'nt':
  if os.path.exists(Dir('#bindep').abspath):
    bindeps = Glob(os.path.join(Dir('#bindep').abspath, '*'))
    for bindep in bindeps:
      env.InstallAs(os.path.join(Dir('#matfertilized/fertilized').abspath, os.path.basename(bindep.abspath)), bindep)
Return("lib_file")
