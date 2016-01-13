// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
#include <Rcpp.h>
using namespace Rcpp;

// http://nt2.metascale.fr/doc/html/tutorials/simd_hello_world.html
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <iostream>

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
