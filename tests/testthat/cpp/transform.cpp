/**
 * @title Transforming a Matrix in Parallel using RcppParallel
 * @author JJ Allaire
 * @license GPL (>= 2)
 */
 
#include <Rcpp.h>
using namespace Rcpp;

#include <cmath>
#include <algorithm>

double timesTwo(double x) {
   return x * 2;
}

// [[Rcpp::export]]
NumericMatrix matrixTimesTwo(NumericMatrix orig) {

  // allocate the matrix we will return
  NumericMatrix mat(orig.nrow(), orig.ncol());

  // transform it
  std::transform(orig.begin(), orig.end(), mat.begin(), ::timesTwo);

  // return the new matrix
  return mat;
}
// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

struct TimesTwo : public Worker
{
   // source matrix
   const RMatrix<double> input;
   
   // destination matrix
   RMatrix<double> output;
   
   // initialize with source and destination
   TimesTwo(const NumericMatrix input, NumericMatrix output) 
      : input(input), output(output) {}
   
   void operator()(std::size_t begin, std::size_t end) {
      std::transform(input.begin() + begin, 
                     input.begin() + end, 
                     output.begin() + begin, 
                     ::timesTwo);
   }
};

// [[Rcpp::export]]
NumericMatrix parallelMatrixTimesTwo(NumericMatrix x) {
  
  // allocate the output matrix
  NumericMatrix output(x.nrow(), x.ncol());
  
  // TimesTwo functor (pass input and output matrixes)
  TimesTwo timesTwo(x, output);
  
  // call parallelFor to do the work
  parallelFor(0, x.nrow() * x.ncol(), timesTwo);
  
  // return the output matrix
  return output;
}

