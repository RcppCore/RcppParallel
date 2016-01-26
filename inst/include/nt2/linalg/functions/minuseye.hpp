//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MINUSEYE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MINUSEYE_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
      struct minuseye_ :  ext::abstract_<minuseye_>
      {
        typedef ext::abstract_<minuseye_> parent;
        template<class... Args>
        static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
        BOOST_AUTO_DECLTYPE_BODY( dispatching_minuseye_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
      };
  }
  namespace ext
  {
      template<class Site, class... Ts>
      BOOST_FORCEINLINE generic_dispatcher<tag::minuseye_, Site> dispatching_minuseye_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
      {
        return generic_dispatcher<tag::minuseye_, Site>();
      }
      template<class... Args>
      struct impl_minuseye_;
  }

  /**
   * @brief Perform minuseye(a, l)computation
   *
   * For any given matrix expression computes a - l*eye(right_size,  right_type).
   * l defaults to 1.
   *
   * @param    a Matrix expression
   * @param    l scalar factor to apply to a
   *
   * @return an expression for the result
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::minuseye_, minuseye, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::minuseye_, minuseye, 2)

}

#endif
