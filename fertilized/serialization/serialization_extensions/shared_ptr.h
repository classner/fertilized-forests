#pragma once
#ifndef FERTILIZED_SERIALIZATION_EXTENSIONS_SHARED_PTR_H_
#define FERTILIZED_SERIALIZATION_EXTENSIONS_SHARED_PTR_H_

#include <memory>
#include <unordered_map>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// shared_ptr.h: serialization for stl shared_ptr
//
// This header implements serialization for the stl shared_ptr. It is based
// on a suggestion on stackoverflow:
// http://stackoverflow.com/questions/8115220/how-can-boostserialization-be-used-with-stdshared-ptr-from-c11
//
// (C) Copyright 2013 Christoph Lassner.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8


namespace boost { namespace serialization {

template<class Archive, class Type>
void save(Archive & archive, const std::shared_ptr<Type> & value,
          const unsigned int &/*version*/) {
  Type *data = value.get();
  archive << data;
};

template<class Archive, class Type>
void load(Archive & archive, std::shared_ptr<Type> & value,
          const unsigned int &/*version*/) {
  Type *data;
  archive >> data;

  typedef std::weak_ptr<Type> WeakPtr;
  static std::unordered_map<void*, WeakPtr> hash;

  if (hash[data].expired())
  {
    value = std::shared_ptr<Type>(data);
    hash[data] = value;
  }
  else value = hash[data].lock();
};

template<class Archive, class Type>
inline void serialize(Archive & archive, std::shared_ptr<Type> & value,
                      const unsigned int &version)
{
    split_free(archive, value, version);
};

}}  // namespace serialization namespace boost

#endif
