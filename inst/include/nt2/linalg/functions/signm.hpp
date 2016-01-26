//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SIGNM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SIGNM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag signm_ of functor signm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct signm_ :   ext::tieable_<signm_>
    {
      typedef ext::tieable_<signm_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_signm_(
                                  ext::adl_helper(),
                                  static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::signm_, Site>
    dispatching_signm_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::signm_, Site>();
    }
    template<class... Args>
    struct impl_signm_;
  }
  /**
   * @brief signm(a0) computes the 'sign' of a square matricial expression
   *
   * signm(a) must not be confused with sign(a) that computes on an
   * elementwise basis the sign of the elements of matrix a.
   * s = signnm(a) is a matrix such that:
   *
   * (a) mtimes(s, s)= I (s is involutory);
   * (b) s is diagonalizable with eigenvalues +1 or -1;
   * (c) sa = as;
   * (d) if a is real then s is real;
   * (e) (I + s)/2 and (I − s)/2 are projectors onto the invariant subspaces associated
   *       with the eigenvalues in the right half-plane and left half-plane, respectively.
   *
   * a  can be a any square matricial expression whose
   * non real eigenvalues are not on the imaginary axis.
   *
   * @param  a0  Matrix expression or scalar
   *
   * @return a matrix containing signm(a1)
   *
   * signm is computed here from the schur decomposition.
   *
   * signm(a, epsi) allows to to be +/- tolerant about the fact
   * that the schur triangular matrix is in fact diagonal.
   * epsi default value is 10*Eps<type>() where type
   * is the input element type.

   **/


  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::signm_, signm, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::signm_, signm, 2)

}
namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::signm_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }
#endif

