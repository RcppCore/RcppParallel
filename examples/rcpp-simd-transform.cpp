// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallelSIMD.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace RcppParallel;

struct add_two_impl {
   
   template <typename T>
   T operator()(T data) const {
      return data + 2.0;
   }
   
   template <typename T>
   T operator()(T lhs, T rhs) const {
      return lhs + rhs;
   }
};

// [[Rcpp::export]]
NumericVector simd_add_two(NumericVector data)
{
   return simd::transform(data, add_two_impl());
}

// [[Rcpp::export]]
NumericVector simd_add(NumericVector lhs, NumericVector rhs)
{
   return simd::transform(lhs, rhs, add_two_impl());
}

struct plus {
   template <typename T>
   T operator()(const T& lhs, const T& rhs) const {
      return lhs + rhs;
   }
};

// [[Rcpp::export]]
double simd_sum(NumericVector data)
{
   return simd::accumulate(data, 0.0, plus());
}

/*** R
data <- as.numeric(1:16)
simd_add_two(data)
simd_add(data, data)
simd_sum(data)
*/
