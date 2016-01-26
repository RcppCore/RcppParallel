//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_RANDO_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_RANDO_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_rando rando
 *
 * rando  random matrix with elements -1, 0 or 1. or random elements
 *    a = rando(n,m,k,as_<T>) is a random n-by-m matrix with
 *    elements from one of the following discrete distributions
 *    (default k = 1):
 *       k = 1:  a(i,j) =  0 or 1    with equal probability,
 *       k = 2:  a(i,j) = -1 or 1    with equal probability,
 *       k = 3:  a(i,j) = -1, 0 or 1 with equal probability.
 * one can also call rando<T>(n,m,k)
 * omitted T produces double elements
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rando.hpp>
 * \endcode
 *
 **/
//==============================================================================
// rando actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag rando_ of functor rando
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct rando_ : ext::unspecified_<rando_>
    {
      typedef ext::unspecified_<rando_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_rando_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
}
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::rando_, Site> dispatching_rando_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::rando_, Site>();
    }
    template<class... Args>
    struct impl_rando_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::rando_, rando, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::rando_, rando, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::rando_, rando, 2)

  template<class T>
  BOOST_FORCEINLINE typename meta::call<tag::rando_(size_t, size_t, size_t, meta::as_<T>)>::type
  rando(size_t n)
  {
    return nt2::rando(n, n, 1, meta::as_<T>());
  }
  template<class T>
  BOOST_FORCEINLINE typename meta::call<tag::rando_(size_t,size_t, meta::as_<T>)>::type
  rando(size_t n, size_t m)
  {
    return nt2::rando(n, m, 1, meta::as_<T>());
  }
  template<class T>
  BOOST_FORCEINLINE typename meta::call<tag::rando_(size_t,size_t, meta::as_<T>)>::type
  rando(size_t n, size_t m, size_t k)
  {
    return nt2::rando(n, m, k, meta::as_<T>());
  }
}


#endif

