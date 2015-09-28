
if (WITH_PYTHON)
  set (dir ${CMAKE_CURRENT_BINARY_DIR}/fertilized/)
  foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_BINARY_DIR}/fertilized )
  endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
  set (CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
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
      list (APPEND CHUNK_LIST "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp")
      math (EXPR CHUNK_ELEMS "${CHUNK_ELEMS}+1")
      math (EXPR ELEM_IDX "${ELEM_IDX}+1")
    endwhile (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp" AND CHUNK_ELEMS LESS 50)
    list (APPEND CHUNK_LIST "${CMAKE_CURRENT_SOURCE_DIR}/pyfertilized_${PFPART}.cpp")
    add_library ("pyfertilized_${PFPART}" SHARED ${CHUNK_LIST})
    list (APPEND LIBLIST "pyfertilized_${PFPART}")
    set_target_properties ("pyfertilized_${PFPART}" PROPERTIES PREFIX "")
    if (APPLE)
      set_target_properties ("pyfertilized_${PFPART}" PROPERTIES SUFFIX .so)
      set_target_properties ("pyfertilized_${PFPART}" PROPERTIES INSTALL_RPATH "@loader_path/")
    endif()
    if (WIN32)
      set_target_properties ("pyfertilized_${PFPART}" PROPERTIES SUFFIX .pyd)
    endif()
    if (LINUX)
      set_target_properties ("pyfertilized_${PFPART}" PROPERTIES INSTALL_RPATH "$ORIGIN/:$$ORIGIN")
    endif()
    target_compile_features ("pyfertilized_${PFPART}" PRIVATE ${REQ_CPP11_FEATURES})
    target_link_libraries ("pyfertilized_${PFPART}" fertilized boost_numpy ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
    math (EXPR PFPART "${PFPART}+1")
  endwhile (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/exporters/__${ELEM_IDX}_exporter.cpp")

  file (GLOB_RECURSE Python_MF_CPP
    "exporters_mod_funcs/*.cpp"
    "pyfertilized_mf.cpp"
  )

  add_library (pyfertilized_mf SHARED ${Python_MF_CPP})
  set_target_properties (pyfertilized_mf PROPERTIES PREFIX "")
  if (APPLE)
    set_target_properties (pyfertilized_mf PROPERTIES SUFFIX .so)
  endif()
  if (APPLE)
    set_target_properties (pyfertilized_mf PROPERTIES SUFFIX .so)
    set_target_properties (pyfertilized_mf PROPERTIES INSTALL_RPATH "@loader_path/")
  endif()
  if (WIN32)
    set_target_properties (pyfertilized_mf PROPERTIES SUFFIX .pyd)
  endif()
  if (LINUX)
    set_target_properties (pyfertilized_mf PROPERTIES INSTALL_RPATH "$ORIGIN/:$$ORIGIN")
  endif()
  target_link_libraries (pyfertilized_mf fertilized boost_numpy ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})
  target_compile_features (pyfertilized_mf PRIVATE ${REQ_CPP11_FEATURES})
  list (APPEND LIBLIST pyfertilized_mf)

  file (GLOB_RECURSE Python_VEC_CPP
    "exporters_vec_types/*.cpp"
    "pyfertilized_vec.cpp"
  )
  add_library (pyfertilized_vec SHARED ${Python_VEC_CPP})
  set_target_properties (pyfertilized_vec PROPERTIES PREFIX "")
  if (APPLE)
    set_target_properties (pyfertilized_vec PROPERTIES SUFFIX .so)
  endif()
  if (APPLE)
    set_target_properties (pyfertilized_vec PROPERTIES SUFFIX .so)
    set_target_properties (pyfertilized_vec PROPERTIES INSTALL_RPATH "@loader_path/")
  endif()
  if (WIN32)
    set_target_properties (pyfertilized_vec PROPERTIES SUFFIX .pyd)
  endif()
  if (LINUX)
    set_target_properties (pyfertilized_vec PROPERTIES INSTALL_RPATH "$ORIGIN/:$$ORIGIN")
  endif()

  target_link_libraries (pyfertilized_vec fertilized boost_numpy ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${OpenCV_LIBRARIES})
  target_compile_features (pyfertilized_vec PRIVATE ${REQ_CPP11_FEATURES})
  list(APPEND LIBLIST "pyfertilized_vec")

  # Prepare for setuptools installation.
  file (COPY fertilized/__init__.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fertilized/)
  file (COPY fertilized/TypeTranslations.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fertilized/)
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in
                  ${CMAKE_CURRENT_BINARY_DIR}/setup.py @ONLY)

  # On installation, run setuptools.
  install (CODE "exec_program(${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR} ARGS setup.py install)")

  # Add tests.
  add_test (NAME py_classification COMMAND ${PYTHON_EXECUTABLE} classification.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_dnn_feature_extraction COMMAND ${PYTHON_EXECUTABLE} dnn_feature_extraction.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_effect_depth COMMAND ${PYTHON_EXECUTABLE} effect_depth.py quiet
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_effect_weak_learner COMMAND ${PYTHON_EXECUTABLE} effect_weak_learner_rand.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_overview COMMAND ${PYTHON_EXECUTABLE} overview.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_custom COMMAND ${PYTHON_EXECUTABLE} custom.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_spiral COMMAND ${PYTHON_EXECUTABLE} spiral_rf.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_threshold_classifiers COMMAND ${PYTHON_EXECUTABLE} threshold_classifiers.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_regression COMMAND ${PYTHON_EXECUTABLE} regression.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
  add_test (NAME py_serialization COMMAND ${PYTHON_EXECUTABLE} serialization.py quiet
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/python)
endif()
