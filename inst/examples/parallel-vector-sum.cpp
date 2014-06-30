/**
 * @title Parallel Vector Sum using TBB
 * @author JJ Allaire
 * @license GPL (>= 2)
 * @tags TBB parallel
 * @summary Demonstrates computing the sum of a vector in parallel using 
 *   Intel TBB (Threading Building Blocks). 
 *
 * The **TBB** package includes an interface to the [Intel 
 * TBB](https://www.threadingbuildingblocks.org/) library for parallel 
 * programming with C++. This article describes using TBB to compute the
 * sum of a vector in parallel.
 */

/**
 * First a serial version of computing the sum of a vector. For this we use
 * a simple call to the STL `std::accumulate` function:
 */

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double vectorSum(NumericVector x) {
   return std::accumulate(x.begin(), x.end(), 0.0);
}

/**
 * Now we adapt our code to run in parallel using Intel TBB. We'll use the 
 * `tbb::parallel_reduce` function to do this:
 */

// [[Rcpp::depends(TBB)]]
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
   
   // declare the SumBody instance that takes a pointer to the vector data
   SumBody sumBody(x.begin());
   
   // call parallel_reduce to start the work
   parallel_reduce(blocked_range<size_t>(0, x.length()), sumBody);
   
   // return the computed sum
   return sumBody.sum;
}

/**
 * A comparison of the performance of the two functions shows the parallel
 * version performing about 4 times as fast on a machine with 4 cores:
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

/**
 * If you want to try out TBB you can install the package from it's GitHub
 * repository at:
 * 
 * ```r 
 * devtools::install_github("jjallaire/TBB") 
 * ```
 * 
 * Note that the package is currently only available for the Linux and
 * Mac OS X platforms.
 */

