//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MPOWER_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MPOWER_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag mpower_ of functor mpower
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct mpower_ :  ext::unspecified_<mpower_>
    {
      typedef ext::unspecified_<mpower_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mpower_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::mpower_, Site> dispatching_mpower_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::mpower_, Site>();
    }
    template<class... Args>
    struct impl_mpower_;
  }
  /**
   * @brief compute matricial power a0^a1
   *
   * a0 or a1 can be a square matricial expression,  but one of the two must be scalar
   *
   * @param  a0  Matrix expression or scalar
   * @param  a1  Scalar or matrix expression
   *
   * @return a matrix containing a0^a1
   **/

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mpower_, mpower, 2)

}

#endif

