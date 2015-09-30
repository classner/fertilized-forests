
if (WITH_MATLAB)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/fertilized)
  foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string (TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_BINARY_DIR}/fertilized)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_BINARY_DIR}/fertilized)
  endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

  set (CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  include_directories (${Matlab_INCLUDE_DIRS})

  file (GLOB_RECURSE Matlab_CPP "*.cpp")
  add_library (matfertilized SHARED ${Matlab_CPP})
  target_compile_features (matfertilized PRIVATE ${REQ_CPP11_FEATURES})
  set_target_properties (matfertilized PROPERTIES PREFIX "")
  if (APPLE)
    set_target_properties (matfertilized PROPERTIES SUFFIX .so)
    set_target_properties (matfertilized PROPERTIES INSTALL_RPATH "@loader_path/")
  else()
    set_target_properties (matfertilized PROPERTIES INSTALL_RPATH "$ORIGIN/:$$ORIGIN")
  endif()
  target_compile_definitions (matfertilized PRIVATE -D__BUILD_MATFERTILIZED_LIBRARY)
  target_link_libraries (matfertilized
    fertilized
    ${Boost_LIBRARIES}
    ${OpenCV_COMATIBLE_LIBRARIES}
    ${Matlab_LIBRARIES}
  )

  # Header files.
  file (GLOB_RECURSE MATLAB_HEADERS "matlab_headers/*.h")
  foreach (HEADER ${MATLAB_HEADERS})
    file(COPY ${HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fertilized/headers/)
  endforeach (HEADER ${MATLAB_HEADERS})
  # Matlab base files.
  file (GLOB MATLAB_CORE "fertilized/*.m")
  foreach (HEADER ${MATLAB_CORE})
    file(COPY ${HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fertilized/)
  endforeach (HEADER ${MATLAB_CORE})
  # Matlab base files.
  file (GLOB MATLAB_GENERATED "fertilized/generated/*.m")
  foreach (HEADER ${MATLAB_GENERATED})
    file(COPY ${HEADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fertilized/generated/)
  endforeach (HEADER ${MATLAB_GENERATED})
endif()
