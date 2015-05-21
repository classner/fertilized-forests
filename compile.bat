@echo off
REM This file will be overwritten by running setup_environment.bat!
REM ######################
REM Initialization
REM Run after every `git pull`, etc.
REM Get the submodules
REM git submodule update --init --recursive
REM Generate the interfaces
REM scons --generate-interfaces

REM #######################
REM Setup environment
echo You can speed up the build process by editing
echo "compile.bat" and increasing the --jobs=1
echo value. For further information and setup info, display/edit it.

REM Setting up paths.
set BOOST_ROOT=C:\libraries\boost-compiled
REM Whereever the compiled files are.
set BOOST_LIB_DIR=%BOOST_ROOT%\stage\lib
set OPENCV_ROOT=C:\libraries\opencv\build
set OPENCV_LIB_DIR=%OPENCV_ROOT%\x64\vc12\lib
set OPENCV_VERSION=2411
set EIGEN_ROOT=C:\libraries\Eigen\build\native\include
REM Only required if you build --with-matlab
REM set MATLAB_ROOT=C:\Program Files\MATLAB\R2014a
REM Only required if you build --with-caffe
REM set HDF5_ROOT=C:\Users\christoph\Documents\fertilized-forests\nuget-deps\hdf5
REM set HDF5_LIB_DIR=C:\Users\christoph\Documents\fertilized-forests\nuget-deps\hdf5\lib
REM set OPENBLAS_ROOT=C:\Users\christoph\Documents\fertilized-forests\nuget-deps\OpenBLAS\lib\native
REM set OPENBLAS_LIB_DIR=C:\Users\christoph\Documents\fertilized-forests\nuget-deps\OpenBLAS\lib\native\lib\x64
REM set PROTOBUF_INCLUDE_DIR=C:\Users\christoph\Documents\fertilized-forests\nuget-deps\protobuf-v120\build\native\include
REM set PROTOBUF_LIB_DIR=C:\Users\christoph\Documents\fertilized-forests\nuget-deps\protobuf-v120\build\native\lib\x64\v120\Release
REM set PROTOC=C:\Users\christoph\Documents\fertilized-forests\nuget-deps\protoc\protoc.exe

IF NOT "%FERTILIZED_ADDED_PATH%"=="" goto notextending
  echo Extending path!
  set PATH=%PATH%;%OPENCV_ROOT%\x64\vc12\bin;%BOOST_LIB_DIR%;
  IF "%HDF5_ROOT%"=="" goto hdf5done
  set PATH=%PATH%;C:\Users\christoph\Documents\fertilized-forests\nuget-deps\hdf5\bin;
:hdf5done
  IF "%OPENBLAS_ROOT%"=="" goto openblasdone
  set PATH=%PATH%;C:\Users\christoph\Documents\fertilized-forests\nuget-deps\OpenBLAS\lib\native\bin\x64;
:openblasdone
  IF "%MATLAB_ROOT%"=="" goto matlabdone
  set PATH=%PATH%;%MATLAB_ROOT%\bin\win64;
:matlabdone
  set FERTILIZED_ADDED_PATH=1
  goto end
:notextending
  echo Path already extended. No update.

:end

REM #######################
REM Compile
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
scons --with-serialization --with-tests --with-examples --jobs=1

