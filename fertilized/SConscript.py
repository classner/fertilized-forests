# -*- python -*-
# Author: Christoph Lassner.
import os
Import(["env", 'caffe_headers', 'caffe_core_objects', 'caffe_link_libs'])

# Create a temporary environment to be able to modify it locally.
fertilized_lib_env = env.Clone()
# Activate symbol exporting.
fertilized_lib_env.AppendUnique(CPPDEFINES='__BUILD_FERTILIZED_LIBRARY')
if GetOption('with_caffe'):
    # Add caffe libraries.
    fertilized_lib_env.AppendUnique(LIBS=caffe_link_libs)
    # Add caffe include path.
    fertilized_lib_env.PrependUnique(CPPPATH=[Dir('#external/caffe-brewer/include').abspath])
    if os.name == 'nt':
      fertilized_lib_env.PrependUnique(CPPPATH=[Dir('#external/caffe-brewer/dependencies/gflags-2.1.1/include').abspath])
      fertilized_lib_env.PrependUnique(CPPPATH=[Dir('#external/caffe-brewer/dependencies/glog-0.3.3/src/windows').abspath])
      fertilized_lib_env.PrependUnique(CPPDEFINES=['GOOGLE_GLOG_DLL_DECL='])
    else:
      fertilized_lib_env.PrependUnique(CPPPATH=[Dir('#external/caffe-brewer/dependencies/gflags-2.1.1-linux/include').abspath])
    fertilized_lib_env.PrependUnique(CPPPATH=[Dir('#external/caffe-brewer/dependencies/leveldb/include').abspath])
    fertilized_lib_env.PrependUnique(CPPPATH=[Dir('#external/caffe-brewer/dependencies/mdb/libraries/liblmdb').abspath])
    if GetOption('cpu_only'):
      fertilized_lib_env.AppendUnique(CPPDEFINES=['CPU_ONLY'])
    fertilized_lib_env['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME']=1
if fertilized_lib_env['CC'] == 'cl':
  # Set warning level to 3 (highest, before all warnings).
  fertilized_lib_env.AppendUnique(CPPFLAGS='/W3')
# Create the build file list.
file_list = Glob('util/*.cpp') +\
            Glob('feature_extraction/*.cpp') + \
            Glob('feature_extraction/hog/*.cpp') + \
            Glob('serialization/*.cpp')
headers = Glob('*.h') + Glob('*.hpp') + \
          Glob('*/*.h') + Glob('*/*.hpp') + \
          Glob('*/*/*.h') + Glob('*/*/*.hpp') + \
          Glob('*/*/*/*.h') + Glob('*/*/*/*.hpp') + \
          Glob('*/*/*/*/*.h') + Glob('*/*/*/*/*.hpp')
# Build the object files.
fertilized_objects = []
for ffile in file_list:
  fertilized_objects.append(fertilized_lib_env.SharedObject(ffile))
# The library.
lib_file = fertilized_lib_env.SharedLibrary('fertilized', fertilized_objects + caffe_core_objects)
# Add dependency to caffe.
Depends(lib_file, caffe_headers)
Return("lib_file", "headers")
