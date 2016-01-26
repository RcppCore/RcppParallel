//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_AS_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_AS_SIZE_HPP_INCLUDED

#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/assert.hpp>

namespace nt2
{
  namespace details
  {
    // single scalar case : generate [s s]
    template<typename S, typename H>
    BOOST_FORCEINLINE auto as_size( S const& s
                                  , ext::scalar_< ext::arithmetic_<H> > const&
                                  )
    -> decltype(nt2::of_size(s,s))
    {
      return nt2::of_size(s,s);
    }

    // fusion sequence case : return s itself
    template<typename S, typename H>
    BOOST_FORCEINLINE S const& as_size( S const& s
                                      , ext::fusion_sequence_<H> const&
                                      )
    {
      return s;
    }

    // ast case : evaluate the table inside the result
    template<typename S, typename H, typename D>
    BOOST_FORCEINLINE of_size_max as_size(S const& s, ext::ast_<H,D> const&)
    {
      BOOST_ASSERT_MSG( nt2::isrow(s)
                      , "Error: Size vector must be a row vector."
                      );

      std::ptrdiff_t n = nt2::first_index<1>(s);
      std::size_t l = nt2::length(s);
      of_size_max that;

      if(l > 1)
      {
        for(std::size_t i=0; i < l; ++i) that[i] = s(n+i);
      }
      else
      {
        that[0] = that[1] = s(n);
      }

      return that;
    }
  }

  /*
    @brief Turn value into a proper size object

    Build an of_size_ instance based on its parameters and following the
    Matlab semantic of sizes.

    @par Semantic:

    For any value @c s of type @c S, the code:

    @code
    auto r = as_size(s);
    @endcode

    is equivalent to:

    @code
    auto r = of_size(s,s);
    @endcode

    if @c S is a scalar type, to:

    @code
    auto r = s;
    @endcode

    if @c S is a Fusion Sequence type, and to:

    @code
    auto r = of_size(s(1), ..., s(length(s)));
    @endcode

    if @c S is a non-scalar expression.

    @param s Value to convert
    @return An instance of of_size built properly.
  */
  template<typename S>
  BOOST_FORCEINLINE auto as_size(S const& s)
    -> decltype(nt2::details::as_size(s, nt2::meta::hierarchy_of_t<S>()))
  {
    return nt2::details::as_size(s, nt2::meta::hierarchy_of_t<S>());
  }
  /*
    @brief Turn value into a proper size object

    Build an of_size_ instance based on its parameters and following the
    MAtlab semantic of sizes.

    @par Semantic:

    For any values <tt>s0,s1,sn...</tt> of type @c S, the code:

    @code
    auto r = as_size(s0,s1,sn...);
    @endcode

    is equivalent to:

    @code
    auto r = of_size(s0,s1,sn...);
    @endcode

    if @c S is a scalar type.:

    @param s0 First dimension of the resulting size
    @param s1 Second dimension of the resulting size
    @param sn Other dimensions of the resulting size

    @return An instance of of_size built properly.
  */
  template<typename S0, typename S1, typename... Sn>
  BOOST_FORCEINLINE auto as_size(S0 const& s0, S1 const& s1, Sn const&... sn)
    -> decltype(nt2::of_size(s0,s1,sn...))
  {
    return nt2::of_size(s0,s1,sn...);
  }
}

#endif
