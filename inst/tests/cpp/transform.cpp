/**
 * @title Transforming a Matrix in Parallel using RcppParallel
 * @author JJ Allaire
 * @license GPL (>= 2)
 */
 
#include <Rcpp.h>
using namespace Rcpp;

#include <cmath>
#include <algorithm>

double squareRoot(double x) {
   return ::sqrt(x);
}

// [[Rcpp::export]]
NumericMatrix matrixSqrt(NumericMatrix orig) {

  // allocate the matrix we will return
  NumericMatrix mat(orig.nrow(), orig.ncol());

  // transform it
  std::transform(orig.begin(), orig.end(), mat.begin(), squareRoot);

  // return the new matrix
  return mat;
}
// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

struct SquareRoot : public Worker
{
   // source matrix
   const RMatrix<double> input;
   
   // destination matrix
   RMatrix<double> output;
   
   // initialize with source and destination
   SquareRoot(const NumericMatrix input, NumericMatrix output) 
      : input(input), output(output) {}
   
   // take the square root of the range of elements requested
   void operator()(std::size_t begin, std::size_t end) {
      std::transform(input.begin() + begin, 
                     input.begin() + end, 
                     output.begin() + begin, 
                     squareRoot);
   }
};

// [[Rcpp::export]]
NumericMatrix parallelMatrixSqrt(NumericMatrix x) {
  
  // allocate the output matrix
  NumericMatrix output(x.nrow(), x.ncol());
  
  // SquareRoot functor (pass input and output matrixes)
  SquareRoot squareRoot(x, output);
  
  // call parallelFor to do the work
  parallelFor(0, x.nrow() * x.ncol(), squareRoot);
  
  // return the output matrix
  return output;
}

