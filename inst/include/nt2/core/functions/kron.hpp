//==============================================================================
//         Copyright 2015  J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_KRON_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_KRON_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief kron generic tag

     Represents the kron function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct  kron_ : ext::abstract_<kron_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<kron_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_kron_( ext::adl_helper()
                                                 , static_cast<Args&&>(args)... ) )
    };
  }

  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::kron_, Site>
   dispatching_kron_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::kron_, Site>();
   }
   template<class... Args>
   struct impl_kron_;
  }
  /*!
    krnecker tensor product

    @par Semantic:


    @code
    auto r = kron(a0,a1);
    @endcode

    The result is a large matrix formed by taking all possible
    products between the elements of a0 and those of a1.


    @param a0 first matricial expression

    @param a1 second matricial expression

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::kron_, kron, 2)
}

#endif
