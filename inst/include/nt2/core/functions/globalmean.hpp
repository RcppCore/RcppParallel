//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALMEAN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalmean functor
    **/
    struct globalmean_ : ext::abstract_<globalmean_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<globalmean_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_globalmean_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalmean_, Site> dispatching_globalmean_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::globalmean_, Site>();
    }
    template<class... Args>
    struct impl_globalmean_;
  }

  /*!
    @brief Mean of all the elements of an expression

    Computes the mean of all the elements of a table expression

    @par Semantic

    For any table expression :

    @code
    T r = globalmean(t);
    @endcode

    is equivalent to:

    @code
    T r = mean(t(_))(1);
    @endcode

    @see @funcref{colon}, @funcref{mean}
    @param a0 Table to process

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmean_, globalmean, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( globalmean_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::mean_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::mean_>(), a0);
    }
  };
} }

#endif
