//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GEQP3_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GEQP3_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements qp3 function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines qp3 function tag
    struct geqp3_ : ext::abstract_<geqp3_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<geqp3_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_geqp3_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::geqp3_, Site> dispatching_geqp3_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::geqp3_, Site>();
    }
    template<class... Args>
    struct impl_geqp3_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::geqp3_, geqp3
                                  , (A0&)(A1&)(A2&)
                                  , 3
                                  );

  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::geqp3_, geqp3
                                  , (A0&)(A1&)(A2&)(A3&)
                                  , 4
                                  );
}

#endif
