//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_RSF2CSF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_RSF2CSF_HPP_INCLUDED

#include <nt2/linalg/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2
{
  namespace tag
  {
    struct rsf2csf_ :  ext::tieable_<rsf2csf_>
    {
      typedef ext::tieable_<rsf2csf_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_rsf2csf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::rsf2csf_, Site>
    dispatching_rsf2csf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::rsf2csf_, Site>();
    }
    template<class... Args>
    struct impl_rsf2csf_;
  }

  /**
   * @brief real schur form to complex schur form.
   *
   *   transforms the outputs of schur(x) (where x is
   *   real) from hessenberg form to triangular but complex form.
   *
   *
   * if  tie(u, t) = schur(x) were x is a real matrix,  we have   u*t*trans(u) == x
   with u orthogonal and t upper hessenberg
   *
   *  after    tie(cu, ct) = rsf2csf(u, t)
   *
   *   we still have   cu*ct*ctrans(cu),  cu is unitary and ct is upper triangular
   *
   * If u and t do not came from a real schur decompoition the routine is meaningless.
   *
   * @param u orthogonal matrix from real schur decomposition
   * @param t hessenbeg matrix from real schur decomposition
   * @return a fusion sequence of two complex matrices
   *
   * @see @funcref{schur},  @funcref{cplxpair}
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::rsf2csf_, rsf2csf, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::rsf2csf_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
