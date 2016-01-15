//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_BUILTIN_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_BUILTIN_SHUFFLE_HPP_INCLUDED

#ifndef __has_builtin
#define __has_builtin(x) 0
#define BOOST_SIMD_NO_HAS_BUILTIN
#endif

#if (defined(__clang__) && __has_builtin(__builtin_shufflevector))              \
 || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)))

  #include <boost/preprocessor/repetition/enum.hpp>
  #include <boost/preprocessor/tuple/elem.hpp>
  #include <boost/preprocessor/seq/for_each.hpp>

  #ifdef __clang__
    #define BOOST_SIMD_BUILTIN_SHUFFLE2(a, b, n, m)                             \
    __builtin_shufflevector(a, b, BOOST_PP_ENUM(n, m, n))                       \
    /**/

    #define BOOST_SIMD_BUILTIN_SHUFFLE1(a, n, seq)                              \
    __builtin_shufflevector(a, BOOST_PP_ENUM(n, m, n))                          \
    /**/

  #else
    #define BOOST_SIMD_BUILTIN_SHUFFLE2(a, b, n, m)                             \
    __builtin_shuffle(a, b, mask_type{BOOST_PP_ENUM(n, m, n)})                  \
    /**/

    #define BOOST_SIMD_BUILTIN_SHUFFLE1(a, n, t)                                \
    __builtin_shuffle(a, mask_type{BOOST_PP_ENUM(n, m, n)})                     \
    /**/
  #endif

  #define BOOST_SIMD_DEFINE_SHUFFLE2_(z, n, t)                                                     \
  template<class Dummy>                                                                            \
  struct impl<n, Dummy>                                                                            \
  {                                                                                                \
    BOOST_FORCEINLINE static mask_type call(mask_type const a0, mask_type const a1)                \
    {                                                                                              \
      return BOOST_SIMD_BUILTIN_SHUFFLE2(a0, a1, n, t);                                            \
    }                                                                                              \
  };                                                                                               \

  #define BOOST_SIMD_DEFINE_SHUFFLE2( Tag, Macro, Hierarchy )                                      \
  BOOST_DISPATCH_IMPLEMENT( Tag, boost::simd::tag::simd_                                           \
                          , (A0)(X)                                                                \
                          , ((simd_< Hierarchy<A0>, X >))                                          \
                            ((simd_< Hierarchy<A0>, X >))                                          \
                          )                                                                        \
  {                                                                                                \
    typedef A0 result_type;                                                                        \
                                                                                                   \
    typedef typename boost::dispatch::meta::                                                       \
            as_integer< typename boost::dispatch::meta::primitive_of<A0>::type, signed >::type     \
    primitive;                                                                                     \
                                                                                                   \
    static const int M = sizeof(typename A0::native_type);                                         \
    typedef typename meta::as_simd<primitive, tag::simd_emulation_<M> >::type mask_type;           \
                                                                                                   \
    template<std::size_t N, class Dummy = void>                                                    \
    struct impl                                                                                    \
    {                                                                                              \
      BOOST_FORCEINLINE static mask_type call(mask_type const a0, mask_type const a1)              \
      {                                                                                            \
        native<primitive, tag::simd_emulation_<M> > a = a0;                                        \
        native<primitive, tag::simd_emulation_<M> > b = a1;                                        \
        return boost::dispatch::functor<tag::Tag, tag::cpu_>()(a, b)();                            \
      }                                                                                            \
    };                                                                                             \
                                                                                                   \
    BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO(2, 32, BOOST_SIMD_DEFINE_SHUFFLE2_, Macro)             \
                                                                                                   \
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const                     \
    {                                                                                              \
      return (typename A0::native_type)impl<A0::static_size>::call( (mask_type)a0()                \
                                                                  , (mask_type)a1()                \
                                                                  );                               \
    }                                                                                              \
  };                                                                                               \
  /**/

#else
  #define BOOST_SIMD_DEFINE_SHUFFLE2(Tag, Macro, Hierarchy)
#endif

#ifdef BOOST_SIMD_NO_HAS_BUILTIN
#undef __has_builtin
#endif

#endif
