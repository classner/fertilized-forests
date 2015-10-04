message(STATUS "Using custom Find${CMAKE_FIND_PACKAGE_NAME} module")

# Originally from
# https://github.com/mhauskn/dqn/blob/master/cmake/Modules/FindCAFFE.cmake
#
# The MIT License (MIT)
#
# Copyright (c) 2014 Yasuhiro Fujita
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# The following variables are optionally searched for defaults
#  CAFFE_ROOT_DIR:            Base directory where all GLOG components are found
#
# The following are set after configuration is done:
#  CAFFE_FOUND
#  CAFFE_INCLUDE_DIRS
#  CAFFE_LIBRARIES

include(FindPackageHandleStandardArgs)

set(CAFFE_ROOT_DIR "" CACHE PATH "Folder containing CAFFE")

find_path(CAFFE_INCLUDE_DIR caffe/caffe.hpp
  PATHS ${CAFFE_ROOT_DIR}
  PATH_SUFFIXES
  build/install include ../include)
find_path(CAFFE_PROTO_INCLUDE_DIR caffe/proto/caffe.pb.h
  PATHS ${CAFFE_ROOT_DIR}
  PATH_SUFFIXES
  build/install build/include include)

if (WIN32)
  find_library(CAFFE_LIBRARY caffe
    PATHS ${CAFFE_ROOT_DIR}
    PATH_SUFFIXES
    lib install/lib ../lib build/lib)
else()
  if (WIN32)
    if ("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
      find_library(CAFFE_LIBRARY caffe-d.lib
        PATHS ${CAFFE_ROOT_DIR}
        PATH_SUFFIXES
        lib install/lib ../lib build/lib)
    else()
      find_library(CAFFE_LIBRARY caffe.lib
        PATHS ${CAFFE_ROOT_DIR}
        PATH_SUFFIXES
        lib install/lib ../lib build/lib)
    endif()
  else()
    # Explicitly link to the shared library.
    find_library(CAFFE_LIBRARY libcaffe.so
      PATHS ${CAFFE_ROOT_DIR}
      PATH_SUFFIXES
      lib install/lib ../lib build/lib)
    endif()
endif()

find_package_handle_standard_args(CAFFE DEFAULT_MSG
  CAFFE_INCLUDE_DIR CAFFE_PROTO_INCLUDE_DIR CAFFE_LIBRARY)

if(CAFFE_FOUND)
  set(CAFFE_INCLUDE_DIRS ${CAFFE_INCLUDE_DIR} ${CAFFE_PROTO_INCLUDE_DIR})
  set(CAFFE_LIBRARIES ${CAFFE_LIBRARY})
endif()
