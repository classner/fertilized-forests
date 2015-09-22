#pragma once
#ifndef FERTILIZED_SERIALIZATION_EXTENSIONS_TUPLE_H_
#define FERTILIZED_SERIALIZATION_EXTENSIONS_TUPLE_H_

#include <boost/serialization/nvp.hpp>
#include <utility>


// This entire file has been altered to work for the std::tuple class from
// the C++ 11 STL. However, it is based on a file by Christian Henning, who
// wrote it for the boost::tuple. Even though it was modified, the copyright
// notice is reproduced.

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization/tuple.h: serialization for stl tuples
//
// This header was originally written by Christian Henning for the tr1 tuple
// and has been altered to work with C++ 11 version by Christoph Lassner.
//
// (C) Copyright 2006 - Christian Henning.
// (C) Copyright 2013 - Christoph Lassner.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

namespace boost { namespace serialization {

// double
template<class Archive, class FIRST, class SECOND>
inline void serialize( Archive & ar
                     , std::tuple< FIRST, SECOND >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , std::get<0>(t)  );
   ar & boost::serialization::make_nvp("second", std::get<1>(t)  );
}

// triple
template<class Archive, class FIRST, class SECOND, class THIRD>
inline void serialize( Archive & ar
                     , std::tuple<FIRST, SECOND, THIRD>& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , std::get<0>(t)  );
   ar & boost::serialization::make_nvp("second", std::get<1>(t)  );
   ar & boost::serialization::make_nvp("third" , std::get<2>(t)  );
}


// quadruple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH >
inline void serialize( Archive & ar
                     , std::tuple< FIRST, SECOND, THIRD, FOURTH 
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , std::get<0>(t)  );
   ar & boost::serialization::make_nvp("second", std::get<1>(t)  );
   ar & boost::serialization::make_nvp("third" , std::get<2>(t)  );
   ar & boost::serialization::make_nvp("fourth", std::get<3>(t)  );
}

//quintuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH >
inline void serialize( Archive & ar
                     , std::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , std::get<0>(t)  );
   ar & boost::serialization::make_nvp("second"  , std::get<1>(t)  );
   ar & boost::serialization::make_nvp("third"   , std::get<2>(t)  );
   ar & boost::serialization::make_nvp("fourth"  , std::get<3>(t)  );
   ar & boost::serialization::make_nvp("fifth"   , std::get<4>(t)  );
}

// sextuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH
        >
inline void serialize( Archive & ar
                     , std::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , std::get<0>(t)  );
   ar & boost::serialization::make_nvp("second"  , std::get<1>(t)  );
   ar & boost::serialization::make_nvp("third"   , std::get<2>(t)  );
   ar & boost::serialization::make_nvp("fourth"  , std::get<3>(t)  );
   ar & boost::serialization::make_nvp("fifth"   , std::get<4>(t)  );
   ar & boost::serialization::make_nvp("sixth"   , std::get<5>(t)  );
}

// septuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH
        >
inline void serialize( Archive & ar
                     , std::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , std::get<0>(t)  );
   ar & boost::serialization::make_nvp("second"  , std::get<1>(t)  );
   ar & boost::serialization::make_nvp("third"   , std::get<2>(t)  );
   ar & boost::serialization::make_nvp("fourth"  , std::get<3>(t)  );
   ar & boost::serialization::make_nvp("fifth"   , std::get<4>(t)  );
   ar & boost::serialization::make_nvp("sixth"   , std::get<5>(t)  );
   ar & boost::serialization::make_nvp("seventh" , std::get<6>(t)  );
}

// octet
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT
        >
inline void serialize( Archive & ar
                     , std::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH, EIGHT 
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , std::get<0>(t)  );
   ar & boost::serialization::make_nvp("second"  , std::get<1>(t)  );
   ar & boost::serialization::make_nvp("third"   , std::get<2>(t)  );
   ar & boost::serialization::make_nvp("fourth"  , std::get<3>(t)  );
   ar & boost::serialization::make_nvp("fifth"   , std::get<4>(t)  );
   ar & boost::serialization::make_nvp("sixth"   , std::get<5>(t)  );
   ar & boost::serialization::make_nvp("seventh" , std::get<6>(t)  );
   ar & boost::serialization::make_nvp("eighth"  , std::get<7>(t)  );
}

// This implementation originates from the boost tuple, which was defined
// for up to ten elements.
//// 9-tuple
//template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
//        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT, class NINE
//        >
//inline void serialize( Archive & ar
//                     , std::tuple< FIRST, SECOND, THIRD, FOURTH
//                                   , FIFTH, SIXTH, SEVENTH, EIGHT, NINE 
//                                   >& t
//                     , const unsigned int /* file_version */
//)
//{
//   ar & boost::serialization::make_nvp("first"   , std::get<0>(t)  );
//   ar & boost::serialization::make_nvp("second"  , std::get<1>(t)  );
//   ar & boost::serialization::make_nvp("third"   , std::get<2>(t)  );
//   ar & boost::serialization::make_nvp("fourth"  , std::get<3>(t)  );
//   ar & boost::serialization::make_nvp("fifth"   , std::get<4>(t)  );
//   ar & boost::serialization::make_nvp("sixth"   , std::get<5>(t)  );
//   ar & boost::serialization::make_nvp("seventh" , std::get<6>(t)  );
//   ar & boost::serialization::make_nvp("eighth"  , std::get<7>(t)  );
//   ar & boost::serialization::make_nvp("ninth"   , std::get<8>(t)  );
//}
//
//// 10-tuple
//template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
//        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT, class NINE, class TEN
//        >
//inline void serialize( Archive & ar
//                     , std::tuple< FIRST, SECOND, THIRD, FOURTH
//                                   , FIFTH, SIXTH, SEVENTH, EIGHT
//                                   , NINE, TEN
//                                   >& t
//                     , const unsigned int /* file_version */
//)
//{
//   ar & boost::serialization::make_nvp("first"   , std::get<0>(t)  );
//   ar & boost::serialization::make_nvp("second"  , std::get<1>(t)  );
//   ar & boost::serialization::make_nvp("third"   , std::get<2>(t)  );
//   ar & boost::serialization::make_nvp("fourth"  , std::get<3>(t)  );
//   ar & boost::serialization::make_nvp("fifth"   , std::get<4>(t)  );
//   ar & boost::serialization::make_nvp("sixth"   , std::get<5>(t)  );
//   ar & boost::serialization::make_nvp("seventh" , std::get<6>(t)  );
//   ar & boost::serialization::make_nvp("eighth"  , std::get<7>(t)  );
//   ar & boost::serialization::make_nvp("ninth"   , std::get<8>(t)  );
//   ar & boost::serialization::make_nvp("tenth"   , std::get<9>(t)  );
//}

}} // serialization boost

#endif  // FERTILIZED_BASE_SERIALIZATION_EXTENSIONS_TUPLE_H_
