//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LOGM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LOGM_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag logm_ of functor logm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct logm_ :   ext::unspecified_<logm_>
    {
      typedef ext::unspecified_<logm_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_logm_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::logm_, Site> dispatching_logm_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::logm_, Site>();
    }
    template<class... Args>
    struct impl_logm_;
  }
  /**
   * @brief compute natural principal logarithm of a matricial expression
   *
   * logm(a0) must not be confused with log(a0) that computes on an
   * elementwise basis the logarithms of the elements of matrix a0.
   *
   * a0  can be a any square matricial expression whose
   * real eigenvalues are strictly positive
   *
   * @param  a0  Matrix expression or scalar
   *
   * @return a matrix containing logm(a1)
   **/


  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logm_, logm, 1)

}

#endif

