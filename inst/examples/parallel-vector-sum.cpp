
#include <Rcpp.h>
using namespace Rcpp;

#include <algorithm>

// [[Rcpp::export]]
double vectorSum(NumericVector x) {
   return std::accumulate(x.begin(), x.end(), 0.0);
}

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

struct Sum : public RcppParallel::Worker
{   
   // source vector
   double * input;
   
   // value that I have accumulated
   double value;
   
   // constructors
   Sum() : input(NULL), value(0) {}
   Sum(double* input) : input(input), value(0) {}
   
   // accumulate just the element of the range I've been asked to
   void operator()(std::size_t begin, std::size_t end) {
      value += std::accumulate(input + begin, input + end, 0.0);
   }
   
   // split me from another Sum
   void split(const Sum& source) {
      input = source.input;
      value = 0;
   }
    
   // join my value with that of another Sum
   void join(const Sum& rhs) { 
      value += rhs.value; 
   }
};

// [[Rcpp::export]]
double parallelVectorSum(NumericVector x) {
   
   // declare the SumBody instance that takes a pointer to the vector data
   Sum sum(x.begin());
   
   // call parallel_reduce to start the work
   RcppParallel::parallelReduce(0, x.length(), sum);
   
   // return the computed sum
   return sum.value;
}


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
