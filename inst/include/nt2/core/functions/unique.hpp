//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_UNIQUE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_UNIQUE_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief unique generic tag

      Represents the unique function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct unique_ : ext::unspecified_<unique_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<unique_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_unique_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::unique_, Site> dispatching_unique_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::unique_, Site>();
    }
    template<class... Args>
    struct impl_unique_;
  }

  /*!
    sort and suppress duplicates elements.

    @par Semantic:

    For every matrix expression

    @code
    auto r = unique(a0);
    @endcode

    returns the same data as in a0, but with no repetitions as a sorted column vector.

    @param a0

    @return a column vector of size less or equal to numel(a)
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unique_       , unique, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::unique_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::unique_,Domain,N,Expr>
    : meta::size_as<Expr,0>
  {};

} }

#endif
