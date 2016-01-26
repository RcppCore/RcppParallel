//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_TABLE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_TABLE_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/core/container/table/adapted/table.hpp>
#include <nt2/include/functions/construct.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/memory/adapted/container_ref.hpp>
#include <nt2/sdk/meta/layout.hpp>
#include <nt2/core/settings/locality.hpp>
#include <boost/type_traits/is_same.hpp>
#include <type_traits>

// Disable the 'class : multiple assignment operators specified' warning
#if defined(BOOST_MSVC)
#pragma warning( push )
#pragma warning( disable : 4522 ) // multiple assignment operators specified
#endif

namespace nt2 { namespace container
{
  template<typename T, typename S>
  struct  table
        : expression< boost::proto::basic_expr< nt2::tag::terminal_
                                              , boost::proto::term
                                                < nt2::memory
                                                     ::container< nt2::tag::table_
                                                                , T,S>
                                                                >
                                              >
                    , nt2::memory::container<nt2::tag::table_,T,S>
                    >
  {
    typedef nt2::memory::container<nt2::tag::table_,T,S>           container_type;
    typedef expression< boost::proto::basic_expr< nt2::tag::terminal_
                                                , boost::proto::term<container_type>
                                                 >
                      , container_type
                      >                                           nt2_expression;

    typedef typename container_type::pointer                      pointer;
    typedef typename container_type::const_pointer                const_pointer;
    typedef typename container_type::iterator                     iterator;
    typedef typename container_type::const_iterator               const_iterator;
    typedef typename container_type::allocator_type               allocator_type;

    //==========================================================================
    //  table default constructor
    //==========================================================================
    table() {}

    //==========================================================================
    //  table constructor from its allocator
    //==========================================================================
    table( allocator_type const& a ) : nt2_expression(container_type(a)) {}

    //==========================================================================
    // table copy constructor
    //==========================================================================
    table( table const& a0 ) : nt2_expression(a0)
    {
    }

    //==========================================================================
    // table constructor from a single initializer.
    // This version handles initializing from of_size or expression.
    //==========================================================================

    template<typename A0>
    table( A0 const& a0)
    {
      nt2::construct(*this,a0);
    }

    //==========================================================================
    // table constructor from a pair of initializer.
    //==========================================================================
    template<typename A0, typename A1>
    table( A0 const& a0, A1 const& a1 )
    {
      nt2::construct(*this,a0,a1);
    }

    //==========================================================================
    // table constructor from a triplet of initializer.
    // This version handles initializing from : { size, Iterator, Iterator }
    //==========================================================================
    template<typename A0, typename A1, typename A2>
    table( A0 const& a0, A1 const& a1, A2 const& a2 )
    {
      nt2::construct(*this,a0,a1,a2);
    }

    //==========================================================================
    // Enable base expression handling of assignment
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , table&
                              >::type
    operator=(Xpr const& xpr)
    {
      using check = boost::mpl::bool_
                    <  meta::is_device_assign<Xpr,table>::value
                    && meta::is_container_and_terminal<Xpr>::value
                    >;

      return eval(xpr,check{});
    }

    template<class Xpr> BOOST_FORCEINLINE
    table& eval(Xpr const& xpr, boost::mpl::true_ const&)
    {
      boost::proto::value(*this).assign(boost::proto::value(xpr));
      return *this;
    }

    template<class Xpr> BOOST_FORCEINLINE
    table& eval(Xpr const& xpr, boost::mpl::false_ const&)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE table& operator=(table const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    iterator        begin()       { return boost::proto::value(*this).begin(); }
    const_iterator  begin() const { return boost::proto::value(*this).begin(); }

    iterator        end()       { return boost::proto::value(*this).end(); }
    const_iterator  end() const { return boost::proto::value(*this).end(); }
  };
} }

#if defined(BOOST_MSVC)
#pragma warning( pop )
#endif

#endif
