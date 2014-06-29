/**
 * @title Parallel Matrix Transformation
 * @author JJ Allaire
 * @license GPL (>= 2)
 * @tags matrix TBB parallel
 * @summary Demonstrates transforming a matrix in parallel using 
 *   Intel TBB (Threading Building Blocks). 
 *
 * The **TBB** package includes an interface to the [Intel 
 * TBB](https://www.threadingbuildingblocks.org/) library for parallel 
 * programming with C++. This article describes using TBB to transform an R
 * matrix in parallel.
 */

/**
 * First a serial version of the matrix transformation. We take the square root 
 * of each item of a matrix and return a new matrix with the tranformed values.
 * We do this by using `std::transform` to call the `sqrt` function on each
 * element of the matrix:
 */

#include <Rcpp.h>
using namespace Rcpp;

#include <cmath>

// [[Rcpp::export]]
NumericMatrix matrixSqrt(NumericMatrix orig) {

  // allocate the matrix we will return
  NumericMatrix mat(orig.nrow(), orig.ncol());

  // transform it
  std::transform(orig.begin(), orig.end(), mat.begin(), ::sqrt);

  // return the new matrix
  return mat;
}

/**
 * Now we adapt our code to run in parallel using Intel TBB. We'll use the 
 * `tbb::parallel_for` function to do this. The TBB library takes care of 
 * dividing up work between threads, our job is to implement a "Body"
 * functor that is called by the TBB scheduler. 
 * 
 * The `SqrtBody` functor below includes pointers to the input matrix as 
 * well as the output matrix. Within it's `operator()` method it 
 * performs a `std::transform` with the `sqrt` function on the array
 * elements specified by the `range` argument:
 */

// [[Rcpp::depends(TBB)]]
#include <tbb/tbb.h>

struct SqrtBody
{
   // source matrix
   double * const input;
   
   // destination matrix
   double* output;
   
   // initialize with source and destination
   SqrtBody(double * const input, double* output) 
      : input(input), output(output) {}
   
   // take the square root of the range of elements requested
   void operator()(const tbb::blocked_range<size_t>& range) const {
      std::transform(input + range.begin(),
                     input + range.end(),
                     output + range.begin(),
                     ::sqrt);
   }
};

/**
 * Here's the parallel version of our matrix transformation function that
 * makes uses of the `SqrtBody` functor. The main difference is that 
 * rather than calling `std::transform` directly, the `tbb::parallel_for`
 * function is called with the range to operate on (based on the length
 * of the input matrix) and an instance of `SqrtBody`:
 */

// [[Rcpp::export]]
NumericMatrix parallelMatrixSqrt(NumericMatrix orig) {

   // allocate the matrix we will return
   NumericMatrix mat(orig.nrow(), orig.ncol());
   
   // transform it in parallel
   tbb::parallel_for(tbb::blocked_range<size_t>(0, orig.length()),
                     SqrtBody(orig.begin(), mat.begin()));
   
   // return the new matrix
   return mat;
}

/**
 * A comparison of the performance of the two functions shows the parallel
 * version performing about 2.5 times as fast on a machine with 4 cores:
 */

/*** R

# allocate a matrix
m <- matrix(as.numeric(c(1:1000000)), nrow = 1000, ncol = 1000)

# ensure that serial and parallel versions give the same result
stopifnot(identical(matrixSqrt(m), parallelMatrixSqrt(m)))

# compare performance of serial and parallel
library(rbenchmark)
res <- benchmark(matrixSqrt(m),
                 parallelMatrixSqrt(m),
                 order="relative")
res[,1:4]
*/

/**
 * If you want to try out TBB you can install the package from it's GitHub
 * repository at:
 * 
 * ```r 
 * devtools::install_github("jjallaire/tbb") 
 * ```
 */

