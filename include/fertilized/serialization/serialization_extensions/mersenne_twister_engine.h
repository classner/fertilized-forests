#pragma once
#ifndef FERTILIZED_SERIALIZATION_EXTENSIONS_MERSENNE_TWISTER_ENGINE_H_
#define FERTILIZED_SERIALIZATION_EXTENSIONS_MERSENNE_TWISTER_ENGINE_H_

#include <random>
#include <sstream>
#include <boost/serialization/nvp.hpp>


/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// mersenne_twister_engine.h: serialization for stl mersenne_twister_engine
//
// This header implements serialization for the stl mersenne_twister_engine.
// Since it supports writing its state to a stream, this is fairly simple
// to achieve.
//
// (C) Author: Christoph Lassner.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8

//---/ Wrapper for std::mersenne_twister_engine<> /----------------------------

namespace boost { namespace serialization {

template<class Archive,
          class _Ty,
          size_t _Wx,
          size_t _Nx,
          size_t _Mx,
          size_t _Rx,
          _Ty _Px,
          size_t _Ux,
          _Ty _Dx,	// added
          size_t _Sx,
          _Ty _Bx,
          size_t _Tx,
          _Ty _Cx,
          size_t _Lx,
          _Ty _Fx>
void save(Archive & archive,
          const std::mersenne_twister_engine<_Ty, _Wx, _Nx, _Mx, _Rx,
            _Px, _Ux, _Dx, _Sx, _Bx, _Tx, _Cx, _Lx, _Fx> &value,
          const unsigned int &/*version*/) {
  // Serialize via a string.
  std::stringstream ss;
  ss << value;
  std::string state = ss.str();
  archive << state;
};

template<class Archive,
          class _Ty,
          size_t _Wx,
          size_t _Nx,
          size_t _Mx,
          size_t _Rx,
          _Ty _Px,
          size_t _Ux,
          _Ty _Dx,	// added
          size_t _Sx,
          _Ty _Bx,
          size_t _Tx,
          _Ty _Cx,
          size_t _Lx,
          _Ty _Fx>
void load(Archive & archive,
          std::mersenne_twister_engine<_Ty, _Wx, _Nx, _Mx, _Rx,
    _Px, _Ux, _Dx, _Sx, _Bx, _Tx, _Cx, _Lx, _Fx> &value,
          const unsigned int &/*version*/) {
  std::string tmp;
  archive >> tmp;
  std::stringstream ss(tmp);
  ss >> value;
};

template<class Archive,
          class _Ty,
          size_t _Wx,
          size_t _Nx,
          size_t _Mx,
          size_t _Rx,
          _Ty _Px,
          size_t _Ux,
          _Ty _Dx,	// added
          size_t _Sx,
          _Ty _Bx,
          size_t _Tx,
          _Ty _Cx,
          size_t _Lx,
          _Ty _Fx>
inline void serialize(Archive & archive,
                      std::mersenne_twister_engine<_Ty, _Wx, _Nx, _Mx, _Rx,
                        _Px, _Ux, _Dx, _Sx, _Bx, _Tx, _Cx, _Lx, _Fx> &value,
                      const unsigned int &version) {
  split_free(archive, value, version);
};

}}  // namespace serialization namespace boost

#endif
