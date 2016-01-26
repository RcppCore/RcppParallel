//==============================================================================
//         Copyright 2015   J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_135_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_135_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief _135 generic tag

     Represents the _135 constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( _135, double
                                , 135, 0x43070000
                                , 0x4060e00000000000ll
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::_135, Site> dispatching__135(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::_135, Site>();
   }
   template<class... Args>
   struct impl__135;
  }
  /*!
    Constant 135.

    @par Semantic:

    For type T0:

    @code
    T0 r = _135<T0>();
    @endcode

    is similar to:

    @code
    T0 r = 135;
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_135, _135);
}

#endif

