//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_EXPM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_EXPM_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag expm_ of functor expm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct expm_ :   ext::unspecified_<expm_>
    {
      typedef ext::unspecified_<expm_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_expm_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::expm_, Site> dispatching_expm_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::expm_, Site>();
    }
    template<class... Args>
    struct impl_expm_;
  }
  /**
   * @brief compute exponential of a matricial expression
   *
   * expm(a0) must not be confused with exp(a0) that computes on an
   * elementwise basis the powers of the elements of matrix a0.
   *
   * a0  can be a any square matricial expression
   *
   * @param  a0  Matrix expression or scalar
   *
   * @return a matrix containing e^a1
   **/


  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::expm_, expm, 1)

}

#endif

