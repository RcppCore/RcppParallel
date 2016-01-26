//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_LCM_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_LCM_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief lcm generic tag

     Represents the lcm function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct lcm_ : ext::elementwise_<lcm_>
    {
       /// @brief Parent hierarchy
     typedef ext::elementwise_<lcm_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lcm_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::lcm_, Site> dispatching_lcm_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::lcm_, Site>();
   }
   template<class... Args>
   struct impl_lcm_;
  }
  /*!
    Computes the least common multiple

    If parameters are floating point and not flint,
    nan is returned.

    @par Semantic:

    For every table expressions

    @code
    auto r = lcm(a0,a1);
    @endcode

      - If any input is zero 0 is returned
      - If parameters are floating point and not flint,
      nan is returned.

    @see @funcref{gcd}, @funcref{is_flint}
    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::lcm_, lcm, 2)
}

#endif

