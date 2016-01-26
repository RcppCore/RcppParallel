//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORMFRO_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORMFRO_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mnormfro mnormfro
 *
 * \par Description
 * compute the froboenius norm of a vector or a matrix
 *
 * that is :
 *  sqrt(asum2((_))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mnormfro.hpp>
 * \endcode
 *
 * mnormfro can be used as
 * mnormfro(a)
 *
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag mnormfro_ of functor mnormfro
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct mnormfro_ :  ext::abstract_<mnormfro_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<mnormfro_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_mnormfro_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::mnormfro_, Site> dispatching_mnormfro_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::mnormfro_, Site>();
    }
    template<class... Args>
    struct impl_mnormfro_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnormfro_, mnormfro, 1)

}

#endif

