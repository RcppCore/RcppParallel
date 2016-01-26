// Example using 'nt2::sin'.

// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

struct nt2_sin {
   template <typename T>
   T operator()(const T& data) {
      return nt2::sin(data);
   }
};

// [[Rcpp::export]]
NumericVector nt2Sin(NumericVector input) {
   NumericVector output = no_init(input.size());
   simdTransform(input.begin(), input.end(), output.begin(), nt2_sin());
   return output;
}

/*** R
set.seed(123)
data <- rnorm(1024)
stopifnot(all.equal(sin(data), nt2Sin(data)))
*/