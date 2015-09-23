
if (WITH_MATLAB)
  FILE(GLOB_RECURSE Matlab_CPP "*.cpp")
  add_library(matfertilized SHARED ${Matlab_CPP})
  target_compile_features(matfertilized PRIVATE ${REQ_CPP11_FEATURES})
  include_directories(${Matlab_INCLUDE_DIRS})
  target_link_libraries(matfertilized
    fertilized
    ${Boost_LIBRARIES}
    ${OpenCV_LIBRARIES}
    ${Matlab_LIBRARIES})
endif()
