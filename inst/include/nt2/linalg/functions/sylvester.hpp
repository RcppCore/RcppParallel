//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SYLVESTER_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SYLVESTER_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag sylvester_ of functor sylvester
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct sylvester_ :   ext::unspecified_<sylvester_>
    {
      typedef ext::unspecified_<sylvester_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_sylvester_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::sylvester_, Site>
    dispatching_sylvester_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::sylvester_, Site>();
    }
    template<class... Args>
    struct impl_sylvester_;
  }
  /**
   * @brief solve the sylvester equation a*x*b+x = c
   *
   *
   * @param  a  Matrix expression
   * @param  b  Matrix expression
   * @param  c  Matrix expression
   *
   * @return a matrix containing the solution
   **/


  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sylvester_, sylvester, 3)

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sylvester_, sylvester, 2)

}

#endif

