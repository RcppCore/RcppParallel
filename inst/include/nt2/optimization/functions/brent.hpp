//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_BRENT_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_BRENT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/optimization/options.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief brent generic tag

     Represents the brent function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct brent_ : ext::unspecified_<brent_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<brent_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_brent_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::brent_, Site> dispatching_brent_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::brent_, Site>();
   }
   template<class... Args>
   struct impl_brent_;
  }
  /*!
   * Applies brent algorithm to find local minimum of a function
   *
   * \param f     Function to optimize
   * \param x0    Initial value
   * \param low   Lower bound of search interval
   * \param up    Upper bound of search interval
   * \param opt   Options pack related to the minimization handling
   *
   * \return  a tuple containing the result of the minimization, the value of the
   *          function at minimum, the number of required iteration and a boolean
   *          notifying success of convergence.
   */
  template<class T,class F, class X, class L, class U, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::brent_( F
                                  , T,T,T
                                  , details::optimization_settings<T> const&
                                  )
                      >::type
  brent(F f, X x0, L low, U up, nt2::details::option_expr<Xpr> const& opt)
  {

    typename boost::dispatch::make_functor<tag::brent_, F>::type callee;
    return callee ( f
                  , static_cast<T>(x0)
                  , static_cast<T>(low)
                  , static_cast<T>(up)
                  , details::optimization_settings<T>(opt)
                  );
  }
  /// @overload
  template<class T,class F, class X, class L, class U> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::brent_( F
                                  , T,T,T
                                  , details::optimization_settings<T> const&
                                  )
                      >::type
  brent(F f, X x0, L low, U up)
  {
    typename boost::dispatch::make_functor<tag::brent_, F>::type callee;
    return callee ( f
                  , static_cast<T>(x0)
                  , static_cast<T>(low)
                  , static_cast<T>(up)
                  , details::optimization_settings<T>()
                  );
  }


}

#endif
