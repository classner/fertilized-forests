
file (GLOB Example_CPP "*.cpp")
foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string (TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_BINARY_DIR}/)
endforeach (OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

foreach (FNAME ${Example_CPP})
  get_filename_component (CLEANNAME ${FNAME} NAME)
  string (REPLACE ".cpp" "" CLEANNAME ${CLEANNAME})
  add_executable (${CLEANNAME} ${FNAME})
  target_compile_features (${CLEANNAME} PRIVATE ${REQ_CPP11_FEATURES})
  target_link_libraries (${CLEANNAME} fertilized ${Boost_LIBRARIES} ${OpenCV_COMPATIBLE_LIBRARIES})
  add_test ("${CLEANNAME}" ${CLEANNAME})
  install (TARGETS ${CLEANNAME} DESTINATION examples/c++)
endforeach (FNAME)

install (DIRECTORY ../matlab DESTINATION examples/)
install (DIRECTORY ../python DESTINATION examples/)

enable_testing()
