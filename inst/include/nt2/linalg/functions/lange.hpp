//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LANGE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LANGE_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements lapack lange function that returns the value of
  the one norm, or the Frobenius norm, or the  infinity norm, or the  element
  of  largest absolute value of a real matrix A.
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines lange function tag
    struct lange_ : ext::abstract_<lange_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<lange_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_lange_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::lange_, Site> dispatching_lange_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::lange_, Site>();
    }
    template<class... Args>
    struct impl_lange_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION (tag::lange_, lange
                                  , 2
                                  );

  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::lange_, lange
                                  , (A0 const&)(A1 const&)(A2)
                                  , 3
                                  );


}

#endif
