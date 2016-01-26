//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TRACE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TRACE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_trace trace
 *
 * \par Description
 * Elementary Least square
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/trace.hpp>
 * \endcode
 *
 *
 * \param a the matrix a on entry, destroyed on exit
 *
 * \param b the second member(s) b on entry, solution on exit
 *
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *
**/
//==============================================================================
// trace actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag trace_ of functor trace
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct trace_ : ext::unspecified_<trace_> { typedef ext::unspecified_<trace_> parent;   template<class... Args>   static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)   BOOST_AUTO_DECLTYPE_BODY( dispatching_trace_( ext::adl_helper(), static_cast<Args&&>(args)... ) ) };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::trace_, Site> dispatching_trace_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::trace_, Site>();
    }
    template<class... Args>
    struct impl_trace_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::trace_, trace, 1)
}

#endif
