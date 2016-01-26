//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_POW_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief pow generic tag

     Represents the pow function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct pow_ : ext::elementwise_<pow_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<pow_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_pow_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::pow_, Site> dispatching_pow_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::pow_, Site>();
   }
   template<class... Args>
   struct impl_pow_;
  }
  /*!
    Computes a0 to a1

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = pow(x,y);
    @endcode

    is similar to:

    @code
    T0 r = exp(y*log(x));
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::pow_, pow, 2)

  template<long long Exp, class A0>
  BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE pow(A0 const& a0)
  BOOST_AUTO_DECLTYPE_BODY(
    dispatching_pow_( ext::adl_helper(), boost::dispatch::default_site_t<A0>()
                    , boost::dispatch::meta::hierarchy_of_t<A0 const&>()
                    , boost::dispatch::meta::hierarchy_of_t< boost::mpl::integral_c<long long, Exp> >()
                    )
    (a0, boost::mpl::integral_c<long long, Exp>())
  )
}

#endif

