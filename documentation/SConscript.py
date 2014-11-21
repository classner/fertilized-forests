# -*- python -*-

# Copyright 2014 Christoph Lassner
import os
import subprocess
Import(["env"])

# Replace the page tags in 'ndarray.h' to avoid collision with the
# main page.
lines = []
with open(os.path.join(Dir('#').abspath,
                       'fertilized',
                       'ndarray.h'), 'r') as docfile:
  omitting = False
  omitting_environment = False
  for line in docfile:
    if line.startswith(" * @page ndarrayMain"):
      omitting = True
      lines = lines[:-1]
    if line.startswith(" * @section environment Environment"):
      omitting_environment = True
    if not omitting and not omitting_environment:
      lines.append(line.replace(r'@page ndarrayTutorial Tutorial', r'@page ndarrayTutorial Multidimensional Arrays Tutorial (ndarray)'))
    elif line.strip().endswith('*/'):
      omitting = False
    elif line.startswith(" * @section construction Creating New Arrays"):
      omitting_environment = False
with open(os.path.join(Dir('#').abspath,
                       'fertilized',
                       'ndarray.h'), 'w') as docfile:
  docfile.writelines(lines)
 # Set the version number in the doxyfile.
lines = []
with open('Doxyfile', 'r') as docfile:
  for line in docfile:
    lines.append(line)
lines[40] =  'PROJECT_NUMBER         = %s%s' % (env['VERSION_STRING'], os.linesep)
with open('Doxyfile', 'w') as docfile:
  docfile.writelines(lines)

subprocess.check_call([env['DOXY_EXEC'], "Doxyfile"])
