//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALNORM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALNORM2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalnorm2 functor
    **/
    struct globalnorm2_ : ext::abstract_<globalnorm2_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<globalnorm2_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_globalnorm2_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalnorm2_, Site> dispatching_globalnorm2_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::globalnorm2_, Site>();
    }
    template<class... Args>
    struct impl_globalnorm2_;
  }

  /*!
    @brief euclidian norm of a whole table expression elements

    @par Semantic

    For any table expression of T @c t integer or weights w   and any integer @c n:

    @code
    T r = globalnorm2(t);
    @endcode

    is equivalent to:

    if w is an integer

    @code
    T r = norm2(t(_))(1);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @par alias:
    norm_eucl

    @see @funcref{firstnonsingleton}, @funcref{norm2}
    @param a0 Table to process

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalnorm2_, globalnorm2, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( globalnorm2_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::norm2_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::norm2_>(), a0);
    }
  };
} }

#endif
