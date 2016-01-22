// A simple example demonstration how 'simdTransform()'
// can be used.

// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

struct plus
{
   template <class T>
   T operator()(const T& lhs, const T& rhs) const
   {
      return lhs + rhs;
   }
};

// [[Rcpp::export]]
NumericVector simd_add(NumericVector lhs, NumericVector rhs)
{
   NumericVector result = no_init(lhs.size());
   simdTransform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), plus());
   return result;
}

// [[Rcpp::export]]
NumericVector cpp_add(NumericVector lhs, NumericVector rhs)
{
   return lhs + rhs;
}

/***R
set.seed(123)
n <- 1024 * 1000
lhs <- rnorm(n)
rhs <- rnorm(n)
simd <- simd_add(lhs, rhs)
cpp <- cpp_add(lhs, rhs)
stopifnot(all.equal(simd, cpp))

library(microbenchmark)
microbenchmark(
   simd = simd_add(lhs, rhs),
   cpp  = cpp_add(lhs, rhs),
   R    = lhs + rhs
)
*/
