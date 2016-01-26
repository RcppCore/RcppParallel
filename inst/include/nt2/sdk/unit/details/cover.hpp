//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_COVER_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_COVER_HPP_INCLUDED

#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/unit/details/once.hpp>
#include <nt2/sdk/unit/details/eval.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/sdk/details/io_fix.hpp>
#include <boost/simd/operator/specific/utils.hpp>
#include <boost/core/ignore_unused.hpp>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <cstddef>

/// INTERNAL ONLY TO REMOVE LATER
#define NT2_CREATE_BUF(Name,Type,Size,Min,Max)                                 \
std::vector<Type,boost::simd::allocator<Type> > Name(Size);                    \
nt2::roll( Name, Min, Max )                                                    \
/**/

/// INTERNAL ONLY TO REMOVE LATER
#define NT2_CREATE_LOGICAL_BUF(Name,Type,Size)                                 \
std::vector<Type,boost::simd::allocator<Type> > Name(Size);                    \
do                                                                             \
{                                                                              \
  for(std::size_t i=0;i<Name.size();++i) Name[i] = Type(rand() % 2);           \
} NT2_TEST_ONCE                                                          \
/**/

/// INTERNAL ONLY Make typed_value out of inputs
#define NT2_COVER_MAKE_VALUES(z,n,t)                                           \
nt2::details::make_typed_value<BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_ELEM(n,t))>\
                              (BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_SEQ_ELEM(n,t)))\
/**/

/// INTERNAL ONLY Process sequence into variadic arguments
#define NT2_ENUM_REFERENCES(I) BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(I)             \
                                            , NT2_COVER_MAKE_VALUES            \
                                            , I                                \
                                            )                                  \
/**/

namespace nt2 { namespace details
{
  // Compute test name
  template<typename Func, typename... V>
  inline std::string cover_test_name(Func f, V const&... v)
  {
    return nt2::type_id(f) + "( " + cover_typename(v...) + " )";
  }

  template<typename W, typename... V>
  inline std::string cover_typename(W const&, V const&... v)
  {
    return nt2::type_id<typename W::type>() + ", " + cover_typename(v...);
  }

  template<typename W> inline std::string cover_typename(W const&)
  {
    return nt2::type_id<typename W::type>();
  }

  // Display error result
  template<typename W, typename... V>
  inline void display_result(std::ostream& os, int i, W const& w, V const&... v)
  {
    os << boost::simd::details::display(w.load(i));
    display_result(os, i, v...);
  }

  template<typename W>
  inline void display_result(std::ostream& os, int i, W const& w)
  {
    os << boost::simd::details::display(w.load(i));
  }

  // Wrap a value and the type to load it with
  template<typename Target, typename Type> struct typed_value
  {
    Type const& value;
    using type = Target;

    BOOST_FORCEINLINE Target load(std::size_t i) const
    {
      return nt2::load<Target>( &(value[i]) );
    }
  };

  template<typename Target, typename Type>
  inline typed_value<Target,Type> make_typed_value(Type const& v)
  {
    return typed_value<Target,Type>{v};
  }

  // Short-cut for cardinal on typed_value target
  template<typename T>
  using type_card_t = typename meta::cardinal_of<typename T::type>::type;

  // Compute the value from the function and pack of typed reference inputs
  template< typename Function, typename Data, typename... V>
  inline Data compute_coverage(Function f, Data const& ref, V const&... v)
  {
    Data out(ref.size());
    auto c = boost::simd::ext::cardinal_common<type_card_t<V>::value...>::value;

    for(std::size_t i=0; i<out.size(); i+=c)
      nt2::store( f( v.load(i)... ), &out[i]);

    return out;
  }

  // Process failure and display them
  template<typename Function, typename Data, typename ULPs, typename... V>
  inline void display_cover_fails ( const char* , Function f
                                  , Data const& out, Data const& ref
                                  , ULPs const& ulps, V const&... v
                                  )
  {
    int ib = -1;
    boost::ignore_unused(f);
    auto c = boost::simd::ext::cardinal_common<type_card_t<V>::value...>::value;

    for( auto const& ff : ulps )
    {
      int ii = static_cast<int>((ff.index/c)*c);
      if(ii > ib)
      {
        typedef typename meta::strip<decltype( f( v.load(0)... ) )>::type r_t;

        std::cout << std::setprecision(20)
                  << "    {";
        display_result(std::cout,ii,v...);
        std::cout << "} => "
                  << boost::simd::details::display(nt2::load<r_t>(&out[ii]))
                  << " while expecting "
                  << boost::simd::details::display(nt2::load<r_t>(&ref[ii]))
                  << " (i.e "   << ff.ulp_error << " ULPs)"
                  << std::endl;
        ib = ii;
      }
    }
    std::cout << std::endl;
  }

  // Run the test and report any errors
  template<typename Function, typename Data, typename... V>
  inline void perform_coverage( const char* desc, const char* file, int line
                              , Function f
                              , Data const& out, Data const& ref, double N
                              , V const&... v
                              )
  {
    typedef typename Data::value_type                               t_t;
    typedef typename nt2::details::max_ulp_<t_t,t_t>::failure_type  f_t;

    double ulpd = 0;
    std::vector< f_t > ulps;
    find_ulp_error(out,ref,ulps,ulpd,N,details::max_ulps_caller());

    if(ulps.empty())
    {
      std::cout << "For " << out.size() << " samples: \n";
      nt2::details::ulp_pass(desc, ulpd, N);
    }
    else
    {
      std::cout << " *** Cover tests failed with a maximum of "
                << ulpd << " ULPs. ***\n";
      nt2::details::ulp_fail( desc, file, line, ulps.size(), N, true );
      display_cover_fails ( desc, f, out, ref, ulps, v...);
    }
  }

  // Prepare data for coverage testing
  template<typename Function, typename Data, typename... V>
  inline  void test_cover_ulp ( const char* desc, const char* file, int line
                              , Function f, Data const& ref
                              , double ulpd, V const&... v
                              )
  {
    nt2::details::perform_coverage( desc, file, line , f
                                  , nt2::details::compute_coverage(f,ref,v...)
                                  , ref , ulpd, v...
                                  );
  }
} }

#endif
