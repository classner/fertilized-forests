# Fertilized Forests Decision Forest library

This project is currently being developed at the [Multimedia Computing
and Computer Vision Lab](http://www.multimedia-computing.de) at the
[University of Augsburg](http://www.uni-augsburg.de).

You can find detailed information including API documentation on
[http://www.fertilized-forests.org](http://www.fertilized-forests.org).

## Build status

The 'working' branch is `unstable`. Only versions that are completely tested
get merged to `master`, so `master` is always always stable, with all tests passing and all builds running. The current status of `unstable` is as follows:

* [![Build Status](https://travis-ci.org/ChrislS/fertilized-forests.svg?branch=unstable)](https://travis-ci.org/ChrislS/fertilized-forests) Build and tests of the core library - Linux
* [![Jenkins](https://img.shields.io/jenkins/s/http/www.christophlassner.de/jenkins/fertilized-continuous-release.svg)]() Build and tests, core library
* [![Jenkins](https://img.shields.io/jenkins/s/http/www.christophlassner.de/jenkins/fertilized-continuous-release-caffe.svg)]() Build and tests, core library and caffe feature extraction

## Installation

For Windows, you can find a pre-compiled ready to use package to
download [here](http://www.multimedia-computing.de/fertilized/pages/download.html).

For Linux and Mac OS, it is necessary to compile from source. Detailed
instructions can be found [here](http://www.multimedia-computing.de/fertilized/pages/compiling.html),
but I'll quickly sum up the steps for Ubuntu here:

* Install the prerequisites:

~~~~~
# Workaround for Ubuntu 13.10 so that OpenCL (an OpenCV dependency)
# does not pull in the nvidia drivers. Run only if you work on
# Ubuntu 13.10 and you are not using the proprietary nvidia drivers.
# http://askubuntu.com/questions/365897/how-to-install-opencv-without-nvidia-drivers
sudo apt-get install ocl-icd-libopencl1

# Install system dependencies.
sudo apt-get install m4 doxygen libboost-all-dev libeigen3-dev \
  python python-dev python-pip python-ply python-scipy \
  python-numpy build-essential libopencv-dev scons

# Install Python dependencies.
sudo pip install networkx
sudo pip install jinja2 cppheaderparser pillow \
  scikit-image matplotlib scikit-learn
~~~~~

* Download the source from github:

~~~~~
git clone https://github.com/ChrislS/fertilized-forests.git
cd fertilized-forests
~~~~~

* Get the required submodules:

~~~~~
git submodule update --init --recursive
~~~~~

* Set the EIGEN library include folder:

~~~~~
# For older Ubuntu versions, this must be /usr/local/include/eigen3
export EIGEN_ROOT=/usr/include/eigen3
~~~~~

* Compile and install

You can add `--jobs=X` to any of the scons build calls to speedup
the build process.

~~~~~
scons --generate-interfaces
scons --with-serialization --with-tests --with-examples
# Optional: install to your library and include folders
sudo scons --with-serialization install
# Optional: Matlab interface:
export MATLAB_ROOT=/usr/local/MATLAB/R20XXc
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/MATLAB/R20XXc/bin/glnxa64
scons --with-serialization --with-matlab
# Optional: Python interface:
scons --with-serialization --with-python
cd pyfertilized && sudo python setup.py install && cd ..
# Optional: generate the doxygen documentation
scons --generate-documentation
~~~~~

_Hint_: On Linux, you might run into an issue about MATLAB not finding
GLIBCXX_X.Y.ZZ. It's a known issue of MATLAB and easy to fix. You can
find the solution [here](https://fantasticzr.wordpress.com/2013/05/29/matlab-error-libstdc-so-version-glibcxx_3-4-15-not-found/).

