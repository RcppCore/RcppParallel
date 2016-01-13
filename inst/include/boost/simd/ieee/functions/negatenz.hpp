//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_NEGATENZ_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_NEGATENZ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief negatenz generic tag

     Represents the negatenz function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct negatenz_ : ext::elementwise_<negatenz_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<negatenz_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_negatenz_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::negatenz_, Site> dispatching_negatenz_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::negatenz_, Site>();
   }
   template<class... Args>
   struct impl_negatenz_;
  }
  /*!
    Returns a0 multiplied by the signnz of a1
    The result is unspecified if a1 is NaN

    @par Semantic:

    @code
    T r = negatenz(a0,a1);
    @endcode

    is similar to:

    @code
    T r = a0*signnz(a1)
    @endcode

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negatenz_, negatenz, 2)
} }

#endif
