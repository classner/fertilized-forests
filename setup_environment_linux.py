#!python
# Author: Christoph Lassner

# Assuming that this script has been called by `setup_environment.sh`,
# it is guaranteed that the commands `python` and `pip` work as intended.

import sys
import os
from subprocess import call, check_call
import time
import urllib
import shutil
from glob import glob

#######################################
# Check for CLINT
try:
  import clint
  print "Python CLINT detected."
except:
  print "Python CLINT not found. Installing..."
  check_call(["pip", "install", "clint"])
  print "Installation complete."
  import clint

from clint.textui import prompt, validators, colored, puts, indent

QUIET_MODE = (sys.argv[1] == '--quiet')
if QUIET_MODE:
  ADD_REPO_SUFF = '-y'
else:
  ADD_REPO_SUFF = ''

if QUIET_MODE:
  puts(colored.red("Using quiet mode!"))
  if len(sys.argv) < 9:
    puts(colored.red("Too few arguments for quiet mode (%d, but required 8)!" % (len(sys.argv)- 1)))
    sys.exit(1)
  else:
    APPLY_UBUNTU_12_PATCHES = (sys.argv[2] == '--ub12')
    APPLY_UBUNTU_13_PATCHES = (sys.argv[2] == '--ub13')
    WITH_PYTHON = (sys.argv[3] == '--pyenabled')
    WITH_MATLAB = (sys.argv[4] == '--matenabled')
    WITH_CAFFE = (sys.argv[5] == '--caffeenabled')
    CAFFE_MODEL_DIR = sys.argv[6]
    CPU_ONLY = (sys.argv[7] == '--cpu-only')
    SUPPRESS_CAFFE_MODEL_DOWNLOAD = (sys.argv[8] == '--suppress-caffe-model-download')
    SET_CXX_CC = True
else:
  #######################################
  # Determine the kind of patches to apply
  APPLY_UBUNTU_12_PATCHES = prompt.yn('Is your system based on the Ubuntu 12 package sources (in doubt, no)? If you answer yes, I will apply fixes to the package sources to make the required software packages available.', default=False)

  if not APPLY_UBUNTU_12_PATCHES:
    APPLY_UBUNTU_13_PATCHES = prompt.yn('Is your system based on the Ubuntu 13 package sources AND you are not using the proprietary NVIDIA drivers (in doubt, no)? If you answer yes, a bug is fixed that erroneously pulls in NVIDIA drivers.', default=False)
  else:
    APPLY_UBUNTU_13_PATCHES = False

  #######################################
  # Initialize configuration.
  WITH_PYTHON = prompt.yn('Do you want to build the Python interface?')
  WITH_MATLAB = prompt.yn('Do you want to build the MATLAB interface?')
  WITH_CAFFE = prompt.yn('Do you want to use the CAFFE feature extraction?')
  if WITH_CAFFE:
    CAFFE_MODEL_DIR = prompt.query('Where do you want the CAFFE models to be stored?', validators=[validators.PathValidator()])
  else:
    CAFFE_MODEL_DIR = None
  try:
    check_call(['which', 'nvcc'])
    CPU_ONLY = prompt.yn('Do you want to build the CPU only version of CAFFE?')
  except:
    puts(colored.red('No nvcc on the command line detected. Configuring CPU only build. If you want to change that, install nvcc and modify the file "compile.sh" (will be created at the end of this script).'))
    CPU_ONLY = True

  SET_CXX_CC = False
  EIGEN_INSTALL_DIR = None

#######################################
# Build tools
puts('Installing build tools...')
check_call(['apt-get', 'install', 'build-essential'])

#######################################
# Ubuntu 12
if APPLY_UBUNTU_12_PATCHES:
  puts(colored.green('Applying Ubuntu 12 patches.'))
  if not QUIET_MODE:
    puts(colored.red('If you answer any of the following questions with "n", you will HAVE to care for installing a current version of the respective library and adjusting "setup_paths.sh" yourself. Otherwise, the build WILL fail!'))
  with indent(4):
    puts('Adding current gcc repository...')
    check_call(['add-apt-repository','ppa:ubuntu-toolchain-r/test', ADD_REPO_SUFF])
    puts('Adding current OpenCV repository...')
    check_call(['add-apt-repository', 'ppa:yjwong/opencv2', ADD_REPO_SUFF])
    puts('Adding current boost repository...')
    check_call(['add-apt-repository', 'ppa:boost-latest/ppa', ADD_REPO_SUFF])
    puts('Updating package cache...')
    check_call(['apt-get', 'update'])
    puts('Installing gcc 4.8...')
    check_call(['apt-get', 'install', 'g++-4.8', '>', 'allout.txt', '2>&1'])
    if not QUIET_MODE:
      SET_CXX_CC = prompt.yn('Should gcc-4.8 be registered as system compiler (CXX and CC environment variables will be set)?')
    if SET_CXX_CC:
      # Set environment variable.
      # c.t. http://stackoverflow.com/questions/1506010/how-to-use-export-with-python-on-linux
      os.putenv('CXX', 'g++-4.8')
      os.putenv('CC', 'gcc-4.8')
      os.system('bash')
    if WITH_CAFFE:
      if QUIET_MODE or prompt.yn('Should I install a current version of OpenBLAS?'):
        with indent(2):
          check_call(['apt-get', 'install', 'gfortran', '>', 'allout.txt', '2>&1'])
          check_call(['ln', '-s', '/usr/lib/x86_64-linux-gnu/libgfortran.so.3', '/usr/lib/x86_64-linux-gnu/libgfortran.so'])
          check_call(['wget', 'http://github.com/xianyi/OpenBLAS/archive/v0.2.14.zip', '>', 'allout.txt', '2>&1'])
          check_call(['unzip', 'v0.2.14.zip', '>', 'allout.txt', '2>&1'])
          os.chdir('OpenBLAS-0.2.14')
          check_call(['make', '>', 'allout.txt', '2>&1'])
          check_call(['make', 'install', 'PREFIX=/usr/local/OpenBLAS', '>', 'allout.txt', '2>&1'])
          check_call(['ln', '-s', '/usr/local/OpenBLAS/lib/libopenblas.so', '/usr/local/lib/libopenblas.so.0'])
          os.chdir('..')
          os.remove('v0.2.14.zip')
          os.rmdir('OpenBLAS-0.2.14')
      if QUIET_MODE or prompt.yn('Should I install a current version of GLOG?'):
        with indent(2):
          check_call(['wget', 'https://github.com/google/glog/archive/v0.3.4.zip'])
          check_call(['unzip', 'v0.3.4.zip', '>', 'allout.txt', '2>&1'])
          os.chdir('glog-0.3.4')
          check_call(['./configure', '>', 'allout.txt', '2>&1'])
          check_call(['make', '>', 'allout.txt', '2>&1'])
          check_call(['make', 'install', '>', 'allout.txt', '2>&1'])
          os.chdir('..')
          os.remove('v0.3.4.zip')
          os.rmdir('glog-0.3.4')
      if QUIET_MODE or prompt.yn('Should I install a current version of boost?'):
        with indent(2):
          check_call(['apt-get', 'install', 'libboost1.55-all-dev'])
      if QUIET_MODE or prompt.yn('Should I install a current version of EIGEN?'):
        with indent(2):
          check_call(['wget', 'http://bitbucket.org/eigen/eigen/get/3.2.4.zip'])
          check_call(['unzip', '3.2.4.zip', '-d', '/usr/include/eigen3', '>', 'allout.txt', '2>&1'])
          EIGEN_INSTALL_DIR = '/usr/include/eigen3/eigen-eigen-10219c95fe65'

#######################################
# Ubuntu 13
if APPLY_UBUNTU_13_PATCHES:
  puts(colored.green('Applying Ubuntu 13 patches.'))
  with indent(4):
    puts('OpenCL:')
    check_call(['apt-get', 'install', 'ocl-icd-libopencl1'])

#######################################
# General installation
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

puts('Installing system packages...')
puts('OpenCV:')
check_call(['apt-get', 'install', 'libopencv-dev'])
if not APPLY_UBUNTU_12_PATCHES:
  puts('boost:')
  check_call(['apt-get', 'install', 'libboost-all-dev'])
puts('eigen:')
check_call(['apt-get', 'install', 'libeigen3-dev'])
if not check_call(['which', 'git']):
  puts('git:')
  check_call(['apt-get', 'install', 'git-core'])
if WITH_CAFFE:
  puts('Installing additional CAFFE dependencies...')
  with indent(4):
    if not APPLY_UBUNTU_12_PATCHES:
      puts('OpenBLAS:')
      check_call(['apt-get', 'install', 'libopenblas-dev'])
      puts('glog:')
      check_call(['apt-get', 'install', 'libgoogle-glog-dev'])
    puts('protobuf:')
    check_call(['apt-get', 'install', 'libprotobuf-dev', 'protobuf-compiler'])
    puts('hdf5:')
    check_call(['apt-get', 'install', 'libhdf5-serial-dev'])
    puts('AlexNet as default feature extractor...')
    alex_dir = os.path.abspath(os.path.join(CAFFE_MODEL_DIR, 'bvlc_alexnet'))
    if not os.path.exists(alex_dir):
      os.mkdir(alex_dir)
    layer_filename = os.path.join(alex_dir, 'bvlc_alexnet.caffemodel')
    if not os.path.exists(layer_filename):
      urllib.urlretrieve('http://dl.caffe.berkeleyvision.org/bvlc_alexnet.caffemodel',
                         layer_filename, download_reporthook)
    model_filename = os.path.join(alex_dir, 'alexnet_extraction.prototxt')
    orig_model_file = glob('./fertilized/feature_extraction/alexnet_extraction.prototxt')
    if not os.path.exists(model_filename):
      shutil.copyfile(os.path.abspath(str(orig_model_file[0])),
                      model_filename)
    mean_filename = os.path.join(alex_dir, 'alexnet_mean.txt')
    orig_mean_file = Glob('./fertilized/feature_extraction/alexnet_mean.txt')
    if not os.path.exists(mean_filename):
      shutil.copyfile(os.path.abspath(str(orig_mean_file[0])),
                      mean_filename)

#######################################
# EIGEN include folder
if EIGEN_INSTALL_DIR is None:
  if os.path.exists('/usr/include/eigen3'):
    EIGEN_INSTALL_DIR = '/usr/include/eigen3'
  elif os.path.exists('/usr/local/include/eigen3'):
    EIGEN_INSTALL_DIR = '/usr/local/include/eigen3'
  else:
    puts(colored.red('EIGEN installation dir not in /usr[/local]/include/eigen3! Locate it yourself and modify "setup_paths.sh"!'))

#######################################
# Python
puts(colored.green('Installing Python modules...'))
PIPLIST = ['networkx', 'cppheaderparser', 'ply']
CONDALIST = ['jinja2', 'numpy', 'scons']
if WITH_PYTHON:
  CONDALIST.extend(['scipy', 'pillow', 'scikit-image', 'matplotlib', 'scikit-learn'])
try:
  CONDA_AVAILABLE = (check_call(['which', 'conda']) != '')
except:
  CONDA_AVAILABLE = False
if CONDA_AVAILABLE:
  check_call(['conda', 'update', '--yes', 'conda', '>', 'allout.txt', '2>&1'])
else:
  PIPLIST.extend(CONDALIST)
  CONDALIST = []
with indent(4):
  for mname in CONDALIST:
    puts("%s:" % (mname))
    check_call(['conda', 'install', '--yes', mname, '>', 'allout.txt', '2>&1'])
  for mname in MLIST:
    puts("%s:" % (mname))
    check_call(['pip', 'install', mname, '>', 'allout.txt', '2>&1'])

#######################################
# MATLAB
if WITH_MATLAB:
  puts(colored.green('Configuring for MATLAB...'))
  MATLAB_ROOT = prompt.query('Where is your MATLAB installed? This folder should have the subfolders "bin", "extern", ...', validators=[validators.PathValidator()])
  MATLAB_PATH_STRING = 'export MATLAB_ROOT="%s"' % (MATLAB_ROOT)
else:
  MATLAB_PATH_STRING = '# export MATLAB_ROOT=...'

#######################################
# Submodules
puts(colored.green('Pulling in submodules...'))
check_call(['git', 'submodule', 'update', '--init', '--recursive'])

#######################################
# Generating interfaces
puts(colored.green('Generating interfaces...'))
check_call(['scons', '--generate-interfaces'])

#######################################
# File generation
puts(colored.green('Generating setup_paths.sh...'))
if SET_CXX_CC:
  CXX_CC_CODE = 'export CXX="g++-4.8" CC="gcc-4.8"'
else:
  CXX_CC_CODE = ''
with open('setup_paths.sh', 'w') as outfile:
  outfile.write(r"""
# Modify this file as required.
# export BOOST_ROOT=...
# export BOOST_LIB_DIR=...
# export OPENCV_ROOT=...
# export OPENCV_LIB_DIR=...
# export OPENBLAS_ROOT=...
# export PROTOBUF_ROOT=...
# export PROTOC=...
# export PATH="...:$PATH"
%s
%s
export EIGEN_ROOT="%s"
""" % (CXX_CC_CODE, MATLAB_PATH_STRING, EIGEN_INSTALL_DIR))
check_call(['chmod', '+x', 'setup_paths.sh'])
puts(colored.green('Generating compile.sh...'))
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

with open('compile.sh', 'w') as outfile:
  outfile.write(r"""
echo You can speed up the build process by editing
echo "compile.sh" and increasing the --jobs=1
echo value.

echo Setting up paths...
source setup_paths.sh

echo Compiling...
# Add --with-python to build the python interface.
# Add --with-matlab to build the MATLAB interface.
# Add --with-tests to build the tests.
# Add --with-examples to build the examples.
# Add --with-caffe to build the CAFFE feature extraction.
# Configure --caffe-model-dir to change the location of the CAFFE models for feature extraction.
# Configure --temp-folder to change the CAFFE tmp folder.
# Add --cpu-only to build the CPU only version of CAFFE.
# Add --with-checks to enable assertions.
# Add --disable-optimizations to create an -Od build for debugging.
scons --with-serialization %s%s--with-tests --with-examples %s%s%s--jobs=1
""" % (PY_STRING, MA_STRING, CA_STRING, CA_MO_STRING, CA_CP_STRING))
check_call(['chmod', '+x', 'compile.sh'])

puts(colored.green('All set! Adjust "setup_paths.sh" and "compile.sh" to your needs!'))
if WITH_PYTHON:
  puts(colored.yellow('Infos for Python:'))
  with indent(4):
    puts('If you want to install the module after building into your python library, cd to the folder pyfertilized and run "python setup.py install"')

if WITH_MATLAB:
  puts(colored.yellow('Infos for MATLAB:'))
  with indent(4):
    puts('You have to add the MATLAB 64 bit binary path to your LD_LIBRARY path to make things work. You can do this by adding "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:%s/bin/glnxa64" to your ~/.bashrc.' % (MATLAB_ROOT))

puts(colored.green("If there are any issues, please don't hesitate to post an issue report on github after consulting the FAQ page on http://www.fertilized-forests.org . For straightforward troubleshooting during the configuration process, see the file 'config.log'."))


