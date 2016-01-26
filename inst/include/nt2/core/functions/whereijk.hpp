//==============================================================================
//         Copyright 2003 - 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_WHEREIJK_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_WHEREIJK_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the whereijk function
 **/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for whereijk functor
     **/
    struct whereijk_ : ext::elementwise_<whereijk_>
    {
      typedef ext::elementwise_<whereijk_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_whereijk_( ext::adl_helper(), static_cast<Args&&>(args)... )
      )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::whereijk_, Site>
    dispatching_whereijk_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::whereijk_, Site>();
    }
    template<class... Args>
    struct impl_whereijk_;
  }

  /*!
    @brief Act as : for i for j for k r(i, j, k) = f(i, j, k) ? a(i, j, k) : b(i, j, k)
    @param f Ternary Polymorphic Function object to apply to 0 based indices
    @param a First expression to process
    @param b Second expression to process

    see @funcref{if_else}, @funcref{whereij}
  **/
  template<class Functor, class A0, class A1> BOOST_FORCEINLINE
  typename meta::call<tag::whereijk_(Functor const&, A0 const&, A1 const&)>::type
  whereijk(Functor const& f, A0 const& a, A1 const& b)
  {
    return typename make_functor<tag::whereijk_, A0>::type()(f,a,b);
  }
}

#endif
