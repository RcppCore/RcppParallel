//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_COMBINE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_COMBINE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief combine generic tag

      Represents the combine function in generic contexts.
    **/
    struct combine_ : ext::unspecified_<combine_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<combine_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_combine_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::combine_, Site> dispatching_combine_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::combine_, Site>();
    }
    template<class... Args>
    struct impl_combine_;
  }

  /*!
    @brief Combining vector

    Join two SIMD register into a register of greater cardinal.

    @par Semantic



    @param  a0 First part of the combination
    @param  a1 Second part of the combination

    @return The combined vector
  */

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::combine_, combine, 2)

} }

#endif
