#pragma once
#ifndef FERTILIZED_SERIALIZATION_EXTENSIONS_SHUFFLE_ORDER_ENGINE_H_
#define FERTILIZED_SERIALIZATION_EXTENSIONS_SHUFFLE_ORDER_ENGINE_H_

#include <random>
#include <sstream>
#include <boost/serialization/nvp.hpp>


/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// shuffle_order_engine.h: serialization for stl shuffle_order_engine
//
// This header implements serialization for the stl shuffle_order_engine.
// Since it supports writing its state to a stream, this is fairly simple
// to achieve.
//
// (C) Copyright 2013 Christoph Lassner.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


//---/ Wrapper for std::shuffle_order_engine<> /-------------------------------

namespace boost { namespace serialization {

template<class Archive, class E, size_t K>
void save(Archive & archive, const std::shuffle_order_engine<E, K> &value,
          const unsigned int &/*version*/) {
  // Serialize via a string.
  std::stringstream ss;
  ss << value;
  std::string state = ss.str();
  archive << state;
};

template<class Archive, class E, size_t K>
void load(Archive & archive, std::shuffle_order_engine<E, K> &value,
          const unsigned int &/*version*/) {
  std::string tmp;
  archive >> tmp;
  std::stringstream ss(tmp);
  ss >> value;
};

template<class Archive, class E, size_t K>
inline void serialize(Archive & archive, std::shuffle_order_engine<E, K> &value,
                      const unsigned int &version) {
  split_free(archive, value, version);
};

}}  // namespace serialization namespace boost

#endif
