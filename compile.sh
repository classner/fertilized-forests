#!/bin/bash
# This file will be overwritten by running ./setup_environment.sh!
# The automated script will do the following steps automatically for you.
#
#######################
# Setup (just run once)
# The following code snippets work on Ubuntu:

# Workaround for Ubuntu 13.10 so that OpenCL (an OpenCV dependency)
# does not pull in the nvidia drivers. Run only if you work on
# Ubuntu 13.10 and you are not using the proprietary nvidia drivers.
# http://askubuntu.com/questions/365897/how-to-install-opencv-without-nvidia-drivers
# sudo apt-get install ocl-icd-libopencl1

# Install system dependencies.
#sudo apt-get install m4 doxygen libboost-all-dev libeigen3-dev \
#  python python-dev python-pip python-ply python-scipy \
#  python-numpy build-essential libopencv-dev scons

# Install Python dependencies.
# sudo pip install networkx
# sudo pip install jinja2 cppheaderparser pillow \
#   scikit-image matplotlib scikit-learn

######################
# Initialization
# Run after every `git pull`, etc.
# Get the submodules
# git submodule update --init --recursive

# Generate the interfaces
# scons --generate-interfaces

######################
# Compilation
echo You can speed up the build process by editing
echo "compile.sh" and increasing the --jobs=1
echo value. For further information and setup info, display/edit it.

echo Setting up paths...
# export BOOST_ROOT=...
# export BOOST_LIB_DIR=...
# export OPENCV_ROOT=...
# export OPENCV_LIB_DIR=...
# export PROTOBUF_ROOT=...
# export PROTOC=...
# export PATH="...:$PATH"
# export OPENBLAS_ROOT=...
# export MATLAB_ROOT=...
export EIGEN_ROOT="/usr/include/eigen3"

echo Compiling...
# Add --with-python to build the python interface.
# Add --with-matlab to build the MATLAB interface.
# Add --with-tests to build the tests.
# Add --with-examples to build the examples.
# Add --with-caffe to build the CAFFE feature extraction.
# Configure --caffe-model-dir to change the location of the CAFFE models for feature extraction.
# Configure --temp-folder to change the CAFFE tmp folder.
# Configure --cuda-architectures=20;30;35;50 to change the available compiled graphics card architectures.
# Add --cpu-only to build the CPU only version of CAFFE.
# Add --with-checks to enable assertions.
# Add --disable-optimizations to create an -Od build for debugging.
scons --with-serialization --with-tests --with-examples --jobs=1
