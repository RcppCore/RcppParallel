/**
 * @title Transforming a Matrix in Parallel using RcppParallel
 * @author JJ Allaire
 * @license GPL (>= 2)
 * @tags matrix parallel featured
 * @summary Demonstrates transforming a matrix in parallel using 
 *   the RcppParallel package.
 *
 * The [RcppParallel](https://github.com/RcppCore/RcppParallel) package includes
 * high level functions for doing parallel programming with Rcpp. For example,
 * the `parallelFor` function can be used to convert the work of a standard
 * serial "for" loop into a parallel one. This article describes using
 * RcppParallel to transform an R matrix in parallel.
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
#include <algorithm>

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
 * Now we adapt our code to run in parallel. We'll use the `parallelFor` 
 * function to do this. RcppParallel takes care of dividing up work between 
 * threads, our job is to implement a "Worker" functor that is called by the 
 * RcppParallel scheduler.
 * 
 * The `SquareRoot` functor below includes pointers to the input matrix as well
 * as the output matrix. Within it's `operator()` method it performs a 
 * `std::transform` with the `sqrt` function on the array elements specified by 
 * the `range` argument:
 */

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

struct SquareRoot : public Worker
{
   // source matrix
   RMatrix<double> input;
   
   // destination matrix
   RMatrix<double> output;
   
   // initialize with source and destination
   SquareRoot(NumericMatrix input, NumericMatrix output) 
      : input(input), output(output) {}
   
   // take the square root of the range of elements requested
   void operator()(std::size_t begin, std::size_t end) {
      std::transform(input.begin() + begin, 
                     input.begin() + end, 
                     output.begin() + begin, 
                     ::sqrt);
   }
};

/**
 * Note that `SquareRoot` derives from the `RcppParallel::Worker` class, this is
 * required for function objects passed to `parallelFor`.
 * 
 * Note also that we use the `RMatrix<double>` type for accessing the matrix. 
 * This is because this code will execute on a background thread where it's not 
 * safe to call R or Rcpp APIs. The `RMatrix` class is included in the 
 * RcppParallel package and provides a lightweight, thread-safe wrapper around R
 * matrixes.
 */

/**
 * Here's the parallel version of our matrix transformation function that
 * makes uses of the `SquareRoot` functor. The main difference is that 
 * rather than calling `std::transform` directly, the `parallelFor`
 * function is called with the range to operate on (based on the length
 * of the input matrix) and an instance of `SquareRoot`:
 */

// [[Rcpp::export]]
NumericMatrix parallelMatrixSqrt(NumericMatrix x) {
  
  // allocate the output matrix
  NumericMatrix output(x.nrow(), x.ncol());
  
  // SquareRoot functor (pass input and output matrixes)
  SquareRoot squareRoot(x, output);
  
  // call parallelFor to do the work
  parallelFor(0, x.length(), squareRoot);
  
  // return the output matrix
  return output;
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
 * If you interested in learning more about using RcppParallel see 
 * [https://github.com/RcppCore/RcppParallel](https://github.com/RcppCore/RcppParallel).
 */ 

