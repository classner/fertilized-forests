cmake_minimum_required (VERSION 3.2)
# Requirement for the findMatlab script shipped with CMake.

project (fertilized C CXX)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
set (CMAKE_INSTALL_PREFIX "/home/christoph/tmp/fertilizedtest")
# Versioning.
set (fertilized_VERSION_MAJOR 1)
set (fertilized_VERSION_MINOR 2)
set (fertilized_VERSION_PATCH 0)
set (fertilized_VERSION ${fertilized_VERSION_MAJOR}.${fertilized_VERSION_MINOR}.${fertilized_VERSION_PATCH})

# Configure the library.
include_directories (include)
add_subdirectory (include)
set (BOOST_COMPONENTS date_time
                      serialization
                      filesystem
                      system
                      unit_test_framework
                      thread)

option (WITH_SERIALIZATION "Build the serialization routines" ON)
find_package(PythonInterp)
find_package(PythonLibs)
if (PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
  option (WITH_PYTHON "Build the Python interface" ON)
endif()
find_package(Matlab)
if (MATLAB_FOUND)
  option (WITH_MATLAB "Build the MATLAB interface" ON)
endif()

if (WITH_SERIALIZATION)
  message(STATUS "Building serialization routines")
  add_definitions (-DSERIALIZATION_ENABLED)
endif()
if (WITH_PYTHON)
  MESSAGE(STATUS "Building with Python support")
  add_definitions (-DPYTHON_ENABLED)
  include_directories(${PYTHON_INCLUDE_PATH})
  if(${PYTHON_VERSION_STRING} GREATER 3.0)
    message(STATUS "Using Python3")
    list(APPEND BOOST_COMPONENTS python3)
  else()
    message(STATUS "Using Python2")
    list(APPEND BOOST_COMPONENTS python)
  endif()
endif()
message(STATUS "Building with OpenCV")
find_package(OpenCV REQUIRED core imgproc highgui)

# Use C++11 features.
set(REQ_CPP11_FEATURES
    cxx_strong_enums
    cxx_constexpr
    cxx_auto_type)

# Check for OpenMP support.
find_package (OpenMP)

# Configure the dependencies.
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
find_package(Eigen3 REQUIRED)
add_definitions(-DEIGEN_MPL2_ONLY)
SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
include_directories(${EIGEN3_INCLUDE_DIR})

# Create the library.
add_subdirectory(src)

# Create the tests.
add_subdirectory(tests)
enable_testing()

# Create the bindings.
add_subdirectory(bindings/python)

# Create the examples.
add_subdirectory(examples/c++)

# Create the documentation.
add_subdirectory(documentation)

# Summarize.
MESSAGE(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "Library Type: " ${LIB_TYPE})
MESSAGE(STATUS "Compiler flags:" ${CMAKE_CXX_COMPILE_FLAGS})
MESSAGE(STATUS "Compiler cxx debug flags:" ${CMAKE_CXX_FLAGS_DEBUG})
MESSAGE(STATUS "Compiler cxx release flags:" ${CMAKE_CXX_FLAGS_RELEASE})
MESSAGE(STATUS "Compiler cxx min size flags:" ${CMAKE_CXX_FLAGS_MINSIZEREL})
MESSAGE(STATUS "Compiler cxx flags:" ${CMAKE_CXX_FLAGS})
