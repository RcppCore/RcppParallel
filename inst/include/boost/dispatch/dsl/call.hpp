//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DSL_CALL_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// This file generate basic EDSL expression wrapper over any nt2 function
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace dispatch { namespace tag
{
  /// INTERNAL ONLY
  struct ast_ {};
}
namespace meta
{
  template<class T>
  struct is_formal : is_formal<typename T::parent>
  {
  };

  template<>
  struct is_formal<tag::formal_>
   : mpl::true_
  {
  };

  template<class T>
  struct is_formal<unknown_<T> >
   : mpl::false_
  {
  };
} } }

////////////////////////////////////////////////////////////////////////////////
// Defines the catch-all call for proto expression
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_REGISTER_G_TO_IF( unspecified_<Func>
                               , tag::formal_
                               , (Func)(...A)
                               , (mpl::and_< mpl::not_< is_formal<Func> >
                                           , any < boost::proto::
                                                   is_expr<boost::mpl::_>
                                                 , A...
                                                 >
                                           >
                                 )
                               , (unspecified_<A>...)
                               , (implement<Func(tag::ast_), tag::formal_>)
                               )

  template<class Func,class Dummy>
  struct implement<Func(tag::ast_),tag::formal_,Dummy>
  {
    template<class Sig>
    struct result;

    template<class This, class... A>
    struct result<This(A...)>
    {
      typedef typename boost::proto::result_of::
      make_expr < Func
                , typename meta::as_ref<A>::type...
                >::type type;
    };
    template<class... A>
    BOOST_FORCEINLINE
    typename result<implement(A&&...)>::type
    operator()(A&&... a) const
    {
      return boost::proto::
      make_expr< Func >
               ( boost::reference_wrapper< typename boost::remove_reference< typename meta::as_ref<A&&>::type >::type >(a)... );
    }
  };
} } }

#endif
