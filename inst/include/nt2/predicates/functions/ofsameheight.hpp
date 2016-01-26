//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_OFSAMEHEIGHT_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_OFSAMEHEIGHT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core_is_equal is_equal
 *
 * \par Description
 * Returns true or false according a0 and a1 have same height.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ofsameheight.hpp>
 * \endcode
 *
 * \par Alias
 * \arg eq
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     bool ofsameheight(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of ofsameheight
 *
 * \return a bool value
 *
**/

namespace nt2
{
  namespace tag
  {
    struct ofsameheight_ : ext::abstract_<ofsameheight_>
    {
      typedef ext::abstract_<ofsameheight_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ofsameheight_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::ofsameheight_, Site> dispatching_ofsameheight_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::ofsameheight_, Site>();
    }
    template<class... Args>
    struct impl_ofsameheight_;
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ofsameheight_, ofsameheight, 2)
}

#endif
