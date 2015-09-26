cmake_minimum_required (VERSION 3.2)
# Requirement for the findMatlab script shipped with CMake.

project (fertilized C CXX)
list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build_support/cmake/modules)

# Versioning.
set (fertilized_VERSION_MAJOR 1)
set (fertilized_VERSION_MINOR 0)
set (fertilized_VERSION_PATCH 2)
set (fertilized_VERSION
  "${fertilized_VERSION_MAJOR}.${fertilized_VERSION_MINOR}.${fertilized_VERSION_PATCH}")
set (fertilized_VERSION_NUMBER
  "${fertilized_VERSION_MAJOR}${fertilized_VERSION_MINOR}${fertilized_VERSION_PATCH}")

# Set a default build type if none was specified.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message (STATUS "Setting build type to 'Release' since none was specified.")
  set (CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui.
  set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Setup the library.
include_directories (include)
include_directories (${CMAKE_CURRENT_BINARY_DIR}/include)
add_subdirectory (include)
set (BOOST_COMPONENTS date_time
                      serialization
                      filesystem
                      system
                      unit_test_framework
                      thread)
# Options.
option (WITH_SERIALIZATION "Build the serialization routines" ON)
# Python.
find_package (PythonInterp)
find_package (PythonLibs)
if (PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
  option (WITH_PYTHON "Build the Python interface" ON)
else()
  option (WITH_PYTHON "Build the Python interface" OFF)
endif()
# Matlab.
find_package (Matlab)
if (MATLAB_FOUND)
  option (WITH_MATLAB "Build the MATLAB interface" ON)
else()
  option (WITH_MATLAB "Build the MATLAB interface" OFF)
endif()
# OpenCV.
find_package (OpenCV COMPONENTS core imgproc highgui)
if (OpenCV_FOUND)
  option (WITH_OPENCV "Enable feature extraction with OpenCV" ON)
else()
  option (WITH_OPENCV "Enable feature extraction with OpenCV" OFF)
endif()
# Caffe.
find_package (Caffe)
if (CAFFE_FOUND AND OpenCV_FOUND)
  option (WITH_CAFFE "Build the caffe feature extractor" ON)
else()
  option (WITH_CAFFE "Build the caffe feature extractor" OFF)
endif()
# CUDA.
find_package (CUDA)
if (CUDA_FOUND)
  option (CAFFE_CPU_ONLY "Use the CPU only version of CAFFE" OFF)
else()
  option (CAFFE_CPU_ONLY "Use the CPU only version of CAFFE" ON)
endif()

# Configure.
if (WITH_SERIALIZATION)
  add_definitions (-DSERIALIZATION_ENABLED)
endif()
if (WITH_PYTHON)
  if (NOT PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
    message (FATAL_ERROR "You specified WITH_PYTHON, but interpreter or libs \
                          weren't found!")
  endif ()
  add_definitions (-DPYTHON_ENABLED)
  include_directories (${PYTHON_INCLUDE_PATH})
  if (${PYTHON_VERSION_STRING} GREATER 3.0)
    message (STATUS "Using Python3")
    list (APPEND BOOST_COMPONENTS python3)
  else()
    message (STATUS "Using Python2")
    list (APPEND BOOST_COMPONENTS python)
  endif ()
  # Take care of Boost.NumPy.
  set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/build_support/external/Boost.NumPy/libs/numpy/cmake ${CMAKE_MODULE_PATH})
endif ()
if (WITH_MATLAB)
  if (NOT MATLAB_FOUND)
    message (FATAL_ERROR "You specified WITH_MATLAB, but it wasn't found!\
                          Try to run CMAKE with -DMatlab_ROOT_DIR=...!")
  endif ()
endif ()
if (WITH_OPENCV)
  if (NOT OpenCV_FOUND)
    message (FATAL_ERROR "You specified WITH_OPENCV, but it wasn't found!")
  endif ()
endif ()
if (WITH_CAFFE)
  if (NOT CAFFE_FOUND)
    message (FATAL_ERROR "You specified WITH_CAFFE, but it wasn't found!\
                          Try to run CMAKE with -DCAFFE_ROOT_DIR=...!\
                          It is necessary to build the shared library of\
                          caffe by configuring it with `-DBUILD_SHARED_LIBS=ON`\
                          on Linux&Mac. You should afterwards either install\
                          it or set -DCAFFE_ROOT_DIR to the path of the\
                          caffe or its build oe install directory.")
  endif ()
  if (NOT WITH_OPENCV)
    message (FATAL_ERROR "When building with CAFFE, OpenCV is required!")
  endif ()
  if (NOT CAFFE_CPU_ONLY AND NOT CUDA_FOUND)
    message (FATAL_ERROR "You specified to build the not CPU only version of\
                          CAFFE but CUDA could not be found!")
  endif ()
endif ()

# Use C++11 features.
set (REQ_CPP11_FEATURES
     cxx_strong_enums
     cxx_constexpr
     cxx_auto_type)

# Check for OpenMP support.
find_package (OpenMP)
if (OPENMP_FOUND)
  list (APPEND CMAKE_CXX_FLAGS ${OpenMP_CXX_FLAGS})
endif ()

# Fix clang warnings.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  list (APPEND CMAKE_CXX_FLAGS "-Wno-tautological-compare -Wno-logical-op-parentheses")
endif()

# Configure the dependencies.
find_package (Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
include_directories (${Boost_INCLUDE_DIRS})
if (WITH_PYTHON)
  find_package (NumPy REQUIRED)
  include_directories (${NUMPY_INCLUDE_DIRS})
  include_directories (${PROJECT_SOURCE_DIR}/build_support/external/Boost.NumPy)
  add_subdirectory (${PROJECT_SOURCE_DIR}/build_support/external/Boost.NumPy/libs/numpy/src)
endif()
find_package(Eigen3 REQUIRED)
add_definitions (-DEIGEN_MPL2_ONLY)
include_directories (${EIGEN3_INCLUDE_DIR})


# Targets.
# Create the library.
add_subdirectory (src)

# Create the tests.
add_subdirectory (tests)
enable_testing ()

# Create the bindings.
add_subdirectory (bindings/python)
add_subdirectory (bindings/matlab)

# Create the examples.
add_subdirectory (examples/c++)

# Create the documentation.
add_subdirectory (documentation)

# Summarize.
message ("--------------------------------------------------------------------")
message ("Configuration summary")
message ("--------------------------------------------------------------------")
message ("")
message ("Library options:")
if (WITH_SERIALIZATION)
  message ("  Building serialization routines")
else ()
  message ("  Building without serialization routines")
endif ()
if (WITH_PYTHON)
  message ("  Building Python bindings for version " ${PYTHONLIBS_VERSION_STRING})
  message ("  Python interpreter:\t" ${PYTHON_EXECUTABLE})
  message ("  Python include path:\t" ${PYTHON_INCLUDE_DIRS})
  message ("  Python library:\t" ${PYTHON_LIBRARIES})
else ()
  message ("  Not building Python bindings")
endif ()
if (WITH_MATLAB)
  message ("  Building MATLAB bindings")
else ()
  message ("  Not building MATLAB bindings")
endif ()
if (WITH_OPENCV)
  message ("  Building with OpenCV")
else ()
  message ("  Building without OpenCV")
endif ()
if (WITH_CAFFE)
  message("  Building caffe interface")
  if (CAFFE_CPU_ONLY)
    message ("    Building CPU only interface (must match CAFFE compilation!)")
  else ()
    message ("    Building CPU&GPU interface (must match CAFFE compilation!)")
  endif ()
else ()
  message ("  Not building caffe interface")
endif ()
message ("")
message ("Compiler options:")
message ("  Build type: " ${CMAKE_BUILD_TYPE})
message ("  Compiler flags: " ${CMAKE_CXX_COMPILE_FLAGS})
message ("  Compiler cxx debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})
message ("  Compiler cxx release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message ("  Compiler cxx min size flags: " ${CMAKE_CXX_FLAGS_MINSIZEREL})
message ("  Compiler cxx flags: " ${CMAKE_CXX_FLAGS})
message ("")
message ("Installation options:")
message ("  Installation prefix path: " ${CMAKE_INSTALL_PREFIX})
message ("")
message ("--------------------------------------------------------------------")
