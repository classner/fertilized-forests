
file (GLOB_RECURSE Common_CPP "*.cpp")
add_library (fertilized SHARED ${Common_CPP})
target_compile_features (fertilized PRIVATE ${REQ_CPP11_FEATURES})
target_compile_definitions (fertilized PRIVATE -D__BUILD_FERTILIZED_LIBRARY)
target_link_libraries (fertilized ${Boost_LIBRARIES} ${OpenCV_COMPATIBLE_LIBRARIES})
if (WITH_PYTHON)
  target_link_libraries (fertilized ${PYTHON_LIBRARIES})
endif()
if (APPLE)
  set_target_properties (fertilized PROPERTIES INSTALL_RPATH "@rpath")
endif()
if (WITH_CAFFE)
  # The CPU_ONLY flag is only added to not have CUDA dependencies pulled in
  # by caffe headers. It is still possible to use the GPU!
  target_compile_definitions (fertilized PRIVATE -DCAFFE_FEATURE_EXTRACTION_ENABLED)
  if (CAFFE_CPU_ONLY)
    target_compile_definitions (fertilized PRIVATE -DCPU_ONLY)
  endif()
  include_directories (${CAFFE_INCLUDE_DIRS} ${CUDA_INCLUDE_DIRS})
  target_link_libraries (fertilized ${CAFFE_LIBRARIES})
endif()

install (TARGETS fertilized DESTINATION lib)
if (WITH_PYTHON)
  add_custom_command (TARGET fertilized POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy
       "$<TARGET_FILE:fertilized>"
       "${CMAKE_BINARY_DIR}/bindings/python/fertilized/$<TARGET_FILE_NAME:fertilized>"
    COMMENT "Copying to python directory")
    install (TARGETS fertilized DESTINATION bindings/python/fertilized/)
endif()
if (WITH_MATLAB)
  add_custom_command (TARGET fertilized POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy
       "$<TARGET_FILE:fertilized>"
       "${CMAKE_BINARY_DIR}/bindings/matlab/fertilized/$<TARGET_FILE_NAME:fertilized>"
    COMMENT "Copying to MATLAB directory")
    install (TARGETS fertilized DESTINATION bindings/matlab/fertilized/)
endif()
add_custom_command (TARGET fertilized POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy
     "$<TARGET_FILE:fertilized>"
     "${CMAKE_BINARY_DIR}/tests/$<TARGET_FILE_NAME:fertilized>"
  COMMENT "Copying to test directory")
install (TARGETS fertilized DESTINATION tests/)
add_custom_command (TARGET fertilized POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy
     "$<TARGET_FILE:fertilized>"
     "${CMAKE_BINARY_DIR}/examples/c++/$<TARGET_FILE_NAME:fertilized>"
  COMMENT "Copying to C++ examples directory")
install (TARGETS fertilized DESTINATION examples/c++)
