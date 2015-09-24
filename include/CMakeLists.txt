configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fertilized/version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/fertilized/version.h @ONLY)

install (DIRECTORY fertilized DESTINATION include
  PATTERN "*.in" EXCLUDE)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/fertilized/version.h
  DESTINATION include/fertilized/)
