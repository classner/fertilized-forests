@echo off
set BOOST_ROOT=C:\libraries\boost_1_56_0
REM set BOOST_LIB_DIR=%BOOST_ROOT%\whereeveryoucompiledto
set OPENCV_ROOT=C:\libraries\opencv\2.4.11\build
set OPENCV_LIB_DIR=%OPENCV_ROOT%\x64\vc12\lib
set OPENCV_VERSION=2411
set EIGEN_ROOT=C:\libraries\eigen
REM Only required if you build --with-matlab
REM set MATLAB_ROOT=C:\Program Files\MATLAB\R2014a
REM Only required if you build --with-caffe
REM set HDF5_ROOT=C:\libraries\HDF5\1.8.14
REM set OPENBLAS_ROOT=C:\libraries\OpenBLAS-v0.2.14
REM set PROTOBUF_ROOT=C:\libraries\protobuf-2.6.1
REM set PROTOC=%PROTOBUF_ROOT%\vsprojects\x64\Release\protoc.exe

IF NOT "%FERTILIZED_ADDED_PATH%"=="" goto notextending
  echo Extending path!
  set PATH=%PATH%;%OPENCV_ROOT%\x64\vc12\bin;
  IF "%HDF5_ROOT%"=="" goto hdf5done
  set PATH=%PATH%;%HDF5_ROOT%\bin;
:hdf5done
  IF "%OPENBLAS_ROOT%"=="" goto openblasdone
  set PATH=%PATH%;%OPENBLAS_ROOT%\bin;
:openblasdone
  IF "%MATLAB_ROOT%"=="" goto matlabdone
  set PATH=%PATH%;%MATLAB_ROOT%\bin\win64;
:matlabdone
  set FERTILIZED_ADDED_PATH=1
  goto end
:notextending
  echo Path already extended. No update.

:end
