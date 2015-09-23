
FILE(GLOB Example_CPP "*.cpp")
foreach(FNAME ${Example_CPP})
  get_filename_component(CLEANNAME ${FNAME} NAME)
  # string( REPLACE ".cpp" "" CLEANNAME ${FNAME} )
  add_executable(${CLEANNAME} ${FNAME})
  target_compile_features(${CLEANNAME} PRIVATE ${REQ_CPP11_FEATURES})
  target_link_libraries(${CLEANNAME} fertilized ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
  add_test ("${CLEANNAME}" ${CLEANNAME})
endforeach(FNAME)

enable_testing()
