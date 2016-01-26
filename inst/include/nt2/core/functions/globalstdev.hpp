//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALSTDEV_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALSTDEV_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/stdev.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalstdev functor
    **/
    struct globalstdev_ : ext::abstract_<globalstdev_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<globalstdev_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_globalstdev_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalstdev_, Site> dispatching_globalstdev_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::globalstdev_, Site>();
    }
    template<class... Args>
    struct impl_globalstdev_;
  }
  /*!
    @brief Standard Deviation  of all the elements of an expression

    Computes the standard deviation  of all the elements of a table expression

    @par Semantic

    For any table expression :

    @code
    T r = globalstdev(t, k);
    @endcode

    is equivalent to:

    @code
    T r = stdev(t(_), k)(1);
    @endcode


    @see @funcref{colon}, @funcref{stdev}
    @param a0 Table expression to process
    @param a1 Table expression or integer

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalstdev_, globalstdev, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalstdev_, globalstdev, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( globalstdev_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::stdev_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::stdev_>(), a0);
    }
  };
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( globalstdev_, tag::cpu_
                              , (A0)(A1)
                              , (unspecified_<A0>)
                              (scalar_<integer_<A1> > )
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::stdev_>
                                            , const A0&
                                            , const A1&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
       return global(nt2::functor<tag::stdev_>(), a0, a1);
    }
  };
} }

#endif
