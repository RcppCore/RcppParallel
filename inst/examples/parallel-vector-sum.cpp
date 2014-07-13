
#include <Rcpp.h>
using namespace Rcpp;

#include <algorithm>

/**
 * First the serial version:
 */

// [[Rcpp::export]]
double vectorSum(NumericVector x) {
   return std::accumulate(x.begin(), x.end(), 0.0);
}

/**
 * Now the parallel version:
 */

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

struct Sum : public Worker
{   
   // source vector
   VectorReader<double> input;
   
   // value that I have accumulated
   double value;
   
   // constructors
   Sum(NumericVector x) : input(x), value(0) {}
   Sum(Sum& sum, Split) : input(sum.input), value(0) {}
   
   // accumulate just the element of the range I've been asked to
   void operator()(std::size_t begin, std::size_t end) {
      value += std::accumulate(input.begin() + begin, input.begin() + end, 0.0);
   }
     
   // join my value with that of another Sum
   void join(const Sum& rhs) { 
      value += rhs.value; 
   }
};

// [[Rcpp::export]]
double parallelVectorSum(NumericVector x) {
   
   // declare the SumBody instance that takes a pointer to the vector data
   Sum sum(x);
   
   // call parallel_reduce to start the work
   RcppParallel::parallelReduce(0, x.length(), sum);
   
   // return the computed sum
   return sum.value;
}

/**
 * Compare serial and parallel performance:
 */

/*** R
# allocate a vector
v <- as.numeric(c(1:10000000))

# ensure that serial and parallel versions give the same result
stopifnot(identical(vectorSum(v), parallelVectorSum(v)))

# compare performance of serial and parallel
library(rbenchmark)
res <- benchmark(vectorSum(v),
                 parallelVectorSum(v),
                 order="relative")
res[,1:4]
*/
