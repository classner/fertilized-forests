# Author: Christoph Lassner

# Assuming that this script has been called by `setup_environment.bat`,
# it is guaranteed that the commands `python` and `pip` work as intended.

import sys
import os
from subprocess import check_call, Popen, PIPE
import time
import urllib
import shutil
from glob import glob
import zipfile

STDOUT = open("setup-stdout.txt","wb")
STDERR = open("setup-stderr.txt","wb")

QUIET_MODE = len(sys.argv) > 1 and (sys.argv[1] == '--quiet')
if QUIET_MODE:
  BIN_FOLDER = sys.argv[2] + '\\Scripts\\'
  print 'Using scripts folder at %s.' % (BIN_FOLDER)
else:
  BIN_FOLDER = ''

#######################################
# Check for CLINT
try:
  import clint
  print "Python CLINT detected."
except:
  print "Python CLINT not found. Installing..."
  check_call(["%spip" % (BIN_FOLDER), "install", "clint"], stdout=STDOUT, stderr=STDERR)
  print "Installation complete."
  import clint

from clint.textui import prompt, validators, colored, puts, indent

#######################################
# Setup
if QUIET_MODE:
  puts(colored.yellow("Using quiet mode!"))
  if len(sys.argv) < 9:
    puts(colored.red("Too few arguments for quiet mode (%d, but required 8)!" % (len(sys.argv)- 1)))
    sys.exit(1)
  else:
    WITH_PYTHON = (sys.argv[3] == '--pyenabled')
    WITH_MATLAB = (sys.argv[4] == '--matenabled')
    WITH_CAFFE = (sys.argv[5] == '--caffeenabled')
    CAFFE_MODEL_DIR = sys.argv[6]
    CPU_ONLY = (sys.argv[7] == '--cpu-only')
    SUPPRESS_CAFFE_MODEL_DOWNLOAD = (sys.argv[7] == '--suppress-caffe-model-download')
else:
  #######################################
  # Initialize configuration.
  WITH_PYTHON = prompt.yn('Do you want to build the Python interface?')
  WITH_MATLAB = prompt.yn('Do you want to build the MATLAB interface?')
  WITH_CAFFE = prompt.yn('Do you want to use the CAFFE feature extraction?')
  if WITH_CAFFE:
    CAFFE_MODEL_DIR = prompt.query('Where do you want the CAFFE models to be stored (no spaces allowed)?', validators=[validators.PathValidator()])
  else:
    CAFFE_MODEL_DIR = None
  try:
    check_call(['which', 'nvcc'])
    CPU_ONLY = prompt.yn('Do you want to build the CPU only version of CAFFE?')
  except:
    puts(colored.red('No nvcc on the command line detected. Configuring CPU only build. If you want to change that, install nvcc and modify the file "compile.bat" (will be created at the end of this script).'))
    CPU_ONLY = True
  SUPPRESS_CAFFE_MODEL_DOWNLOAD = False

EIGEN_INSTALL_DIR = None
OPENBLAS_INSTALL_DIR = None

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

#######################################
# nuget
puts(colored.green('Checking build tools...'))
try:
  check_call(['where', 'nuget'], stdout=STDOUT, stderr=STDERR)
  with indent(4):
      puts('nuget found.')
except:
  with indent(4):
      puts('nuget not found. Downloading...')
      urllib.urlretrieve('https://nuget.org/nuget.exe',
                         'nuget.exe', download_reporthook)

#######################################
# General installation
class PackageValidator(object):
    message = 'Enter a valid path.'

    def __init__(self, message=None, contained_files=[]):
        if message is not None:
            self.message = message
        self.contained_files = contained_files

    def __call__(self, value):
        """
        Validates that the input is a valid directory.
        """
        if not os.path.isdir(value):
            raise validators.ValidationError(self.message)
        for contfile in self.contained_files:
            if not os.path.exists(os.path.join(value, contfile)):
                raise validators.ValidationError(self.message + os.linesep +\
                  "The path did not contain the file/folder %s!" % (contfile))
        return value

def configure_package(name,
                      contained_files,
                      download_url=None,
                      download_filename=None,
                      install_commands=[],
                      version=None,
                      doubleindent=False):
    SPECIFY_PATH = False
    OWN = False
    if doubleindent:
        indents = '        '
    else:
        indents = '    '
    if not QUIET_MODE:
        SPECIFY_PATH = not prompt.yn(indents + "Do you want to use your own version of %s?" % (name), default='n')
    if SPECIFY_PATH:
        libpath = prompt.query(indents + "Please specify the path to %s. The folder must " % (name) +\
          "contain the files/folders " + ", ".join(contained_files) + ".",
          validators=[PackageValidator(contained_files=contained_files)])
        OWN = True
    else:
        if not download_url is None:
            if os.path.exists(download_filename):
                with indent(4):
                    puts('Download file %s detected. Skipping.' % (download_filename))
            else:
                puts('Downloading...')
                urllib.urlretrieve(download_url,
                                   download_filename,
                                   download_reporthook)
                for command in install_commands:
                    check_call(command, stdout=STDOUT, stderr=STDERR)
            libpath = None
        else:
            if os.path.exists(os.path.join('nuget-deps', name)):
                with indent(4):
                    puts('nuget folder detected. Skipping.')
            else:
                with indent(4):
                    puts('installing using nuget...')
                if version is None:
                    check_call(['nuget', 'install', name, '-OutputDirectory', 'nuget-deps', '-ExcludeVersion'])
                else:
                    check_call(['nuget', 'install', name, '-Version', version, '-OutputDirectory', 'nuget-deps', '-ExcludeVersion'])
            libpath = os.path.join("nuget-deps", name)
    return libpath, OWN

def copy_contents(src, dst):
    r"""
    C.t. http://techs.studyhorror.com/python-copy-move-sub-folders-recursively-i-92.
    """
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if not os.path.exists(d):
            shutil.copy2(s, d)

def install_boost_binary(name, package_name=None):
    if package_name is None:
        package_name = 'boost_%s-vc120' % (name)
    if not os.path.exists(os.path.join('nuget-deps', package_name)):
        check_call(['nuget', 'install', package_name, '-OutputDirectory', 'nuget-deps', '-ExcludeVersion'])
    copy_contents(r'nuget-deps\%s\lib\native\address-model-64\lib' % (package_name),
                  r'nuget-deps\boost-compiled\stage\lib')

puts(colored.green('Installing packages...'))
if not os.path.exists('nuget-deps'):
    os.mkdir('nuget-deps')
with indent(4):
  puts('OpenCV.')
  OPENCV_ROOT, own = configure_package('OpenCV',
                                       [r'include\opencv2'],
                                       'http://downloads.sourceforge.net/project/opencvlibrary/opencv-win/2.4.11/opencv-2.4.11.exe',
                                       'opencv-2.4.11.exe',
                                       [['opencv-2.4.11.exe', r'-o"%s"' % (os.path.relpath(os.path.abspath('nuget-deps'), os.path.splitdrive(os.getcwd())[0] + '\\')), '-y']])
  if own:
      OPENCV_VERSION = prompt.query("    Please specify the OpenCV version as whole number, e.g., 2411 for 2.4.11:")
  else:
      OPENCV_VERSION = "2411"
      OPENCV_ROOT = r"nuget-deps\opencv\build"
  OPENCV_LIB_DIR = os.path.join(OPENCV_ROOT, 'x64', 'vc12', 'lib')
  OPENCV_BIN_DIR = os.path.join(OPENCV_ROOT, 'x64', 'vc12', 'bin')
  puts('eigen 3.')
  EIGEN_ROOT, own = configure_package('Eigen', [r'Eigen\Eigen'])
  if not own:
      EIGEN_ROOT += r'\build\native\include'
  puts('boost.')
  if not os.path.exists(r'nuget-deps\boost-compiled'):
      os.mkdir(r'nuget-deps\boost-compiled')
  BOOST_ROOT, own = configure_package('boost', ['boost', r'stage\lib'])
  if not own:
      if not os.path.exists(r'nuget-deps\boost-compiled\boost'):
          shutil.move(r'nuget-deps\boost\lib\native\include\boost',
                      r'nuget-deps\boost-compiled\boost')
      if not os.path.exists(r'nuget-deps\boost-compiled\stage'):
          os.mkdir(r'nuget-deps\boost-compiled\stage')
      if not os.path.exists(r'nuget-deps\boost-compiled\stage\lib'):
          os.mkdir(r'nuget-deps\boost-compiled\stage\lib')
      install_boost_binary('serialization')
      install_boost_binary('thread')
      install_boost_binary('unit_test_framework')
      install_boost_binary('wserialization')
      install_boost_binary('test_exec_monitor')
      if not os.path.exists(r'boost_python_2.7_cache.zip'):
          puts(colored.yellow('Using a prepared version of boost python for Python 2.7. If you want to use the library with a different version of Python, you can, but will have to use a self-compiled version of boost with your specific Python.'))
          urllib.urlretrieve('http://www.multimedia-computing.de/fertilized/files/cache/boost_python_2.7.zip',
                             'boost_python_2.7.zip',
                             download_reporthook)
          bpcache_zip = zipfile.ZipFile('boost_python_2.7.zip')
          bpcache_zip.extractall(path=r'nuget-deps\boost-compiled\stage\lib')
      if WITH_CAFFE:
          install_boost_binary('chrono')
          install_boost_binary('date_time')
          install_boost_binary('filesystem')
          install_boost_binary('system')
      BOOST_ROOT += '-compiled'
  if WITH_CAFFE:
    puts(colored.yellow('Installing additional CAFFE dependencies...'))
    with indent(4):
      puts('OpenBLAS.')
      OPENBLAS_ROOT, own = configure_package('OpenBLAS', [r'include\cblas.h'], doubleindent=True)
      if not own:
          OPENBLAS_ROOT += r'\lib\native'
          OPENBLAS_LIB_DIR = os.path.join(OPENBLAS_ROOT, 'lib', 'x64')
          OPENBLAS_BIN_DIR = os.path.join(OPENBLAS_ROOT, 'bin', 'x64')
      else:
          OPENBLAS_LIB_DIR = os.path.join(OPENBLAS_ROOT, 'lib')
          OPENBLAS_BIN_DIR = os.path.join(OPENBLAS_ROOT, 'bin')
      shutil.copy2(os.path.join(OPENBLAS_LIB_DIR, 'libopenblas.dll.a'),
                   os.path.join(OPENBLAS_LIB_DIR, 'libopenblas.dll.a.lib'))
      puts('protobuf.')
      PROTOBUF_ROOT, own = configure_package('protobuf-v120', [r'src\google\protobuf'], version='2.6.1', doubleindent=True)
      if own:
          PROTOBUF_LIB_DIR = os.path.join(PROTOBUF_ROOT, 'vsprojects', 'x64', 'Release')
          PROTOBUF_INCLUDE_DIR = os.path.join(PROTOBUF_ROOT, 'src')
      else:
          PROTOBUF_LIB_DIR = os.path.join(PROTOBUF_ROOT, 'build', 'native', 'lib', 'x64', 'v120', 'Release')
          PROTOBUF_INCLUDE_DIR = os.path.join(PROTOBUF_ROOT, 'build', 'native', 'include')
      PROTOC, own = configure_package('protoc',
                                      ['protoc.exe'],
                                      'https://github.com/google/protobuf/releases/download/v2.6.1/protoc-2.6.1-win32.zip',
                                      'protoc-2.6.1-win32.zip',
                                      [],
                                      doubleindent=True)
      if not own and not os.path.exists(r'nuget-deps\protoc'):
          os.mkdir(r'nuget-deps\protoc')
          protoc_zip = zipfile.ZipFile('protoc-2.6.1-win32.zip')
          protoc_zip.extractall(path=r'nuget-deps\protoc')
      if own:
         PROTOC += r'\protoc.exe'
      else:
         PROTOC = r'nuget-deps\protoc\protoc.exe'
      os.environ['PROTOC'] = PROTOC
      puts('hdf5.')
      HDF5_ROOT, own = configure_package('hdf5-v120', [r'include\hdf5.h', r'lib\hdf5.lib'], doubleindent=True)
      if not own and not os.path.exists(r'nuget-deps\hdf5'):
        urllib.urlretrieve('http://www.multimedia-computing.de/fertilized/files/cache/HDF5.zip',
               'HDF5.zip',
               download_reporthook)
        hdf5_zip = zipfile.ZipFile('hdf5.zip')
        os.mkdir(r'nuget-deps\hdf5')
        hdf5_zip.extractall(path=r'nuget-deps\hdf5')
        HDF5_ROOT = r'nuget-deps\hdf5'
      HDF5_LIB = HDF5_ROOT + r'\lib'
      HDF5_BIN = HDF5_ROOT + r'\bin'
      puts('AlexNet as default feature extractor.')
      # This can happen in quiet mode.
      if not os.path.exists(CAFFE_MODEL_DIR):
        # Try the best.
        os.mkdir(CAFFE_MODEL_DIR)
      alex_dir = os.path.abspath(os.path.join(CAFFE_MODEL_DIR, 'bvlc_alexnet'))
      if not os.path.exists(alex_dir):
        os.mkdir(alex_dir)
      layer_filename = os.path.join(alex_dir, 'bvlc_alexnet.caffemodel')
      if not os.path.exists(layer_filename):
        if not SUPPRESS_CAFFE_MODEL_DOWNLOAD:
          urllib.urlretrieve('http://dl.caffe.berkeleyvision.org/bvlc_alexnet.caffemodel',
                             layer_filename, download_reporthook)
        else:
          puts(colored.yellow('Caffe model download suppressed. You will have to manually install the "bvlc_alexnet.caffemodel" to %s.' % (layer_filename)))
      model_filename = os.path.join(alex_dir, 'alexnet_extraction.prototxt')
      orig_model_file = glob(r'fertilized\feature_extraction\alexnet_extraction.prototxt')
      if not os.path.exists(model_filename):
        shutil.copyfile(os.path.abspath(str(orig_model_file[0])),
                        model_filename)
      mean_filename = os.path.join(alex_dir, 'alexnet_mean.txt')
      orig_mean_file = glob(r'fertilized\feature_extraction\alexnet_mean.txt')
      if not os.path.exists(mean_filename):
        shutil.copyfile(os.path.abspath(str(orig_mean_file[0])),
                        mean_filename)

#######################################
# Python
puts(colored.green('Installing Python modules...'))
PIPLIST = ['networkx', 'cppheaderparser', 'ply', 'pypiwin32']
CONDALIST = ['jinja2', 'numpy']
if WITH_PYTHON:
  CONDALIST.extend(['scipy', 'pillow', 'scikit-image', 'matplotlib', 'scikit-learn'])
try:
  print 'conda location: %s' % ('%sconda.exe' % (BIN_FOLDER))
  check_call(['where', '%sconda.exe' % (BIN_FOLDER)]) #, stdout=STDOUT, stderr=STDERR)
  CONDA_AVAILABLE = True
  call(['dir', r'C:\Anaconda\Scripts'])
except:
  CONDA_AVAILABLE = False
if CONDA_AVAILABLE:
  puts(colored.green('conda detected! Using conda to install available packages.'))
  check_call(['%sconda' % (BIN_FOLDER), 'update', '--yes', 'conda'], stdout=STDOUT, stderr=STDERR)
else:
  PIPLIST.extend(CONDALIST)
  CONDALIST = []
with indent(4):
  for mname in CONDALIST:
    puts("%s." % (mname))
    check_call(['%sconda' % (BIN_FOLDER), 'install', '--yes', mname], stdout=STDOUT, stderr=STDERR)
  for mname in PIPLIST:
    puts("%s." % (mname))
    try:
        check_call(['%spip' % (BIN_FOLDER), 'install', mname], stdout=STDOUT, stderr=STDERR)
    except:
        print "Installing %s using pip failed. Please try to install it yourself. If that's not possible, use the Anaconda Python distribution. In that case, this script will use the 'conda' installer, with which all packages can be installed for sure." % (mname)
        sys.exit(1)

#######################################
# Scons
# Scons must be installed from the homepage, since the version on pip is
# outdated and does not work with VS2013.
puts(colored.green('Installing SCons 2.3.4...'))
if not os.path.exists('scons-2.3.4.zip'):
    with indent(4):
        puts("Downloading...")
        urllib.urlretrieve('http://prdownloads.sourceforge.net/scons/scons-2.3.4.zip',
                           'scons-2.3.4.zip',
                           download_reporthook)
        puts("Extracting...")
        protoc_zip = zipfile.ZipFile('scons-2.3.4.zip')
        protoc_zip.extractall(path='.')

        os.chdir('scons-2.3.4')
        puts("Installing...")
        check_call([sys.executable, 'setup.py', 'install'], stdout=STDOUT, stderr=STDERR)
        os.chdir('..')
else:
    with indent(4):
        puts("scons-2.3.4.zip detected. Skipping.")

#######################################
# MATLAB
if WITH_MATLAB:
  puts(colored.green('Configuring for MATLAB...'))
  MATLAB_ROOT = prompt.query('Where is your MATLAB installed? This folder should have the subfolders "bin", "extern", etc. Finish the foldername without trailing backslash:', validators=[validators.PathValidator()])
  MATLAB_PATH_STRING = 'set MATLAB_ROOT="%s"' % (MATLAB_ROOT)
else:
  MATLAB_PATH_STRING = '# set MATLAB_ROOT=...'

#######################################
# Submodules
puts(colored.green('Pulling in submodules...'))
check_call([r'C:\\Program Files (x86)\\Git\\bin\\git.exe', 'submodule', 'update', '--init', '--recursive'], stdout=STDOUT, stderr=STDERR)

#######################################
# Generating interfaces
puts(colored.green('Generating interfaces...'))
SCONS = Popen('where scons', stdout=PIPE).communicate()[0].strip()
check_call([SCONS, '--generate-interfaces'])
# Cleanup
if os.path.exists('config.log'):
  os.remove('config.log')
if os.path.exists('.sconsign.dblite'):
  os.remove('.sconsign.dblite')
if os.path.exists('.sconf_temp'):
  shutil.rmtree('.sconf_temp')

#######################################
# File generation
puts(colored.green('Generating setup_paths.bat...'))

# Making paths absolute.
BOOST_ROOT = os.path.abspath(BOOST_ROOT)
OPENCV_ROOT = os.path.abspath(OPENCV_ROOT)
EIGEN_ROOT = os.path.abspath(EIGEN_ROOT)
if WITH_MATLAB:
  MATLAB_ROOT = os.path.abspath(MATLAB_ROOT)
if WITH_CAFFE:
  HDF5_ROOT = os.path.abspath(HDF5_ROOT)
  HDF5_LIB = os.path.abspath(HDF5_LIB)
  HDF5_BIN = os.path.abspath(HDF5_BIN)
  OPENBLAS_ROOT = os.path.abspath(OPENBLAS_ROOT)
  OPENBLAS_LIB_DIR = os.path.abspath(OPENBLAS_LIB_DIR)
  OPENBLAS_BIN_DIR = os.path.abspath(OPENBLAS_BIN_DIR)
  PROTOBUF_INCLUDE_DIR = os.path.abspath(PROTOBUF_INCLUDE_DIR)
  PROTOBUF_LIB_DIR = os.path.abspath(PROTOBUF_LIB_DIR)
  PROTOC = os.path.abspath(PROTOC)

if WITH_MATLAB:
    matlab_code = r'set MATLAB_ROOT=%s' % (MATLAB_ROOT)
else:
    matlab_code = r'REM set MATLAB_ROOT=C:\Program Files\MATLAB\R2014a'
if WITH_CAFFE:
    hdf5_code = r'set HDF5_ROOT=%s%sset HDF5_LIB_DIR=%s' % (HDF5_ROOT, os.linesep, HDF5_LIB)
    openblas_code = r'set OPENBLAS_ROOT=%s%sset OPENBLAS_LIB_DIR=%s' % (OPENBLAS_ROOT, os.linesep, OPENBLAS_LIB_DIR)
    protobuf_code = 'set PROTOBUF_INCLUDE_DIR=%s\nset PROTOBUF_LIB_DIR=%s' % (PROTOBUF_INCLUDE_DIR, PROTOBUF_LIB_DIR)
    protoc_code = r'set PROTOC=%s' % (PROTOC)
else:
    hdf5_code = r'REM set HDF5_ROOT=C:\libraries\HDF5\1.8.14%sREM set HDF5_LIB_DIR=...' % (os.linesep)
    openblas_code = r'REM set OPENBLAS_ROOT=C:\libraries\OpenBLAS-v0.2.14'
    protobuf_code = r'REM set PROTOBUF_ROOT=C:\libraries\protobuf-2.6.1%sset PROTOBUF_LIB_DIR=...' % (os.linesep)
    protoc_code = r'REM set PROTOC=%PROTOBUF_ROOT%\vsprojects\x64\Release\protoc.exe'
with open('setup_paths.bat', 'w') as outfile:
  outfile.write(r"""
@echo off
set BOOST_ROOT={BOOST_ROOT}
REM Whereever the compiled files are.
set BOOST_LIB_DIR=%BOOST_ROOT%\stage\lib
set OPENCV_ROOT={OPENCV_ROOT}
set OPENCV_LIB_DIR=%OPENCV_ROOT%\x64\vc12\lib
set OPENCV_VERSION={OPENCV_VERSION}
set EIGEN_ROOT={EIGEN_ROOT}
REM Only required if you build --with-matlab
{matlab_code}
REM Only required if you build --with-caffe
{hdf5_code}
{openblas_code}
{protobuf_code}
{protoc_code}

IF NOT "%FERTILIZED_ADDED_PATH%"=="" goto notextending
  echo Extending path!
  set PATH=%PATH%;%OPENCV_ROOT%\x64\vc12\bin;%BOOST_LIB_DIR%;
  IF "%HDF5_ROOT%"=="" goto hdf5done
  set PATH=%PATH%;{HDF5_BIN};
:hdf5done
  IF "%OPENBLAS_ROOT%"=="" goto openblasdone
  set PATH=%PATH%;{OPENBLAS_BIN_DIR};
:openblasdone
  IF "%MATLAB_ROOT%"=="" goto matlabdone
  set PATH=%PATH%;%MATLAB_ROOT%\bin\win64;
:matlabdone
  set FERTILIZED_ADDED_PATH=1
  goto end
:notextending
  echo Path already extended. No update.

:end
""".format(**locals()))
puts(colored.green('Generating compile.bat...'))
if WITH_PYTHON:
  PY_STRING = '--with-python '
else:
  PY_STRING = ''

if WITH_MATLAB:
  MA_STRING = '--with-matlab '
else:
  MA_STRING = ''

if WITH_CAFFE:
  CA_STRING = '--with-caffe '
  CA_MO_STRING = '--caffe-model-dir=%s ' % (CAFFE_MODEL_DIR)
  if CPU_ONLY:
    CA_CP_STRING = '--cpu-only '
  else:
    CA_CP_STRING = ''
else:
  CA_STRING = ''
  CA_MO_STRING = ''
  CA_CP_STRING = ''

with open('compile.bat', 'w') as outfile:
  outfile.write(r"""
@echo off
echo You can speed up the build process by editing
echo "compile.bat" and increasing the --jobs=1
echo value.

echo Setting up paths...
call setup_paths.bat

echo Compiling...
REM Add --with-python to build the python interface.
REM Add --with-matlab to build the MATLAB interface.
REM Add --with-tests to build the tests.
REM Add --with-examples to build the examples.
REM Add --with-caffe to build the CAFFE feature extraction.
REM Configure --caffe-model-dir to change the location of the CAFFE models for feature extraction.
REM Configure --temp-folder to change the CAFFE tmp folder.
REM Add --cpu-only to build the CPU only version of CAFFE.
REM Add --with-checks to enable assertions.
REM Add --disable-optimizations to create an -Od build for debugging.
scons --with-serialization %s%s--with-tests --with-examples %s%s%s--jobs=1
""" % (PY_STRING, MA_STRING, CA_STRING, CA_MO_STRING, CA_CP_STRING))

puts(colored.green('All set! Adjust "setup_paths.bat" and "compile.bat" to your needs!'))
if WITH_PYTHON:
  puts(colored.yellow('Infos for Python:'))
  with indent(4):
    puts('If you want to install the module after building into your python library, cd to the folder pyfertilized and run "python setup.py install"')

puts(colored.green("If there are any issues, please don't hesitate to post an issue report on github after consulting the FAQ page on http://www.fertilized-forests.org . For straightforward troubleshooting during the configuration process, see the file 'config.log'."))

puts(colored.green("If you completed all parts successfully, you should now be able to build the library with the command 'compile.bat'."))
