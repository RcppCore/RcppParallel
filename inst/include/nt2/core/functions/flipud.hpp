//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//=============================================================================
#ifndef NT2_CORE_FUNCTIONS_FLIPUD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FLIPUD_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief flipud generic tag

     Represents the flipud function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct flipud_ : ext::elementwise_<flipud_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<flipud_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_flipud_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::flipud_, Site> dispatching_flipud_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::flipud_, Site>();
   }
   template<class... Args>
   struct impl_flipud_;
  }
  /*!
    Flips an expression around the horizontal axis

    @par Semantic:

    For every table expression

    @code
    auto r = flipud(a0);
    @endcode

    is similar to:

    @code
    auto r = a0(_, _(width(a0), -1, 1), ..., _);
    @endcode

    @see @funcref{width}, @funcref{colon}
    @param a0

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::flipud_       , flipud, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::flipud_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
