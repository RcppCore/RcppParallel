// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD 1
#include <RcppParallel.h>
#include <Rcpp.h>
using namespace Rcpp;

// http://nt2.metascale.fr/doc/html/tutorials/simd_hello_world.html

// [[Rcpp::export]]
void HelloWorld()
{
   typedef boost::simd::pack<float> p_t;
   
   p_t res;
   p_t u(10);
   p_t r = boost::simd::splat<p_t>(11);
   
   res = (u + r) * 2.f;
   
   Rcout << res << std::endl;
}

/*** R
HelloWorld()
*/