// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD 1
#include <RcppParallel.h>
#include <Rcpp.h>
using namespace Rcpp;

#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/sdk/config/is_supported.hpp>
#include <boost/config.hpp>

// Try playing around with the '-march' flag to see what support is detected.
// Note that most modern processors will implement instructions up to SSE3,
// but certain AVX and FMA instructions are only available on newer CPUs.

// [[Rcpp::export]]
void simd_capabilities() {
   
   using boost::simd::is_supported;
   using namespace boost::simd::tag;
   
   std::cout << "SIMD Capabilities\n"
             << "=================\n\n";
   
   std::cout << "AVX2:   " << is_supported<avx2_>()   << "\n"
             << "AVX:    " << is_supported<avx_>()    << "\n"
             << "FMA4:   " << is_supported<fma4_>()   << "\n"
             << "FMA3:   " << is_supported<fma3_>()   << "\n"
             << "SSE4a:  " << is_supported<sse4a_>()  << "\n"
             << "SSE4_2: " << is_supported<sse4_2_>() << "\n"
             << "SSE4_1: " << is_supported<sse4_1_>() << "\n"
             << "SSE3:   " << is_supported<sse3_>()   << "\n"
             << "SSE2:   " << is_supported<sse2_>()   << "\n"
             << "SSE:    " << is_supported<sse_>()    << "\n";
}

/***R
simd_capabilities()
*/
