// Author: Christoph Lassner
#pragma once
#ifndef FERTILIZED_SERIALIZATION__SERIALIZATION_DEFINITION_H_
#define FERTILIZED_SERIALIZATION__SERIALIZATION_DEFINITION_H_
// Boost serialization libraries.
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/version.hpp>
// Register all used classes with boost::serialization.
#include <boost/serialization/map.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/vector.hpp>
// C++0x support.
#include "./serialization_extensions/shuffle_order_engine.h"
#include "./serialization_extensions/mersenne_twister_engine.h"
#include "./serialization_extensions/shared_ptr.h"
#include "./serialization_extensions/unique_ptr.h"
#include "./serialization_extensions/tuple.h"
#include "./serialization_extensions/unordered_map.hpp"
#include "./serialization_extensions/unordered_set.hpp"
#include "./serialization_extensions/eigen_serialization.h"

#include <vector>
#include <sstream>
#include <iostream>

#include "../global.h"
#include "./serialization.h"

#if defined SERIALIZATION_ENABLED
namespace fertilized {
template <typename T>
  DllExport std::string serialize(const T *obj, const bool &direct) {
    std::stringstream ss;
    // Add the library version information to the stream.
    ss << FERTILIZED_LIB_VERSION() << '\n';
    boost::archive::text_oarchive oa(ss);
    register_fertilized_objects_(oa);
    if (direct)
      oa << *obj;
    else
      oa << obj;
    return ss.str();
  };

  template <typename T>
  DllExport T * deserialize(std::stringstream &ser) {
    unsigned int serialized_lib_version;
    ser >> serialized_lib_version;
    if (serialized_lib_version > FERTILIZED_LIB_VERSION()) {
        std::cout << "Archive version is higher than the current library "
                     "version (defined as FERTILIZED_LIB_VERSION in global.h). "
                     "Most likely deserialization will fail! If it does, you "
                     "have a clue on what the cause might be." << std::endl <<
                     "Archive version: " << serialized_lib_version << "." << std::endl <<
                     "Library version: " << FERTILIZED_LIB_VERSION() << "." << std::endl;
    }
    boost::archive::text_iarchive ia(ser);
    register_fertilized_objects_(ia, false, serialized_lib_version);
    T *obj;
    ia >> obj;
    return obj;
  };

  template <typename T>
  DllExport void deserialize(std::stringstream &ser, T* obj) {
    unsigned int serialized_lib_version;
    ser >> serialized_lib_version;
    if (serialized_lib_version > FERTILIZED_LIB_VERSION()) {
        std::cout << "Archive version is higher than the current library "
                     "version (defined as FERTILIZED_LIB_VERSION in global.h). "
                     "Most likely deserialization will fail! If it does, you "
                     "have a clue on what the cause might be." << std::endl <<
                     "Archive version: " << serialized_lib_version << "." << std::endl <<
                     "Library version: " << FERTILIZED_LIB_VERSION() << "." << std::endl;
    }
    boost::archive::text_iarchive ia(ser);
    register_fertilized_objects_(ia, false, serialized_lib_version);
    ia >> *obj;
  };
}
#endif  // SERIALIZATION_ENABLED
#endif  // FERTILIZED_SERIALIZATION__SERIALIZATION_DEFINITION_H_
