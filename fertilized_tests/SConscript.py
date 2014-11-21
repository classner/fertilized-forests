# -*- python -*-
# Author: Christoph Lassner.
import os
Import("env", 'lib', 'lib_lnk')

# Create a temporary environment to be able to modify it locally.
fertilized_tests_env = env.Clone()

# Install the main library to this folder for cross platform easy access.
lib_rt = fertilized_tests_env.Install(Dir('.').srcnode(), lib[0])
# Enable same directory search path for platform independent library layout.
if fertilized_tests_env['CC'] not in ['cl', 'icl'] and os.name != 'nt':
  fertilized_tests_env.Append(LINKFLAGS = Split('-z origin'))
  fertilized_tests_env.Append(RPATH = env.Literal(os.path.join('\\$$ORIGIN')))
if fertilized_tests_env['CC'] == 'cl':
  # Set warning level to 3 (highest, before all warnings).
  fertilized_tests_env.AppendUnique(CPPFLAGS='/W3')
# Setup.
fertilized_tests_env.AppendUnique(CPPDEFINES=['BOOST_TEST_DYN_LINK'])
fertilized_tests_env.AppendUnique(LIBPATH=[os.path.dirname(lib_lnk.abspath)])
fertilized_tests_env.AppendUnique(LIBS=lib_lnk)
# Create the build file list.
file_list = Glob('*.cpp')
headers = Glob('*.h')
# The library.
tests_executable = fertilized_tests_env.Program('fertilized_tests', file_list)
tests_executable = fertilized_tests_env.Install(Dir('.').srcnode(), tests_executable)
# Binary dependencies.
if os.name == 'nt':
  if os.path.exists(Dir('#bindep').abspath):
    bindeps = Glob(os.path.join(Dir('#bindep').abspath, '*'))
    for bindep in bindeps:
      env.InstallAs(os.path.join(Dir('#fertilized_tests').abspath, os.path.basename(bindep.abspath)), bindep)
# Cleanup.
Return("tests_executable")