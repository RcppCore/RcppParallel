#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double vectorSum(NumericVector x) {
   return std::accumulate(x.begin(), x.end(), 0.0);
}

// [[Rcpp::depends(tbb)]]
#include <tbb/tbb.h>
using namespace tbb;

struct SumBody {
   
   // source vector
   double * const input;
   
   // current sum
   double sum;
   
   SumBody(double * const input) : input(input), sum(0) {}
   SumBody(SumBody& body, tbb::split) : input(body.input), sum(0) {}
   
   void operator()(const blocked_range<size_t>& r) {
      sum += std::accumulate(input + r.begin(), input + r.end(), 0.0);
   }
   
   void join(SumBody& rhs) { sum += rhs.sum; }
};


// [[Rcpp::export]]
double parallelVectorSum(NumericVector x) {
   SumBody sumBody(x.begin());
   parallel_reduce(blocked_range<size_t>(0, x.length()), sumBody);
   return sumBody.sum;
}

/*** R

# allocate a vector
v <- c(1:10000000)

# ensure that serial and parallel versions give the same result
stopifnot(identical(vectorSum(v), parallelVectorSum(v)))

# compare performance of serial and parallel (set replications to 1
# to eliminate the impact of caching)
library(rbenchmark)
res <- benchmark(vectorSum(v),
                 parallelVectorSum(v),
                 order="relative")
res[,1:4]
*/


