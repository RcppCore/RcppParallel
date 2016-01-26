//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SX_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \par Description
 * sx sx<Tag>(a0, a1)      is equivalent to bsxfun(functor<Tag>(), a0, a1) if Tag is a binary functor
 *    sx<Tag>(a0, a1, a2)  is equivalent to tsxfun(functor<Tag>(), a0, a1, a2) if Tag is a ternary functor
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sx.hpp>
 * \endcode
 *
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sx_(A0)>::type
 *     sx(const A0 & a0);
 * }
 * \endcode
 *
**/

namespace nt2
{
  namespace tag
  {
     struct sx_ : ext::abstract_<sx_>
     {
       typedef ext::abstract_<sx_> parent;
       template<class... Args>
       static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
       BOOST_AUTO_DECLTYPE_BODY( dispatching_sx_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
     };
  }
  namespace ext
  {
     template<class Site, class... Ts>
     BOOST_FORCEINLINE generic_dispatcher<tag::sx_, Site> dispatching_sx_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
     {
       return generic_dispatcher<tag::sx_, Site>();
     }
     template<class... Args>
     struct impl_sx_;
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sx_       , sx, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sx_       , sx, 4)
}

#endif
