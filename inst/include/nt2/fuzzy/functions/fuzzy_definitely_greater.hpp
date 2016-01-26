//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fuzzy_definitely_greater generic tag

     Represents the fuzzy_definitely_greater function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fuzzy_definitely_greater_ : ext::elementwise_<fuzzy_definitely_greater_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fuzzy_definitely_greater_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_fuzzy_definitely_greater_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::fuzzy_definitely_greater_, Site> dispatching_fuzzy_definitely_greater_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::fuzzy_definitely_greater_, Site>();
   }
   template<class... Args>
   struct impl_fuzzy_definitely_greater_;
  }
  /*!
    \f$a_0 >  a_1+a_2*\max(|a_0|,|a1|)\f$

    @par Semantic:

    For every parameters of floating type T0:

    @code
    logical<T0> r = fuzzy_definitely_greater(a0,a1,a2);
    @endcode

    is similar to:

    @code
    logical<T0> r = a0 > a1+a2*max(abs(a0), abs(a1));
    @endcode

    @param a0

    @param a1

    @param a2

    @return a logical value  of the type associated the first parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fuzzy_definitely_greater_, fuzzy_definitely_greater, 3)
}

#endif

