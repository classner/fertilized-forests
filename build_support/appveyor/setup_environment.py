
import sys
import os
import subprocess
from subprocess import check_call, Popen, PIPE
import time
import urllib
import shutil
from glob import glob
import zipfile

STDOUT = open("setup-stdout.txt","wb")
STDERR = open("setup-stderr.txt","wb")
PIP = 'C:\Anaconda\Scripts\pip'
VSVERSION_FIT = True
QUIET_MODE = True

#######################################
# Console fanciness
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
if QUIET_MODE:
  DOWNLOAD_HOOK = None
else:
  DOWNLOAD_HOOK = download_reporthook

#######################################
# Check for CLINT
try:
  import clint
  print "Python CLINT detected."
except:
  print "Python CLINT not found. Installing..."
  check_call([PIP, "install", "clint"], stdout=STDOUT, stderr=STDERR)
  print "Installation complete."
  import clint

from clint.textui import prompt, validators, colored, puts, indent

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
                           'nuget.exe',
                           DOWNLOAD_HOOK)
    puts('')

########################################
# Packages
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
    if not QUIET_MODE and VSVERSION_FIT:
        SPECIFY_PATH = not prompt.yn(indents + "Do you want to use your own version of %s?" % (name), default='n')
    if SPECIFY_PATH or not VSVERSION_FIT:
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
                with indent(4):
                    puts('Downloading...')
                    urllib.urlretrieve(download_url,
                                       download_filename,
                                       DOWNLOAD_HOOK)
                    puts('Installing...')
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
        check_call(['nuget', 'install', package_name, '-Version', '1.58.0', '-OutputDirectory', 'nuget-deps', '-ExcludeVersion'])
    copy_contents(r'nuget-deps\%s\lib\native\address-model-64\lib' % (package_name),
                  r'nuget-deps\boost-compiled\stage\lib')

puts(colored.green('Installing packages...'))
if not os.path.exists('nuget-deps'):
    os.mkdir('nuget-deps')
with indent(4):
  puts('Eigen3.')
  EIGEN_ROOT, own = configure_package('Eigen', [r'Eigen\Eigen'])
  if not own:
      EIGEN_ROOT += r'\build\native\include'
  puts('Boost.')
  if not os.path.exists(r'nuget-deps\boost-compiled'):
      os.mkdir(r'nuget-deps\boost-compiled')
  BOOST_ROOT, own = configure_package('boost', ['boost', r'stage\lib'], version='1.58.0')
  if not own:
      if not os.path.exists(r'nuget-deps\boost-compiled\boost'):
          shutil.move(r'nuget-deps\boost\lib\native\include\boost',
                      r'nuget-deps\boost-compiled\boost')
      if not os.path.exists(r'nuget-deps\boost-compiled\stage'):
          os.mkdir(r'nuget-deps\boost-compiled\stage')
      if not os.path.exists(r'nuget-deps\boost-compiled\stage\lib'):
          os.mkdir(r'nuget-deps\boost-compiled\stage\lib')
      install_boost_binary('chrono')
      install_boost_binary('serialization')
      install_boost_binary('thread')
      install_boost_binary('unit_test_framework')
      install_boost_binary('wserialization')
      install_boost_binary('test_exec_monitor')
      install_boost_binary('system')
      install_boost_binary('filesystem')
      # if not os.path.exists(r'boost_python_2.7.zip'):
          # puts(colored.yellow('Using a prepared version of boost python for Python 2.7. '
                              # 'If you want to use the library with a different version of '
                              # 'Python, you can, but will have to use a self-compiled version '
                              # 'of boost with your specific Python.'))
          # urllib.urlretrieve('http://www.multimedia-computing.de/fertilized/files/cache/boost_python_2.7.zip',
                             # 'boost_python_2.7.zip',
                             # DOWNLOAD_HOOK)
          # bpcache_zip = zipfile.ZipFile('boost_python_2.7.zip')
          # bpcache_zip.extractall(path=r'nuget-deps\boost-compiled\stage\lib')
      install_boost_binary('date_time')
      BOOST_ROOT += '-compiled'
  puts('CMake 3.3.')
  urllib.urlretrieve('https://cmake.org/files/v3.3/cmake-3.3.2-win32-x86.zip',
                     'cmake.zip',
                     DOWNLOAD_HOOK)
  cmake_zip = zipfile.ZipFile('cmake.zip')
  cmake_zip.extractall(path=r'cmake')
