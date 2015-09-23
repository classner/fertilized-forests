
if (WITH_PYTHON)
  # Take care of Boost.NumPy.
  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Boost.NumPy/libs/numpy/cmake ${CMAKE_MODULE_PATH})
  find_package(NumPy REQUIRED)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Boost.NumPy)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Boost.NumPy/libs/numpy/src)

  # Chunk the python parts up to have faster compilation and lower memory
  # usage. Otherwise, memory requirements rise quickly on Windows machines
  # at link time.
  set (LIBLIST )
  set (PFPART 0)
  set (ELEM_IDX 0)
  while (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp")
    set (CHUNK_ELEMS 0)
    set (CHUNK_LIST )
    while (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp" AND CHUNK_ELEMS LESS 50)
      list(APPEND CHUNK_LIST "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp")
      MATH(EXPR CHUNK_ELEMS "${CHUNK_ELEMS}+1")
      MATH(EXPR ELEM_IDX "${ELEM_IDX}+1")
    endwhile (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp" AND CHUNK_ELEMS LESS 50)
    list(APPEND CHUNK_LIST "${CMAKE_CURRENT_SOURCE_DIR}/pyfertilized_${PFPART}.cpp")
    add_library("pyfertilized_${PFPART}" SHARED ${CHUNK_LIST})
    list(APPEND LIBLIST "pyfertilized_${PFPART}")
    set_target_properties("pyfertilized_${PFPART}" PROPERTIES PREFIX "")
    set_target_properties("pyfertilized_${PFPART}" PROPERTIES INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")
    target_compile_features("pyfertilized_${PFPART}" PRIVATE ${REQ_CPP11_FEATURES})
    target_link_libraries("pyfertilized_${PFPART}" fertilized boost_numpy ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
    MATH(EXPR PFPART "${PFPART}+1")
  endwhile (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp")

  FILE(GLOB_RECURSE Python_MF_CPP
    "exporters_mod_funcs/*.cpp"
    "pyfertilized_mf.cpp"
  )

  add_library(pyfertilized_mf SHARED ${Python_MF_CPP})
  set_target_properties(pyfertilized_mf PROPERTIES PREFIX "")
  set_target_properties(pyfertilized_mf PROPERTIES INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")
  target_link_libraries (pyfertilized_mf fertilized boost_numpy ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
  target_compile_features(pyfertilized_mf PRIVATE ${REQ_CPP11_FEATURES})
  list(APPEND LIBLIST pyfertilized_mf)

  FILE(GLOB_RECURSE Python_VEC_CPP
    "exporters_vec_types/*.cpp"
    "pyfertilized_vec.cpp"
  )
  add_library(pyfertilized_vec SHARED ${Python_VEC_CPP})
  set_target_properties(pyfertilized_vec PROPERTIES PREFIX "")
  set_target_properties(pyfertilized_vec PROPERTIES INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")
  target_link_libraries (pyfertilized_vec fertilized boost_numpy ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${OpenCV_LIBRARIES})
  target_compile_features(pyfertilized_vec PRIVATE ${REQ_CPP11_FEATURES})
  list(APPEND LIBLIST "pyfertilized_vec")

  install(DIRECTORY fertilized DESTINATION python)
  install(TARGETS ${LIBLIST} DESTINATION python/fertilized)

endif()
