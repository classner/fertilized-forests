#pragma once
#ifndef FERTILIZED_EIGEN_SERIALIZATION_H_
#define FERTILIZED_EIGEN_SERIALIZATION_H_



#include <Eigen/Core>
#include <Eigen/Dense>


/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// eigen_serialization.h: serialization for Eigen Matrices
//
// This header implements serialization for Eigen Matrices. It is based
// on the following Discussion:
// http://stackoverflow.com/questions/18382457/eigen-and-boostserialize/23407209#23407209
//
// (C) Copyright 2013 Christoph Lassner.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8

namespace boost {
  namespace serialization{

    template<class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
    inline void save(Archive &ar,
                     const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> &mat, 
                     const unsigned int &/*version*/) {
      int rows = static_cast<int>(mat.rows());
      int cols = static_cast<int>(mat.cols());
      ar << rows;
      ar << cols;
      ar << boost::serialization::make_array(mat.data(), rows * cols);
    }


    template<class Archive, typename _Scalar, int _Rows, 
             int _Cols, int _Options, int _MaxRows, int _MaxCols>
    inline void load(Archive &ar,
                     Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> &mat, 
                     const unsigned int &/*version*/) {
      int rows;
      int cols;
      ar >> rows;
      ar >> cols;
      mat.resize(rows,cols);
      ar >> boost::serialization::make_array(mat.data(), rows * cols);
    }


    template<class Archive, typename _Scalar, int _Rows, 
             int _Cols, int _Options, int _MaxRows, int _MaxCols>
    inline void serialize(Archive &ar,
                          Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> &mat, 
                          const unsigned int &version) {
      split_free(ar,mat,version);
    }

  } // namespace serialization
} // namespace boost



#endif // FERTILIZED_EIGEN_SERIALIZATION_H_