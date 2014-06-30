/**
 * @title Parallel Vector Sum using Rcpp and TBB
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
 * `tbb::parallel_reduce` function to do this. As with the previous article 
 * describing `tbb::parallel_for`, we implement a "Body" functor with our logic 
 * and TBB takes care of scheduling work on threads and calling our functor when
 * required. For parallel_reduce the functor has three jobs:
 * 
 * 1. Implement a standard and "splitting" constructor. The standard constructor
 * takes a pointer to the array that will be traversed and sets it's sum 
 * variable to 0. The splitting constructor is called when work needs to be 
 * split onto other threads---it takes a reference to the instance it is being 
 * split from and simply copies the pointer to the input array and sets it's 
 * internal sum to 0.
 * 
 * 2. Implement `operator()` to perform the summing. Here we just call
 * `std::accumulate` as we did in the serial version, but limit the accumulation
 * to the items specified by the `range` argument (note that other threads will
 * have been given the task of processing other items in the input array). We
 * save the accumulated value in our `sum` member variable.
 * 
 * 3. Finally, we implement a `join` method which composes the operations of two
 * Body instances that were previously split. Here we simply add the accumulated
 * sum of the instance we are being joined with to our own.
 *
 * Here's the definition of the `SumBody` functor:
 * 
 */

// [[Rcpp::depends(TBB)]]
#include <tbb/tbb.h>

struct SumBody {
   
   // source vector
   double * const input;
   
   // sum that I have accumulated
   double sum;
   
   // standard and splitting constructor  
   SumBody(double * const input) : input(input), sum(0) {}
   SumBody(SumBody& body, tbb::split) : input(body.input), sum(0) {}
   
   // accumulate just the element of the range I've been asked to
   void operator()(const tbb::blocked_range<size_t>& r) {
      sum += std::accumulate(input + r.begin(), input + r.end(), 0.0);
   }
   
   // join my sum with another one
   void join(SumBody& rhs) { sum += rhs.sum; }
};

/**
 * Now that we've defined the functor, implementing the parallel sum 
 * function is straightforward. Just initialize an instance of `SumBody`
 * with a pointer to the input data and call `tbb::parallel_reduce`:
 */

// [[Rcpp::export]]
double parallelVectorSum(NumericVector x) {
   
   // declare the SumBody instance that takes a pointer to the vector data
   SumBody sumBody(x.begin());
   
   // call parallel_reduce to start the work
   tbb::parallel_reduce(tbb::blocked_range<size_t>(0, x.length()), sumBody);
   
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

