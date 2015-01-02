#pragma once
#ifndef FERTILIZED_SERIALIZATION_EXTENSIONS_UNIQUE_PTR_H_
#define FERTILIZED_SERIALIZATION_EXTENSIONS_UNIQUE_PTR_H_

#include <boost/serialization/serialization.hpp>
#include <memory>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// unique_ptr.h: serialization for stl unique_ptr
//
// This header implements serialization for the stl unique_ptr. It is based
// on a suggestion on stackoverflow:
// http://stackoverflow.com/questions/12915267/boost-serialization-stdunique-ptr-support
//
// (C) Copyright 2013 Christoph Lassner.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8

namespace boost { namespace serialization {

template<class Archive, class T>
inline void save(Archive & ar, const std::unique_ptr< T > &t,
                 const unsigned int &file_version) {
  // only the raw pointer has to be saved
  const T * const tx = t.get();
  ar << tx;
};

template<class Archive, class T>
inline void load(Archive & ar, std::unique_ptr< T > &t,
                 const unsigned int &file_version) {
  T *pTarget;
  ar >> pTarget;

  #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
      t.release();
      t = std::unique_ptr< T >(pTarget);
  #else
      t.reset(pTarget);
  #endif
};

template<class Archive, class T>
inline void serialize(Archive & ar, std::unique_ptr< T > &t,
                      const unsigned int &file_version) {
  boost::serialization::split_free(ar, t, file_version);
}

}}  // namespace serialization namespace boost

#endif  // FERTILIZED_BASE_SERIALIZATION_EXTENSIONS_UNIQUE_PTR_H_
