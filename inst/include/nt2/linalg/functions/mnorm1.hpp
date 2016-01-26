//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORM1_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORM1_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mnorm1 mnorm1
 *
 * \par Description
 * compute the 1-norm of a vector or a matrix
 *
 * that is :
 *  sum(abs(a)) for a vector
 *  max(sum(abs(a), 1)) for a matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mnorm1.hpp>
 * \endcode
 *
 * mnorm1 can be used as
 * mnorm1(a)
 *
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag mnorm1_ of functor mnorm1
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct mnorm1_ :  ext::abstract_<mnorm1_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<mnorm1_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mnorm1_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::mnorm1_, Site> dispatching_mnorm1_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::mnorm1_, Site>();
    }
    template<class... Args>
    struct impl_mnorm1_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm1_, mnorm1, 1)

}

#endif

