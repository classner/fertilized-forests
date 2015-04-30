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

STDOUT = open("setup-stdout.txt","wb")
STDERR = open("setup-stderr.txt","wb")

if len(sys.argv) > 9:
  BIN_FOLDER = sys.argv[9]
  if not BIN_FOLDER.endswith('/'):
    BIN_FOLDER = BIN_FOLDER + '/'
  print 'Python bin folder specified as %s.' % (BIN_FOLDER)
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
QUIET_MODE = len(sys.argv) > 1 and (sys.argv[1] == '--quiet')
if QUIET_MODE:
  ADD_REPO_SUFF = '-y'
else:
  ADD_REPO_SUFF = ''

if QUIET_MODE:
  puts(colored.yellow("Using quiet mode!"))
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
  APPLY_UBUNTU_12_PATCHES = not prompt.yn('Is your system based on the Ubuntu 12 package sources (in doubt, no)? If you answer yes, I will apply fixes to the package sources to make the required software packages available.', default='n')
  if not APPLY_UBUNTU_12_PATCHES:
    APPLY_UBUNTU_13_PATCHES = not prompt.yn('Is your system based on the Ubuntu 13 package sources AND you are not using the proprietary NVIDIA drivers (in doubt, no)? If you answer yes, a bug is fixed that erroneously pulls in NVIDIA drivers.', default='n')
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
OPENBLAS_INSTALL_DIR = None

#######################################
# Build tools
puts(colored.green('Installing build tools...'))
check_call(['apt-get', 'install', 'build-essential'], stdout=STDOUT, stderr=STDERR)

#######################################
# Ubuntu 12
if APPLY_UBUNTU_12_PATCHES:
  puts(colored.green('Applying Ubuntu 12 patches.'))
  if not QUIET_MODE:
    puts(colored.yellow('If you answer any of the following questions with "n", you will HAVE to care for installing a current version of the respective library and adjusting "setup_paths.sh" yourself. Otherwise, the build WILL fail!'))
  with indent(4):
    puts('Adding current gcc repository...')
    check_call(['add-apt-repository','ppa:ubuntu-toolchain-r/test', ADD_REPO_SUFF], stdout=STDOUT, stderr=STDERR)
    puts('Adding current OpenCV repository...')
    check_call(['add-apt-repository', 'ppa:yjwong/opencv2', ADD_REPO_SUFF], stdout=STDOUT, stderr=STDERR)
    puts('Adding current boost repository...')
    check_call(['add-apt-repository', 'ppa:boost-latest/ppa', ADD_REPO_SUFF], stdout=STDOUT, stderr=STDERR)
    puts('Updating package cache...')
    check_call(['apt-get', 'update'], stdout=STDOUT, stderr=STDERR)
    puts('Installing gcc 4.8...')
    check_call(['apt-get', 'install', 'g++-4.8'], stdout=STDOUT, stderr=STDERR)
    if not QUIET_MODE:
      SET_CXX_CC = prompt.yn('Should gcc-4.8 be registered as system compiler (CXX and CC environment variables will be set)?')
    if SET_CXX_CC:
      # Set environment variable.
      # c.t. http://stackoverflow.com/questions/1506010/how-to-use-export-with-python-on-linux
      os.environ['CXX'] = 'g++-4.8'
      os.environ['CC'] = 'gcc-4.8'
    if WITH_CAFFE:
      if QUIET_MODE or prompt.yn('Should I install a current version of OpenBLAS?'):
        with indent(4):
          puts('gfortran.')
          check_call(['apt-get', 'install', 'gfortran'], stdout=STDOUT, stderr=STDERR)
          check_call(['ln', '-s', '/usr/lib/x86_64-linux-gnu/libgfortran.so.3', '/usr/lib/x86_64-linux-gnu/libgfortran.so'], stdout=STDOUT, stderr=STDERR)
          puts('OpenBLAS.')
          check_call(['wget', 'http://github.com/xianyi/OpenBLAS/archive/v0.2.14.zip'], stdout=STDOUT, stderr=STDERR)
          check_call(['unzip', 'v0.2.14.zip'], stdout=STDOUT, stderr=STDERR)
          os.chdir('OpenBLAS-0.2.14')
          check_call(['make'], stdout=STDOUT, stderr=STDERR)
          check_call(['make', 'install', 'PREFIX=/usr/local/OpenBLAS'], stdout=STDOUT, stderr=STDERR)
          check_call(['ln', '-s', '/usr/local/OpenBLAS/lib/libopenblas.so', '/usr/local/lib/libopenblas.so.0'], stdout=STDOUT, stderr=STDERR)
          os.chdir('..')
          os.remove('v0.2.14.zip')
          shutil.rmtree('OpenBLAS-0.2.14', ignore_errors=True)
          OPENBLAS_INSTALL_DIR = '/usr/local/OpenBLAS'
      if QUIET_MODE or prompt.yn('Should I install a current version of GLOG?'):
        with indent(4):
          puts('glog.')
          check_call(['wget', 'https://github.com/google/glog/archive/v0.3.4.zip'], stdout=STDOUT, stderr=STDERR)
          check_call(['unzip', 'v0.3.4.zip'], stdout=STDOUT, stderr=STDERR)
          os.chdir('glog-0.3.4')
          check_call(['./configure'], stdout=STDOUT, stderr=STDERR)
          check_call(['make'], stdout=STDOUT, stderr=STDERR)
          check_call(['make', 'install'], stdout=STDOUT, stderr=STDERR)
          os.chdir('..')
          os.remove('v0.3.4.zip')
          shutil.rmtree('glog-0.3.4', ignore_errors=True)
      if QUIET_MODE or prompt.yn('Should I install a current version of boost?'):
        with indent(4):
          puts('boost.')
          check_call(['apt-get', 'install', 'libboost1.55-all-dev'], stdout=STDOUT, stderr=STDERR)
      if QUIET_MODE or prompt.yn('Should I install a current version of EIGEN?'):
        with indent(4):
          puts('eigen.')
          check_call(['wget', 'http://bitbucket.org/eigen/eigen/get/3.2.4.zip'], stdout=STDOUT, stderr=STDERR)
          check_call(['unzip', '3.2.4.zip', '-d', '/usr/include/eigen3'], stdout=STDOUT, stderr=STDERR)
          EIGEN_INSTALL_DIR = '/usr/include/eigen3/eigen-eigen-10219c95fe65'
          os.remove('3.2.4.zip')

#######################################
# Ubuntu 13
if APPLY_UBUNTU_13_PATCHES:
  puts(colored.green('Applying Ubuntu 13 patches.'))
  with indent(4):
    puts('OpenCL:')
    check_call(['apt-get', 'install', 'ocl-icd-libopencl1'], stdout=STDOUT, stderr=STDERR)

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

puts(colored.green('Installing system packages...'))
with indent(4):
  puts('OpenCV.')
  check_call(['apt-get', 'install', 'libopencv-dev'], stdout=STDOUT, stderr=STDERR)
  if not APPLY_UBUNTU_12_PATCHES:
    puts('boost.')
    check_call(['apt-get', 'install', 'libboost-all-dev'], stdout=STDOUT, stderr=STDERR)
    puts('eigen.')
    check_call(['apt-get', 'install', 'libeigen3-dev'], stdout=STDOUT, stderr=STDERR)
  try:
    check_call(['which', 'git'], stdout=STDOUT, stderr=STDERR)
  except:
    puts('git.')
    check_call(['apt-get', 'install', 'git-core'], stdout=STDOUT, stderr=STDERR)
  if WITH_CAFFE:
    puts(colored.yellow('Installing additional CAFFE dependencies...'))
    with indent(4):
      if not APPLY_UBUNTU_12_PATCHES:
        puts('OpenBLAS.')
        check_call(['apt-get', 'install', 'libopenblas-dev'], stdout=STDOUT, stderr=STDERR)
        puts('glog.')
        check_call(['apt-get', 'install', 'libgoogle-glog-dev'], stdout=STDOUT, stderr=STDERR)
      puts('protobuf.')
      check_call(['apt-get', 'install', 'libprotobuf-dev', 'protobuf-compiler'], stdout=STDOUT, stderr=STDERR)
      puts('hdf5.')
      check_call(['apt-get', 'install', 'libhdf5-serial-dev'], stdout=STDOUT, stderr=STDERR)
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
      orig_model_file = glob('./fertilized/feature_extraction/alexnet_extraction.prototxt')
      if not os.path.exists(model_filename):
        shutil.copyfile(os.path.abspath(str(orig_model_file[0])),
                        model_filename)
      mean_filename = os.path.join(alex_dir, 'alexnet_mean.txt')
      orig_mean_file = glob('./fertilized/feature_extraction/alexnet_mean.txt')
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
  check_call(['which', '%sconda' % (BIN_FOLDER)], stdout=STDOUT, stderr=STDERR)
  CONDA_AVAILABLE = True
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
    check_call(['%spip' % (BIN_FOLDER), 'install', mname], stdout=STDOUT, stderr=STDERR)

#######################################
# MATLAB
if WITH_MATLAB:
  puts(colored.green('Configuring for MATLAB...'))
  MATLAB_ROOT = prompt.query('Where is your MATLAB installed? This folder should have the subfolders "bin", "extern", etc. Finish the foldername without trailing backslash, e.g., "/usr/local/MATLAB/R2014a":', validators=[validators.PathValidator()])
  MATLAB_PATH_STRING = 'export MATLAB_ROOT="%s"' % (MATLAB_ROOT)
else:
  MATLAB_PATH_STRING = '# export MATLAB_ROOT=...'

#######################################
# Submodules
puts(colored.green('Pulling in submodules...'))
check_call(['git', 'submodule', 'update', '--init', '--recursive'], stdout=STDOUT, stderr=STDERR)

#######################################
# Generating interfaces
puts(colored.green('Generating interfaces...'))
check_call(['%sscons' % (BIN_FOLDER), '--generate-interfaces'])
# Cleanup
if os.path.exists('config.log'):
  os.remove('config.log')
if os.path.exists('.sconsign.dblite'):
  os.remove('.sconsign.dblite')
if os.path.exists('.sconf_temp'):
  shutil.rmtree('.sconf_temp')

#######################################
# File generation
puts(colored.green('Generating setup_paths.sh...'))
if SET_CXX_CC:
  CXX_CC_CODE = 'export CXX="g++-4.8" CC="gcc-4.8"'
else:
  CXX_CC_CODE = ''
if OPENBLAS_INSTALL_DIR is None:
  OPENBLAS_CODE = '# export OPENBLAS_ROOT=...'
else:
  OPENBLAS_CODE = 'export OPENBLAS_ROOT="%s"' % (OPENBLAS_INSTALL_DIR)
with open('setup_paths.sh', 'w') as outfile:
  outfile.write(r"""
# Modify this file as required.
# export BOOST_ROOT=...
# export BOOST_LIB_DIR=...
# export OPENCV_ROOT=...
# export OPENCV_LIB_DIR=...
# export PROTOBUF_ROOT=...
# export PROTOC=...
# export PATH="...:$PATH"
%s
%s
%s
export EIGEN_ROOT="%s"
""" % (OPENBLAS_CODE, CXX_CC_CODE, MATLAB_PATH_STRING, EIGEN_INSTALL_DIR))
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


