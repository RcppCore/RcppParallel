//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_COMPLEX_FUNCTIONS_C_REAL_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_C_REAL_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup nt2_complex
 * \defgroup nt2_complex_c_real c_real
 *
 * \par Description
 * return the c_real real part of a complex
 * but as a value of dry type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/c_real.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::c_real_(A0)>::type
 *     c_real(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of c_real
 *
 * \return a dry value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the input vectors' elements
 * \par
 *
**/

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag c_real_ of functor c_real
     *        in namespace nt2::tag for toolbox complex
    **/
    struct c_real_ : ext::elementwise_<c_real_> { typedef ext::elementwise_<c_real_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_c_real_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::c_real_, Site> dispatching_c_real_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::c_real_, Site>();
    }
    template<class... Args>
    struct impl_c_real_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::c_real_, c_real, 1)
}

#endif
