# -*- python -*-
# Author: Christoph Lassner.
from SConsChecks import GetLibChecks
import os

# Get the general build environment options and methods.
setupOptions, makeEnvironment, setupTargets, checks, getRequiredLibs = \
  SConscript("SConscript.py", variant_dir='build')
caffeSetupOptions, caffeMakeEnvironment, caffeSetupTargets, \
caffeChecks, caffeGetRequiredLibs = SConscript(
  os.path.join("external", "caffe-brewer", "SConscript.py"),
               variant_dir='build/caffe')

# Prepare the command line options.
variables = setupOptions()
caffeVariables = caffeSetupOptions(rpath=False, python=False, tools=True, libs=False, debug=False, tests=False)

# Create the build environment.
env = makeEnvironment(variables)
if GetOption("with_caffe"):
    caffe_env = caffeMakeEnvironment(caffeVariables, root='external/caffe-brewer')

# The root path must be added, since the fertilized headers are
# referenced.
env.AppendUnique(CPPPATH=[Dir("#").abspath])

# Only take actions if neither help nor clean is specified.
if not GetOption("help") and not GetOption("clean"):
    config = env.Configure(custom_tests=checks)
    checknames = GetLibChecks(getRequiredLibs()).keys()
    if False in (config.__dict__[checkname]() for checkname in checknames):
        Exit(1)
    env = config.Finish()
    # If necessary, configure caffe build environment.
    if GetOption("with_caffe"):
        caffe_config = caffe_env.Configure(custom_tests=checks)
        caffe_checknames = GetLibChecks(caffeGetRequiredLibs()).keys()
        if False in (caffe_config.__dict__[checkname]() for checkname in caffe_checknames):
            Exit(1)
        caffe_env = caffe_config.Finish()

if GetOption("with_caffe"):
    caffe_headers, caffe_core_objects, caffe_link_libs = caffeSetupTargets(caffe_env, root='external/caffe-brewer')
else:
    caffe_headers = []
    caffe_core_objects = []
    caffe_link_libs = []
# The targets must be created in any case (remember, the 'clean' option
# need to know about them).
setupTargets(env, '.', caffe_headers, caffe_core_objects, caffe_link_libs)
