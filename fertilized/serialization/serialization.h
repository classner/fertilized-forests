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
  void register_fertilized_objects_(Archive &ar);

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
  DllExport std::string serialize(T *);

  template <typename T>
  DllExport T* deserialize(std::stringstream &);

  template <typename T>
  DllExport void deserialize(std::stringstream &, T*);

  DllExport void offload_after_serialization_to(const std::vector<int> &devices);

  DllExport extern std::vector<int> __SERIALIZATION_OFFLOAD_DEVICES;

#endif  // SERIALIZATION_ENABLED
}  // namespace fertilized

#endif  // FERTILIZED_SERIALIZATION_SERIALIZATION_H_
