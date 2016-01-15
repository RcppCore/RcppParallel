// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
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

#include <boost/simd/arithmetic/include/functions/fast_sqrt.hpp>

// NOTE: To use the bundled SIMD functions, it looks like we need the
// following header. We should expose all of these functions and auto-include
// them in a utility namespace so users don't have to keep track of this sort
// of thing.
#include <boost/dispatch/functor/meta/call.hpp>

// It also stinks that we have to wrap it in our own functor. Surely
// there's a better way?
struct fast_sqrt {
   template <typename T>
   T operator()(const T& t) { return boost::simd::fast_sqrt(t); }
};

// [[Rcpp::export]]
NumericVector simd_sqrt(NumericVector data)
{
   return simd::transform(data, fast_sqrt());
}

/*** R
data <- as.numeric(1:16)
simd_add_two(data)
simd_add(data, data)
simd_sum(data)
simd_sqrt(data)
*/
