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

#include "../global.h"
#include "./serialization.h"

#if defined SERIALIZATION_ENABLED
namespace fertilized {
template <typename T>
  DllExport std::string serialize(const T *obj, const bool &direct) {
    std::stringstream ss;
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
    boost::archive::text_iarchive ia(ser);
    register_fertilized_objects_(ia);
    T *obj;
    ia >> obj;
    return obj;
  };

  template <typename T>
  DllExport void deserialize(std::stringstream &ser, T* obj) {
    boost::archive::text_iarchive ia(ser);
    register_fertilized_objects_(ia);
    ia >> *obj;
  };
}
#endif  // SERIALIZATION_ENABLED
#endif  // FERTILIZED_SERIALIZATION__SERIALIZATION_DEFINITION_H_