//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_SCALAR_ISULPEQUAL_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_SCALAR_ISULPEQUAL_HPP_INCLUDED

#include <nt2/predicates/functions/isulpequal.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/is_less_equal.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( isulpequal_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef bool result_type;
    typedef typename meta::as_real<A0>::type r_type;
    BOOST_FORCEINLINE
      result_type operator()(const A0& a0, const A1& a1) const
    {

      return nt2::ulpdist(a0, a1) <= Half<r_type>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( isulpequal_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              (scalar_<floating_<A2> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& a1, const A2& a2) const
    {
      return nt2::ulpdist(a0, a1) <= a2;
    }
  };
} }

#endif
