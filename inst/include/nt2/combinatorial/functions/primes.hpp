//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_PRIMES_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_PRIMES_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief primes generic tag

     Represents the primes function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct primes_ : ext::elementwise_<primes_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<primes_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_primes_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::primes_, Site> dispatching_primes_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::primes_, Site>();
   }
   template<class... Args>
   struct impl_primes_;
  }
  /*!
    returns the table of prime numbers less or equal to the input

    @par Semantic:

    For every table expression

    @code
    auto r = primes(a0);
    @endcode

    @see @funcref{is_prime}, @funcref{factor}
    @param a0

    @return a table containing the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::primes_,primes, 1)
}

#endif

