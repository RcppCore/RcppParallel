//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_MINIMUM_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief splatted_minimum generic tag

      Represents the splatted_minimum function in generic contexts.
    **/
    struct splatted_minimum_ : ext::unspecified_<splatted_minimum_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<splatted_minimum_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_splatted_minimum_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::splatted_minimum_, Site> dispatching_splatted_minimum_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::splatted_minimum_, Site>();
    }
    template<class... Args>
    struct impl_splatted_minimum_;
  }

  /*!
    @brief Splatted minimum

    Computes the splatted minimum of the element of its argument.

    @par Semantic

    @code
    Type r = splatted_minimum(v);
    @endcode

    @code
    for(int i=0;i<Type::static_size;++i)
      x[i] = minimum(v);
    @endcode

    @param a0

    @return  a value of the same type as the parameter
  */
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::splatted_minimum_, splatted_minimum, 1)
} }

#endif
