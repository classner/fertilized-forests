configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fertilized/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/fertilized/version.h @ONLY)

install (DIRECTORY fertilized DESTINATION include
  PATTERN "*.in" EXCLUDE)
install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} DESTINATION include)
