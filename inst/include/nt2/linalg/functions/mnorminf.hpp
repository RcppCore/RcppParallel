//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORMINF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORMINF_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mnorminf mnorminf
 *
 * \par Description
 * compute the infinity norm of a vector or a matrix
 *
 * that is :
 *  max(abs(a)) for a vector
 *  max(sum(abs(a), 2)) for a matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mnorminf.hpp>
 * \endcode
 *
 *
 * mnorminf can be used as
 * mnorminf(a)
 *
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag mnorminf_ of functor mnorminf
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct mnorminf_ :  ext::abstract_<mnorminf_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<mnorminf_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mnorminf_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::mnorminf_, Site> dispatching_mnorminf_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::mnorminf_, Site>();
    }
    template<class... Args>
    struct impl_mnorminf_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorminf_, mnorminf, 1)

}

#endif

