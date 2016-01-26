//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LYAPUNOV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LYAPUNOV_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag lyapunov_ of functor lyapunov
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct lyapunov_ :   ext::unspecified_<lyapunov_>
    {
      typedef ext::unspecified_<lyapunov_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_lyapunov_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::lyapunov_, Site>
    dispatching_lyapunov_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::lyapunov_, Site>();
    }
    template<class... Args>
    struct impl_lyapunov_;
  }
  /**
   * @brief solve the lyapunov equation ctrans(a)*x+x*a = c
   *
   *
   * @param  a  Matrix expression
   * @param  c  Matrix expression
   *
   * @return a matrix containing the solution
   **/


  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lyapunov_, lyapunov, 2)

}

#endif

