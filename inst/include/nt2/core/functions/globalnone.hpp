//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALNONE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALNONE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalnone functor
    **/
    struct globalnone_ : ext::abstract_<globalnone_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<globalnone_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_globalnone_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalnone_, Site> dispatching_globalnone_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::globalnone_, Site>();
    }
    template<class... Args>
    struct impl_globalnone_;
  }

  /*!
    @brief Checks that none element of an expression is non-zero

    @par Semantic

    For any table expression @c t:

    @code
    logical<T> r = globalnone(t);
    @endcode

    is equivalent to:

    @code
    logical<T> r = none(t(_));
    @endcode

    @see @funcref{colon}, @funcref{none}
    @param a0 Table to process

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalnone_       , globalnone, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( globalnone_
                            , tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::none_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::none_>(), a0);
    }
  };
} }

#endif
