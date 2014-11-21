# -*- python -*-
# Author: Christoph Lassner.
import os
Import(["env"])

# Create a temporary environment to be able to modify it locally.
fertilized_lib_env = env.Clone()
# Activate symbol exporting.
fertilized_lib_env.AppendUnique(CPPDEFINES='__BUILD_FERTILIZED_LIBRARY')
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
# The library.
lib_file = fertilized_lib_env.SharedLibrary('fertilized', file_list)
Return("lib_file", "headers")
