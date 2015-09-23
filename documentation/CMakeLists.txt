# Documentation target.
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # Generate doxygen configuration.
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  # Copy the resource files.
  foreach(FNAME fertilized_logo_bg.png footer.html header.html stylesheet.css)
    file(COPY
      ${CMAKE_CURRENT_SOURCE_DIR}/${FNAME}
      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
  endforeach(FNAME)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)
