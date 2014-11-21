# -*- python -*-
# Copyright 2014 Christoph Lassner, University of Augsburg.
import os
Import("env", 'lib', 'lib_lnk')

# Create a temporary environment to be able to modify it locally.
fertilized_presentation_env = env.Clone()

# Install the main library to this folder for cross platform easy access.
lib_rt = fertilized_presentation_env.Install(Dir('C++').srcnode(), lib[0])
# Enable same directory search path for platform independent library layout.
if fertilized_presentation_env['CC'] not in ['cl', 'icl'] and os.name != 'nt':
  fertilized_presentation_env.Append(LINKFLAGS = Split('-z origin'))
  fertilized_presentation_env.Append(RPATH = env.Literal(os.path.join('\\$$ORIGIN')))
if fertilized_presentation_env['CC'] == 'cl':
  # Set warning level to 3 (highest, before all warnings).
  fertilized_presentation_env.AppendUnique(CPPFLAGS='/W3')
# Setup.
fertilized_presentation_env.AppendUnique(LIBPATH=[os.path.dirname(lib_lnk.abspath)])
fertilized_presentation_env.AppendUnique(LIBS=lib_lnk)
# Create the build file list.
file_list = Glob('C++/*.cpp')
executables = []
for file in file_list:
  # The library.
  executable = fertilized_presentation_env.Program(file)
  executable = fertilized_presentation_env.Install(Dir('C++').srcnode(), executable)
  executables.append(executable)
# Binary dependencies.
if os.name == 'nt':
  if os.path.exists(Dir('#bindep').abspath):
    bindeps = Glob(os.path.join(Dir('#bindep').abspath, '*'))
    for bindep in bindeps:
      env.InstallAs(os.path.join(Dir('#Presentation/C++').abspath, os.path.basename(bindep.abspath)), bindep)
# Cleanup.
Return("executables")