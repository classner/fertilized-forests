
FILE(GLOB_RECURSE Test_CPP "*.cpp")
add_executable(fertilized_tests ${Test_CPP})
target_compile_features(fertilized_tests PRIVATE ${REQ_CPP11_FEATURES})
target_compile_definitions(fertilized_tests PRIVATE -DBOOST_TEST_DYN_LINK)
target_link_libraries(fertilized_tests fertilized ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
add_test (TestsRun fertilized_tests --run_test=*/Correctness*)
enable_testing()
