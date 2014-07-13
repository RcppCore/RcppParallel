
#include <Rcpp.h>
using namespace Rcpp;

#include <cmath>
#include <algorithm>

/**
 * First the serial version:
 */

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
 * Now the parallel version:
 */

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

struct SquareRoot : public RcppParallel::Worker
{
   // source matrix
   double* input;
   
   // destination matrix
   double* output;
   
   // initialize with source and destination
   SquareRoot() : input(NULL), output(NULL) {}
   SquareRoot(double* input, double* output) 
      : input(input), output(output) {}
   
   // take the square root of the range of elements requested
   void operator()(std::size_t begin, std::size_t end) {
      std::transform(input + begin, input + end, output + begin, ::sqrt);
   }
};

// [[Rcpp::export]]
NumericMatrix parallelMatrixSqrt(NumericMatrix x) {
  
  // allocate the output matrix
  NumericMatrix output(x.nrow(), x.ncol());
  
  // SquareRoot instance that takes a pointer to the input & output data
  SquareRoot squareRoot(x.begin(), output.begin());
  
  // call parallelFor to do the work
  RcppParallel::parallelFor(0, x.length(), squareRoot);
  
  // return the output matrix
  return output;
}

/**
 * Compare serial and parallel performance:
 */

/*** R

# allocate a matrix
m <- matrix(as.numeric(c(1:1000000)), nrow = 1000, ncol = 1000)

# compare performance of serial and parallel
library(rbenchmark)
res <- benchmark(matrixSqrt(m),
                 parallelMatrixSqrt(m),
                 order="relative")
res[,1:4]
*/


