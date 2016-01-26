//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ISMEMBER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ISMEMBER_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief ismember generic tag

      Represents the ismember function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct ismember_ : ext::unspecified_<ismember_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<ismember_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ismember_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::ismember_, Site> dispatching_ismember_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::ismember_, Site>();
    }
    template<class... Args>
    struct impl_ismember_;
  }

  /*!
    Computes elements from a table that belongs to another
    @par Semantic:

    For every tables expression

    @code
    auto r = ismember(a, b);
    @endcode

    returns an array of logical of the size of a containing true/false
    iff the corresponding element of a is among the elements of b

    @param a
    @param b

    @return an array logical of the size of a
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ismember_       , ismember, 2)
  /*!
    Computes elements from  table a that approximately belong to table b,
    with no repetitions as a column vector

    @par Semantic:

    For every tables expression

    @code
    auto r = ismember(a, b, tol);
    @endcode

    returns an array of logical of the size of a containing true/false iff the corresponding
    element of a is approximately among the elements of b. approximately belongs means that
    there exist a indexes i and  j such that abs(a(i)-b(j)) < tol*max(abs(a))

    @alias ismembertol

    @param a
    @param b
    @param tol

    @return an array logical of the size of a
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ismember_       , ismember, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ismember_       , ismembertol, 3)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::ismember_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename meta::strip<c0_t>::type                             t_type;
    typedef typename t_type::value_type                                  v_type;
    typedef typename meta::as_logical<v_type>::type                        type;
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::ismember_,Domain,N,Expr>
    : meta::size_as<Expr,0>
  {};

} }

#endif
