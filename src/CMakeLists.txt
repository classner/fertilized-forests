
FILE(GLOB_RECURSE Common_CPP "*.cpp")
add_library(fertilized SHARED ${Common_CPP})
target_compile_features(fertilized PRIVATE ${REQ_CPP11_FEATURES})
target_compile_definitions(fertilized PRIVATE -D__BUILD_FERTILIZED_LIBRARY)
target_link_libraries(fertilized ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
if (WITH_PYTHON)
  target_link_libraries(fertilized ${PYTHON_LIBRARIES})
endif()

install (TARGETS fertilized DESTINATION lib)
install (TARGETS fertilized DESTINATION python/fertilized)
