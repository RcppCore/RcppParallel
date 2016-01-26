//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CDF2RDF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CDF2RDF_HPP_INCLUDED

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
    struct cdf2rdf_ :  ext::tieable_<cdf2rdf_>
    {
      typedef ext::tieable_<cdf2rdf_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_cdf2rdf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::cdf2rdf_, Site>
    dispatching_cdf2rdf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::cdf2rdf_, Site>();
    }
    template<class... Args>
    struct impl_cdf2rdf_;
  }

  /**
   * @brief complex diagonal form to real block diagonal form.
   *
   *   transforms the outputs of nseig(x) (where x is
   *   real) from complex diagonal form to a real block diagonal form.  In
   *   complex diagonal form, d has complex eigenvalues down the
   *   diagonal.  in real diagonal form, the complex eigenvalues are in
   *   2-by-2 blocks on the diagonal.  complex conjugate eigenvalue pairs
   *   are assumed to be next to one another.
   *
   *
   * if  tie(cv, cw) = nseig(x) we have  x*cv =  cw*x
   *
   *     tie(v, w) = cdf2rdf(cv, cw)
   *
   *   we still have  x*v =  w*x,  but v and w are real matrices and w is block
   *   diagonal
   *
   * @param cv eigenvectors complex eigenvectors from nseig
   * @param ct eigenvalues  complex eigenvalues from nseig
   * @return a fusion sequence of two real matrices
   *
   * @see @funcref{cplxpair}
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::cdf2rdf_, cdf2rdf, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::cdf2rdf_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
