//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXPIPI_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXPIPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup exponential
 * \defgroup exponential_expipi expipi
 *
 * \par Description
 * expipionential function: \f$e^{\pi i a_0}\f$ where  \f$i^{2} = -1\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/expipi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expipi_(A0)>::type
 *     expipi(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of expipi
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag expipi_ of functor expipi
     *        in namespace nt2::tag for toolbox expipionential
    **/
    struct expipi_ : ext::elementwise_<expipi_> { typedef ext::elementwise_<expipi_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_expipi_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::expipi_, Site> dispatching_expipi_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::expipi_, Site>();
    }
    template<class... Args>
    struct impl_expipi_;
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expipi_, expipi, 1)
}

#endif
