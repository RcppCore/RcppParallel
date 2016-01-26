//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_DEFINITELY_LESS_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_DEFINITELY_LESS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief definitely_less generic tag

     Represents the definitely_less function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct definitely_less_ : ext::elementwise_<definitely_less_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<definitely_less_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_definitely_less_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::definitely_less_, Site> dispatching_definitely_less_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::definitely_less_, Site>();
   }
   template<class... Args>
   struct impl_definitely_less_;
  }
  /*!
    \f$a_0 <  \mathop{\mbox{predecessor}}(a_1,|a_2|)\f$

    @par Semantic:

    For every parameters of floating types respectively T0, T1, T2:

    @code
    T0 r = definitely_less(a0,a1,a2);
    @endcode

    is similar to:

    @code
    T0 r = ;
    @endcode

    @param a0

    @param a1

    @param a2

    @return a logical value  of the type associated the first parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::definitely_less_, definitely_less, 3)
}

#endif

