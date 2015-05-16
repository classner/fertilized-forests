# -*- python -*-
# Author: Christoph Lassner.

import os
import sys
import platform
import sysconfig
import subprocess
import shutil
import urllib
import time
from SConsChecks import AddLibOptions, GetLibChecks
from version import VERSION as VERSION_STRING

_caffeSetupOptions, _caffeMakeEnvironment, _caffeSetupTargets, \
_caffeChecks, _caffeGetRequiredLibs = SConscript(
  os.path.join("external", "caffe-brewer", "SConscript.py"),
               variant_dir='build/caffe')

_libs = ['boost.datetime',
         'boost.filesystem',
         'boost.interprocess',
         'boost.numpy',
         'boost.preprocessor',
         'boost.python',
         'boost.serialization',
         'boost.system',
         'boost.test',
         'boost.thread',
         'cuda',
         'eigen',
         'hdf5',
         'numpy',
         'matlab',
         'openblas',
         'opencv',
         'protobuf',
         'python']

_checks = GetLibChecks(_libs)

def getRequiredLibs():
  if not (GetOption('generate_interfaces') or \
          GetOption('generate_ndarray') or \
          GetOption('generate_documentation')):
    req_libs = ['boost.preprocessor', 'eigen', 'opencv']
    if GetOption('serialization_enabled'):
      req_libs.append('boost.serialization')
    if GetOption('with_python') or GetOption("python_support"):
      req_libs.extend(['python',
                       'numpy',
                       'boost.python',
                       'boost.thread'])
    if GetOption('with_tests'):
      req_libs.append('boost.test')
    if GetOption('with_matlab'):
      req_libs.append('matlab')
    if GetOption('with_caffe'):
      req_libs.extend(['boost.datetime',
                       'boost.system',
                       'boost.filesystem',
                       'boost.thread',
                       'hdf5',
                       'openblas',
                       'protobuf'])
      if not GetOption('cpu_only'):
        req_libs.append('cuda')
  else:
    req_libs = []
  return req_libs

####################################
# Command line length fix for compilers other than MSVC on Windows.
# http://scons.org/wiki/LongCmdLinesOnWin32
if os.name == 'nt':
    import win32file
    import win32event
    import win32process    
    import win32security
    def my_spawn(sh, escape, cmd, args, spawnenv):
        for var in spawnenv:
            spawnenv[var] = spawnenv[var].encode('ascii', 'replace')
        sAttrs = win32security.SECURITY_ATTRIBUTES()
        StartupInfo = win32process.STARTUPINFO()
        newargs = ' '.join(map(escape, args[1:]))
        cmdline = cmd + " " + newargs
        # check for any special operating system commands
        if cmd == 'del':
            for arg in args[1:]:
                win32file.DeleteFile(arg)
            exit_code = 0
        else:
            # otherwise execute the command.
            hProcess, hThread, dwPid, dwTid = win32process.CreateProcess(None, cmdline, None, None, 1, 0, spawnenv, None, StartupInfo)
            win32event.WaitForSingleObject(hProcess, win32event.INFINITE)
            exit_code = win32process.GetExitCodeProcess(hProcess)
            win32file.CloseHandle(hProcess);
            win32file.CloseHandle(hThread);
        return exit_code

def SetupSpawn( env ):
    if env['CXX'].startswith('g++') and sys.platform == 'win32':
        # Enable workaround for handling of extralong
        # command lines. This is not handled by the
        # default toolchain spawner of SCons in this
        # case.
        env['SPAWN'] = my_spawn
#####################################

# Setup command-line options
def setupOptions():
    default_toolchain = 'default'
    if platform.system() == 'Windows':
        default_prefix = r'C:\Libraries'
    else:
        default_prefix = "/usr/local"
    AddOption("--prefix-dir", dest="prefix", type="string", nargs=1, action="store",
              metavar="DIR", default=default_prefix, help="installation prefix")
    AddOption("--install-headers-dir", dest="install_headers", type="string", nargs=1, action="store",
              metavar="DIR", help="location to install header files (overrides --prefix for headers)")
    AddOption("--install-lib-dir", dest="install_lib", type="string", nargs=1, action="store",
              metavar="DIR", help="location to install libraries (overrides --prefix for libraries)")
    AddOption("--with-serialization", dest="serialization_enabled",
              action="store_true", help="enable serialization (requires boost serialization)",
              default=False)
    AddOption("--with-checks", dest="debug_checks", action="store_true",
              default=False, help="enable debug assertions and checks")
    AddOption("--disable-optimizations", dest="debug_build", action="store_true",
              default=False, help="disable optimizations")
    AddOption("--generate-ndarray", dest="generate_ndarray", action="store_true",
              default=False, help="generate the ndarray code. Requires m4!")
    AddOption("--generate-interfaces", dest="generate_interfaces", action="store_true",
              default=False, help="generate the Python and Matlab interface code.")
    AddOption("--generate-documentation", dest="generate_documentation", action="store_true",
              default=False, help="generate the doxygen documentation.")
    AddOption("--with-python", dest="with_python",
              action="store_true", help="enables building the python library",
              default=False)
    AddOption("--with-python-support", dest="python_support",
              action="store_true", help="enables building python supporting "
              "elements in the core library. Is auto-enabled if option "
              "--with-python is set.", default=False),
    AddOption("--with-tests", dest="with_tests",
              action="store_true", help="enables building the test suite",
              default=False)
    AddOption("--with-matlab", dest="with_matlab",
              action="store_true", help="enables building the matlab interface",
              default=False)
    AddOption("--with-examples", dest="with_examples",
              action="store_true", help="enables building the examples (you can find them in the Presentation folder)",
              default=False)
    AddOption("--with-caffe", dest="with_caffe",
              action="store_true", help="enables caffe feature extraction. Adds additional dependencies and restricts the license to non-commercial use!",
              default=False)
    AddOption("--caffe-model-dir", dest="caffe_model_dir",
              action="store", help="the directory in which caffe models for the caffe feature extraction are stored",
              default="")
    AddOption("--disable-openmp", dest="with_openmp",
              action="store_false", help="disables OpenMP. Disables parallel execution.",
              default=True)
    AddOption("--toolchain", dest="toolchain",
              action="store", metavar="NAME", help="toolchain to use for the build. Supported: msvc (Microsoft compiler), icl (Intel compiler), g++ (GNU compiler)",
              default=default_toolchain)
    AddOption("--rpath", dest="custom_rpath", type="string", action="store",
              help="runtime link paths to add to libraries and executables (unix); may be passed more than once")
    AddOption("--doxygen-command", dest="doxy_exec", type="string", action="store",
              help="doxygen binary to execute for building the documentation. Default: doxygen",
              default="doxygen")
    # Add library configuration options.
    AddLibOptions(AddOption, _libs)
    # Default variables.
    variables = Variables()
    # Enable optimization, building of debug symbols.
    flags_default =  "-O2"
    if os.name == 'nt':
      flags_default = "/O2"
    variables.Add("CCFLAGS", default=os.environ.get("CCFLAGS", flags_default), help="compiler flags")
    return variables

def makeEnvironment(variables):
    shellEnv = {}
    # Some of these don't make sense on Windows, but don't hurt.
    for key in ("CXX", "CC", "PATH", "LD_LIBRARY_PATH", "DYLD_LIBRARY_PATH", "PYTHONPATH"):
        if key in os.environ:
            shellEnv[key] = os.environ[key]
    # Create build enviromnent.
    env = Environment(tools=['default', GetOption("toolchain"), 'm4'], variables=variables, ENV=shellEnv)
    if "CXX" in os.environ:
	env["CXX"] = os.environ["CXX"]
    if "CC" in os.environ:
        env["CC"] = os.environ["CC"]
    print "Using CXX: %s, CC: %s" % (env["CXX"], env["CC"]) 
    #SetupSpawn(env)
    if GetOption("with_caffe") and not GetOption("cpu_only"):
        env.Tool('nvcc')
    # Append environment compiler flags.
    if env.Dictionary().has_key("CCFLAGS"):
        if isinstance(env['CCFLAGS'], basestring):
            env['CCFLAGS'] = env['CCFLAGS'].split()
    if os.environ.has_key("CCFLAGS"):
        env.AppendUnique(CCFLAGS=os.environ.get("CCFLAGS").split())
    # Specifics for MSVC.
    if env['CC'] == 'cl' or env['CC'] == 'icl' and os.name == 'nt':
        # Enable C++ exception handling.
        env.Append(CCFLAGS=['/EHsc'])
        # Enable .dll and .exe builds without GUI.
        env.AppendUnique(LINKFLAGS=['/SUBSYSTEM:CONSOLE'])
        # Linker debug symbol generation, link time code generation.
        env.AppendUnique(LINKFLAGS=["/DEBUG", "/LTCG"])
        # Enable whole program optimization.
        env.AppendUnique(CCFLAGS=['/GL'])
        if GetOption("with_openmp"):
            # Enable OpenMP.
            env.AppendUnique(CPPFLAGS=['/openmp'])
        # Suppress Microsoft disclaimer display on console.
        env.AppendUnique(CPPFLAGS=['/nologo'])
        # Each object has its own pdb, so -jN works
        env.AppendUnique(CCFLAGS=["/Zi", "/Fd${TARGET}.pdb"])
    # Specifics for icl.
    if env['CC'] == 'icl':
        # 3199: triggered in boost serialization
        # 2586: decorated name length exceeded
        # 11081: Python on Windows tries to link via a pragma comment, but 
        #        the library is linked explicitely.
        env.AppendUnique(CCFLAGS=['-wd3199,2586,11081'])
        # Replace /GL with /Qipo-jobs4, which is a speeded up version.
        #env.Replace(CCFLAGS=[flag for flag in env['CCFLAGS'] if flag not in ['/GL']])
        #env.AppendUnique(CCFLAGS=['/Qipo-jobs4'])
    # Specifics for gcc.
    if env['CXX'].startswith('g++') or env['CC'] == 'gcc':
        # Replace default /O2 on Windows if MinGW is used.
        if '/O2' in env['CCFLAGS']:
          env.Replace(CCFLAGS=[flag for flag in env['CCFLAGS'] \
            if flag not in ['/O2']] + ['-O2'])
        # Enable C++ 11 support, OpenMP, and generation of debug symbols.
        env.AppendUnique(CCFLAGS=['-std=c++11', '-g'])
        env.AppendUnique(LINKFLAGS=['-g'])
        if GetOption("with_openmp"):
          env.AppendUnique(CCFLAGS=['-fopenmp'])
          env.AppendUnique(LINKFLAGS=['-fopenmp'])
    if os.name != 'nt':
        # RPATH.
        custom_rpath = GetOption("custom_rpath")
        if custom_rpath is not None:
            env.AppendUnique(RPATH=custom_rpath)
    # Parse options.
    env['SERIALIZATION_ENABLED'] = GetOption('serialization_enabled')
    if GetOption('serialization_enabled'):
        env.AppendUnique(CPPDEFINES=['SERIALIZATION_ENABLED'])
    if GetOption('with_caffe'):
        env.AppendUnique(CPPDEFINES=['CAFFE_FEATURE_EXTRACTION_ENABLED'])
        if GetOption('cpu_only'):
            env.AppendUnique(CPPDEFINES=['CAFFE_CPU_ONLY'])
    env['DEBUG_CHECKS'] = GetOption('debug_checks')
    env['VARIANT_DIR_PREF'] = 'debug' if GetOption('debug_build') else 'release'
    if GetOption('debug_build'):
        # Remove Optimization flags.
        debug_mode_flag = '/Od' if env['CC'] == 'cl' else "-Og"
        env.Replace(CCFLAGS=[flag for flag in env['CCFLAGS'] \
             if flag not in ['-O2', '-O3', '-Ox', '/O2', '/O3']] +\
          [debug_mode_flag])
        if env['CC'] != 'cl' or env['CC'] == 'icl' and os.name == 'nt':
            # Generate position-independent code to ease template debugging.
            env.AppendUnique(CPPFLAGS=['-fPIC'])
        else:
            # Link against debug system libraries.
            env.AppendUnique(CPPDEFINES=['_DEBUG', '_SCL_SECURE_NO_WARNINGS'])
            env.Append(CCFLAGS = ["/MDd"])
    else:
        if env['CC'] == 'cl' or env['CC'] == 'icl' and os.name == 'nt':
          # Link against non-debug system libraries.
          env.AppendUnique(CPPFLAGS=['/MD'])
    if not env['DEBUG_CHECKS']:
        # Set the 'no debug' symbol.
        env.AppendUnique(CPPDEFINES='NDEBUG')
    else:
        env.AppendUnique(CPPDEFINES='RUNTIME_CHECKS')
    if GetOption('with_python') or GetOption('python_support'):
        env.AppendUnique(CPPDEFINES=['PYTHON_ENABLED'])
    if GetOption('with_python'):
        # Add boost numpy include path.
        env.PrependUnique(CPPPATH=[Dir('#external/ndarray/Boost.NumPy').abspath])
    # Disable certain eigen features to be able to use the MPL license.
    env.AppendUnique(CPPDEFINES=['EIGEN_MPL2_ONLY'])
    # Doxygen executable.
    env['DOXY_EXEC'] = GetOption("doxy_exec")
    # Main library include folder.
    env.PrependUnique(CPPPATH=[Dir('#fertilized').abspath])
    # Versioning.
    env['VERSION_STRING'] = VERSION_STRING
    return env

def download_reporthook(count, block_size, total_size):
    """
    From http://blog.moleculea.com/2012/10/04/urlretrieve-progres-indicator/
    """
    global start_time
    if count == 0:
        start_time = time.time()
        return
    duration = time.time() - start_time
    progress_size = int(count * block_size)
    speed = int(progress_size / (1024 * max(duration, 1)))
    percent = int(count * block_size * 100 / total_size)
    sys.stdout.write("\r...%d%%, %d MB, %d KB/s, %d seconds passed" %
                    (percent, progress_size / (1024 * 1024), speed, duration))
    sys.stdout.flush()

    
def setupTargets(env, root=".",
                 caffe_headers=[], caffe_core_objects=[], caffe_link_libs=[]):
    # It should be possible to build without ndarray installed. Similarly,
    # it should be an extra step to build documentation and generate the
    # interface code. This is, why I introduce three extra command line
    # options to do these three steps. It is not possible to combine
    # them with a normal build in one command line call.
    # This has several reasons:
    #   - to generate the ndarray headers, you need m4 installed, which is very
    #     uncommon on Windows.
    #   - it is hard to track the output files of the code generator.
    #   - the doxygen builder module of SCons does not work for me on Windows.
    # I decided to work with explicit command line options instead of implicit
    # build targets to make the options more visible to the build user.
    if GetOption("generate_ndarray"):
      ndarraypath = os.path.join(root,'external','ndarray','include')
      ndarrayheaders = SConscript(os.path.join(ndarraypath,
                                               'SConscript'),
                                   exports='env',
                                   src_dir=os.path.join(root,
                                                        'external',
                                                        'ndarray'))
      installedheaders = []
      for header in Flatten(ndarrayheaders):
        relative = os.path.relpath(header.abspath, ndarraypath)
        installedheaders.append(env.InstallAs(os.path.join(root,
                                                           'fertilized',
                                                           relative), header))
    ndarray_installed = os.path.isfile(os.path.join('fertilized', 'ndarray.h'))
    ndarray_emsg = "You first have to call scons --generate-ndarray to use any " +\
                   "other build options. Otherwise, clone the complete project " +\
                   "from github."
    if GetOption("generate_interfaces"):
      if not ndarray_installed:
        print ndarray_emsg
        sys.exit(1)
      import subprocess
      os.chdir('CodeGenerator')
      subprocess.check_call([sys.executable, 'CodeGenerator.py'])
      os.chdir('..')
    interfaces_generated = os.path.isfile(os.path.join('fertilized', 'fertilized.h'))
    interfaces_emsg = "You first have to call scons --generate-interfaces to "+\
      "build python, matlab and C++ interfaces. Otherwise, clone the complete " +\
      "project from github."
    if GetOption("generate_documentation"):
      # Only add target when explicitely required.
      if not ndarray_installed:
        print ndarray_emsg
        sys.exit(1)
      SConscript(os.path.join(root, 'documentation', 'SConscript.py'),
                 exports=['env'])
    generate_mode = GetOption("generate_interfaces") or \
                    GetOption("generate_ndarray") or \
                    GetOption("generate_documentation")
    if not generate_mode:
      if not ndarray_installed:
        print ndarray_emsg
        sys.exit(1)
      if not interfaces_generated:
        print interfaces_emsg
        sys.exit(1)
    if not generate_mode:
      # After configuring, OpenCV highgui ist included.
      # Remove OpenCV highgui lib, since it is not required.
      if not GetOption("clean") and not GetOption("help"):
        tmp_libs = []
        for libitem in env['LIBS']:
          if isinstance(libitem, list):
            tmp_libs.extend(libitem)
          else:
            tmp_libs.append(libitem)
        if not GetOption("with_caffe"):
          env.Replace(LIBS=[lib for lib in tmp_libs \
                            if not lib.startswith("opencv_highgui")])
      lib, headers = SConscript(os.path.join(root, "fertilized", "SConscript.py"),
                                exports=['env', 'caffe_headers', 'caffe_core_objects', 'caffe_link_libs'],
                                variant_dir='build/'+env['VARIANT_DIR_PREF']+'/fertilized')
      # A copy in the project root for UNIX-sytems to get the linking paths
      # right.
      lib_lnk = lib[1] if os.name=='nt' else lib[0]
      lib_lnk = env.Install('#', lib_lnk)[0]
    if GetOption('with_caffe'):
      # Prepare the AlexNet as standard feature extractor.
      if GetOption('caffe_model_dir') == "":
        print "Please specify a directory to store the caffe models in with the parameter '--caffe-model-dir=/dir'!"
        sys.exit(1)
      else:
        alex_dir = os.path.abspath(os.path.join(GetOption('caffe_model_dir'), 'bvlc_alexnet'))
        if not os.path.exists(alex_dir):
          os.mkdir(alex_dir)
        layer_filename = os.path.join(alex_dir, 'bvlc_alexnet.caffemodel')
        model_filename = os.path.join(alex_dir, 'alexnet_extraction.prototxt')
        mean_filename = os.path.join(alex_dir, 'alexnet_mean.txt')
        with open('fertilized/feature_extraction/__alexnet.h', 'w') as alexf:
          alexf.write('/* This is an automatically generated file! */\n')
          alexf.write('const std::string __ALEXNET_MODELFILE = "%s";\n' % model_filename.replace('\\', '\\\\'))
          alexf.write('const std::string __ALEXNET_MEANFILE = "%s";\n' % mean_filename.replace('\\', '\\\\'))
          alexf.write('const std::string __ALEXNET_LAYERFILE = "%s";\n' % layer_filename.replace('\\', '\\\\'))
    if GetOption('with_python') and not generate_mode:
      # Build boost numpy
      VERSION = sys.version_info.major
      if os.name == 'nt':
          EXT_SUFFIX = '.dll'
          LIB_SUFFIX = '.lib'
          PY_SUFFIX = '.pyd'
      else:
          EXT_SUFFIX = sysconfig.get_config_var("EXT_SUFFIX")
          if VERSION == 2 and EXT_SUFFIX == 'None' or EXT_SUFFIX==None:
              EXT_SUFFIX = '.so'
          elif VERSION == 3 and EXT_SUFFIX == b'None' or EXT_SUFFIX==None:
              EXT_SUFFIX = '.so'
          LIB_SUFFIX = EXT_SUFFIX
          PY_SUFFIX = EXT_SUFFIX
      OBJ_SUFFIX = EXT_SUFFIX.replace ('.so', '.os')
      bn_module_path = os.path.join(root,
                                    'external',
                                    'ndarray',
                                    'Boost.NumPy',
                                    'libs',
                                    'numpy',
                                    'src')
      tmp_env = env.Clone()
      env.AppendUnique(CPPPATH=[Dir("#external/ndarray/Boost.NumPy").abspath])
      if env['CC'] == 'icl':
        # Disable whole library optimization here.
        env.Replace(CCFLAGS=[flag for flag in env['CCFLAGS'] if flag not in ['/GL']])
      bn_module = SConscript(os.path.join(bn_module_path, 'SConscript'),
                             exports=['env', 'EXT_SUFFIX', 'LIB_SUFFIX', 'OBJ_SUFFIX', 'PY_SUFFIX'])
      env = tmp_env
      py_mod, pymf_mod = SConscript(os.path.join(root, "pyfertilized", "SConscript.py"),
                                    exports=['env', 'bn_module', 'lib', 'PY_SUFFIX', 'lib_lnk'],
                                    variant_dir='build/'+env['VARIANT_DIR_PREF']+'/pyfertilized')
    if GetOption('with_tests') and not generate_mode:
      tests_executable = SConscript(os.path.join(root, "fertilized_tests", "SConscript.py"),
                                    exports=['env', 'lib', 'lib_lnk'],
                                    variant_dir='build/'+env['VARIANT_DIR_PREF']+'/fertilized_tests')
    if GetOption('with_matlab') and not generate_mode:
      matlab_module = SConscript(os.path.join(root, "matfertilized", "SConscript.py"),
                                 exports=['env', 'lib', 'lib_lnk'],
                                 variant_dir='build/'+env['VARIANT_DIR_PREF']+'/matfertilized')
    if GetOption('with_examples') and not generate_mode:
      SConscript(os.path.join(root, 'Presentation', 'SConscript.py'),
                 exports=['env', 'lib', 'lib_lnk'],
                 variant_dir='build/'+env['VARIANT_DIR_PREF']+'/Presentation')
    if not generate_mode:
      if GetOption("with_python"):
        print 'The project is built with python support. If you want you can install it ' +\
              'into the python library by ' +\
              'using setuptools from the pyfertilized directory.'
      # Install in project folders.
      project_includes = []
      for header in Flatten(headers):
        relative = os.path.relpath(header.abspath, Dir("#build/"+env['VARIANT_DIR_PREF']+'/fertilized').abspath)
        project_includes.append(env.InstallAs(os.path.join(Dir('#include').abspath,
                                                            'fertilized',
                                                            relative), header))
      if os.name == 'nt':
        project_lib = env.InstallAs(os.path.join(Dir('#lib').abspath, os.path.basename(lib[1].abspath)), lib[1])
        project_bin = env.InstallAs(os.path.join(Dir('#bin').abspath, os.path.basename(lib[0].abspath)), lib[0])
        if os.path.exists(Dir('#bindep').abspath):
          print 'Installing binary dependencies from folder bindep.'
          bindeps = Glob(os.path.join(Dir('#bindep').abspath, '*'))
          for bindep in bindeps:
            env.InstallAs(os.path.join(Dir('#bin').abspath, os.path.basename(bindep.abspath)), bindep)
      else:
        project_lib = env.InstallAs(os.path.join(Dir('#lib').abspath, os.path.basename(lib[0].abspath)), lib[0])
        project_bin = env.InstallAs(os.path.join(Dir('#bin').abspath, os.path.basename(lib[0].abspath)), lib[0])
      # Install in installation folders.
      prefix = Dir(GetOption("prefix")).abspath
      install_headers = GetOption('install_headers')
      install_lib = GetOption('install_lib')
      if not install_headers:
          install_headers = os.path.join(prefix, "include")
      if not install_lib:
          install_lib = os.path.join(prefix, "lib")
      env.Alias("install", env.Install(install_lib, lib))
      if GetOption('with_python'):
        env.Alias("install", env.Install(install_lib, bn_module))
      for header in Flatten(headers):
        relative = os.path.relpath(header.abspath, Dir("#build/"+env['VARIANT_DIR_PREF']+'/fertilized').abspath)
        env.Alias("install", env.InstallAs(os.path.join(install_headers,
                                                        'fertilized',
                                                        relative), header))

Return("setupOptions",
       "makeEnvironment",
       "setupTargets",
       "_checks",
       "getRequiredLibs")
