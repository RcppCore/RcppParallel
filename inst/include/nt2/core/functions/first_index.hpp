//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIRST_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIRST_INDEX_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the first_index function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for first_index functor
    **/
    struct first_index_ : ext::abstract_<first_index_>
    {
      typedef ext::abstract_<first_index_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_first_index_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::first_index_, Site> dispatching_first_index_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::first_index_, Site>();
    }
    template<class... Args>
    struct impl_first_index_;
  }

  /*!
    @brief First index of an expression

    @tparam
    @param

    @return
  **/
  template<std::size_t Dims,class A0>
  typename  boost::dispatch::meta::
            call<tag::first_index_(A0 const&, boost::mpl::size_t<Dims>)>::type
  first_index(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::first_index_, A0>::type callee;
    return callee(a0, boost::mpl::size_t<Dims>() );
  }

  /*!
    @brief First index of an expression

    @param a0
    @param dim

    @return
  **/
  template<class A0, class Dim>
  typename  boost::dispatch::meta::
            call<tag::first_index_(A0 const&, Dim const&)>::type
  first_index(A0 const& a0, Dim const& dim)
  {
    typename boost::dispatch::make_functor<tag::first_index_, A0>::type callee;
    return callee(a0, dim);
  }
}

#endif
