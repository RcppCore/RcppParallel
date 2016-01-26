//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_FASTNORMCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_FASTNORMCDF_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief fastnormcdf generic tag

     Represents the fastnormcdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fastnormcdf_ : ext::elementwise_<fastnormcdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fastnormcdf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_fastnormcdf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::fastnormcdf_, Site> dispatching_fastnormcdf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::fastnormcdf_, Site>();
   }
   template<class... Args>
   struct impl_fastnormcdf_;
  }
  /*!
    fast normal cumulative distribution

    @par Semantic:

    @code
    r = normcdf(a0);
    @endcode

    is similar to:

    @code
    r = erfc(Sqrt_2o_2*-a0)/2;
    @endcode

    @see @funcref{erfc}, @funcref{Sqrt_2o_2},
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fastnormcdf_, fastnormcdf, 1)
}

#endif
