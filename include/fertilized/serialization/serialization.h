/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_SERIALIZATION_SERIALIZATION_H_
#define FERTILIZED_SERIALIZATION_SERIALIZATION_H_

#include <vector>
#include <string>

#include "../global.h"
#include "../types.h"


namespace fertilized {

#ifdef SERIALIZATION_ENABLED

  template <class Archive>
  void register_fertilized_objects_(Archive &ar,
                                    const bool &always_register=true,
                                    const unsigned int &serialization_library_version=0U);

  /**
   * Serializes any library object into an std::string.
   *
   * Library objects and types are supported as specified in their documentation.
   */
  template <typename T>
  DllExport std::string serialize(const T *, const bool &direct=false);

  /**
   * Deserializes a library object from a stringstream.
   *
   * Library objects and types are supported as specified in their documentation.
   */
  template <typename T>
  DllExport T* deserialize(std::stringstream &);

  /**
   * Deserializes a library object from a stringstream.
   *
   * Library objects and types are supported as specified in their documentation.
   */
  template <typename T>
  DllExport void deserialize(std::stringstream &, T*);

#else

  template <typename T>
  std::string serialize(T *, const bool &direct=false) {
    throw Fertilized_Exception("To use the libraries serialization features, "
      "you must define the symbol SERIALIZATION_ENABLED with a preprocessor "
      "define (or use SCons with the flag --with-serialization). "
      "This adds a dependency to boost serialization.");
    return std::string();
  };

  template <typename T>
  T* deserialize(std::stringstream &) {
    throw Fertilized_Exception("To use the libraries serialization features, "
      "you must define the symbol SERIALIZATION_ENABLED with a preprocessor "
      "define (or use SCons with the flag --with-serialization). "
      "This adds a dependency to boost serialization.");
    return nullptr;
  };

  template <typename T>
  void deserialize(std::stringstream &, T*) {
    throw Fertilized_Exception("To use the libraries serialization features, "
      "you must define the symbol SERIALIZATION_ENABLED with a preprocessor "
      "define (or use SCons with the flag --with-serialization). "
      "This adds a dependency to boost serialization.");
  };

#endif  // SERIALIZATION_ENABLED
}  // namespace fertilized

#endif  // FERTILIZED_SERIALIZATION_SERIALIZATION_H_
