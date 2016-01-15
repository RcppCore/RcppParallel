//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_X86_TAGS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_X86_TAGS_HPP_INCLUDED

#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/simd/sdk/simd/extensions/meta/common/tags.hpp>
#include <boost/simd/sdk/config/arch.hpp>

namespace boost { namespace simd { namespace tag
{
  // Tag hierarchy for SSE extensions
  struct sse_   : simd_ { typedef simd_   parent; };
  struct sse2_  : sse_  { typedef sse_    parent; };
  struct sse3_  : sse2_ { typedef sse2_   parent; };
  struct sse4a_ : sse3_ { typedef sse3_   parent; };

#ifdef BOOST_SIMD_ARCH_AMD
  struct ssse3_ : sse4a_  { typedef sse4a_  parent; };
#else
  struct ssse3_ : sse3_   { typedef sse3_   parent; };
#endif

  struct sse4_1_  : ssse3_  { typedef ssse3_  parent; };
  struct sse4_2_  : sse4_1_ { typedef sse4_1_ parent; };
  struct avx_     : sse4_2_ { typedef sse4_2_ parent; };
  struct fma4_    : avx_    { typedef avx_    parent; };
  struct xop_     : fma4_   { typedef fma4_   parent; };

#ifdef BOOST_SIMD_ARCH_AMD
  struct fma3_ : xop_ { typedef xop_  parent; };
#else
  struct fma3_ : avx_ { typedef avx_  parent; };
#endif

  struct avx2_ : fma3_ { typedef fma3_  parent; };

  // Tag hierarchy for mic extensions
  struct mic_ : sse2_ { typedef sse2_  parent; };
} } }

#endif
