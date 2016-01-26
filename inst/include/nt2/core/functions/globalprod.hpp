//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALPROD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALPROD_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the functor
    **/
    struct globalprod_ : ext::abstract_<globalprod_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<globalprod_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_globalprod_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalprod_, Site> dispatching_globalprod_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::globalprod_, Site>();
    }
    template<class... Args>
    struct impl_globalprod_;
  }

 /*!
    @brief product of all the elements of a table expression .

    Computes the product of all the elements of a table expression

    @par Semantic

    For any table expression @c t:

    @code
    T r = globalprod(t);
    @endcode

    is equivalent to:

    @code
    T r = prod(a(_))(1);
    @endcode

    @param a0 Table expression to process
    @return A scalar

  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalprod_       , globalprod, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  BOOST_DISPATCH_IMPLEMENT  ( globalprod_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call < tag::global_(nt2::functor<tag::prod_>
                                , const A0&)
                                >::type                             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::prod_>(), a0);
    }
  };
} }
#endif
