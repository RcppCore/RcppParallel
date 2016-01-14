// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
#include <Rcpp.h>
using namespace Rcpp;

#include <boost/simd/sdk/simd/algorithm.hpp>

struct plus
{
   template <class T>
   T operator()(const T& lhs, const T& rhs) const
   {
      return lhs + rhs;
   }
};

// [[Rcpp::export]]
double simd_sum(NumericVector x)
{
   return boost::simd::accumulate(
      x.begin(),
      x.end(),
      0.0,
      plus()
   );
}

/***R
n <- 1024 * 1000
data <- rnorm(n)
simd_sum(data)
microbenchmark(R = sum(data), simd = simd_sum(data))
*/