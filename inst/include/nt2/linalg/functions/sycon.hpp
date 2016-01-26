//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SYCON_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SYCON_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements lapack sycon function that estimates the
  reciprocal of the condition number of a matrix A in the 1-norm or infinity norm
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines gecon function tag
    struct sycon_ : ext::abstract_<sycon_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<sycon_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_sycon_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::sycon_, Site> dispatching_sycon_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::sycon_, Site>();
    }
    template<class... Args>
    struct impl_sycon_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/

  NT2_FUNCTION_IMPLEMENTATION (tag::sycon_, sycon
                                  , 3
                                  );

}

#endif
