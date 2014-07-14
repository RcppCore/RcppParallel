#include <Rcpp.h>
using namespace Rcpp;

#include <cmath>

/**
 * 
 * TODO: R implementation
 * 
 */


/**
 * Port of R code to Rcpp (serial version)
 */

double kl_divergence(NumericVector vec1, NumericVector vec2) {
  
  double rval = 0;
  for (int i = 0; i < vec1.size(); i++) {
      double r = 0;
      if (vec1[i] > 0 && vec2[i] > 0) {
        r = std::log(vec1[i]/vec2[i]) * vec1[i];
      }
      rval += r;
  }
  return rval;  
}

// [[Rcpp::export]]
NumericMatrix rcpp_js_distance(NumericMatrix mat) {
  
  // allocate the matrix we will return
  NumericMatrix rmat(mat.nrow(), mat.nrow());

  for (int i = 0; i < rmat.nrow(); i++) {
    for (int j = 0; j < i; j++) {
      NumericVector avg = (mat(i,_) + mat(j,_))/2;
      double d1 = kl_divergence(mat(i,_), avg);
      double d2 = kl_divergence(mat(j,_), avg);
      rmat(i,j) = std::sqrt(.5 * (d1 + d2));
    }
  }
  return rmat;
}

/**
 * Parallel version. A few notes about the implementation:
 * 
 * - To implement a parallel version we need to create a [function 
 * object](http://en.wikipedia.org/wiki/Function_object) that can process
 * discrete chunks of work (i.e. ranges of input index).
 * 
 * - Since the parallel version will be called from background threads, we can't
 * use R and Rcpp APIs directly. Rather, we use the threadsafe `RMatrix`
 * accessor class provided by RcppParallel to read and write to directly the
 * underlying matrix memory.
 * 
 * - This implemention will gain performance in two ways: (1) parallel 
 * processing to divide the work amound threads; and (2) using the RMatrix class
 * to directly access memory removes some additional function call and copying
 * overhead.
 * 
 * You'll also notice that the computation of the average of the two rows is
 * done using `std::transform` from the STL rather than Rcpp vector sugar (since
 * we can't rely on Rcpp classes in a background thread).
 * 
 * Here's the `JsDistance` function object:
 */

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

struct JsDistance : public Worker {
   
   // input matrix to read from
   RMatrix<double> input;
   
   // output matrix to write to
   RMatrix<double> output;
   
   // initialize from Rcpp input and output matrixes (the RMatrix class
   // can be automatically converted to from the Rcpp matrix type)
   JsDistance(NumericMatrix input, NumericMatrix output)
      : input(input), output(output) {}
   
   // function call operator that work for the specified range (begin/end)
   void operator()(std::size_t begin, std::size_t end) {
      for (int i = begin; i < end; i++) {
         for (int j = 0; j < i; j++) {
            
            // rows we will operate on
            RMatrix<double>::Row row1 = input.row(i);
            RMatrix<double>::Row row2 = input.row(j);
            
            // compute the average using std::tranform from the STL
            std::vector<double> avg(row1.length());
            std::transform(row1.begin(), row1.end(), // input range 1
                           row2.begin(),             // input range 2
                           avg.begin(),              // output range 
                           average);                 // function to apply
              
            // calculate divergences
            double d1 = kl_divergence(row1, avg);
            double d2 = kl_divergence(row2, avg);
               
            // write to output matrix
            output(i,j) = sqrt(.5 * (d1 + d2));
         }
      }
   }
   
   // kl_divergence helper function
   double kl_divergence(RMatrix<double>::Row row, const std::vector<double>& avg) {
      double rval = 0;
      for (int i = 0; i < row.length(); i++) {
         double r = 0;
         if (row[i] > 0 && avg[i] > 0)
            r = log(row[i]/avg[i]) * row[i];
         rval += r;
      }
      return rval;  
   }
   
   // average helper function (static so that we can pass it easily to std::transform)
   static double average(double val1, double val2) {
      return (val1 + val2) / 2;
   }
};

/**
 * Now that we have the `JsDistance` function object we can pass it to 
 * `parallelFor`, specifying an iteration range based on the number of rows in
 * the input matrix:
 */

// [[Rcpp::export]]
NumericMatrix rcpp_parallel_js_distance(NumericMatrix mat) {
  
   // allocate the matrix we will return
   NumericMatrix rmat(mat.nrow(), mat.nrow());

   // create the worker
   JsDistance jsDistance(mat, rmat);
     
   // call it with parallelFor
   parallelFor(0, mat.nrow(), jsDistance);

   return rmat;
}


/**
 * Comparing the results on a MacBook Pro with 4 cores (8 with hyperthreading) 
 * we see a roughly 10x performance gain (about 2.5x is a result of lower-level 
 * access to the Matrix data and 4x a result of parallelism):
 */

/*** R

# create a matrix
n  = 1000
m = matrix(runif(n*10), ncol = 10)
m = m/rowSums(m)

# ensure that serial and parallel versions give the same result
all.equal(js_distance(m), parallel_js_distance(m)) 

# compare performance
library(rbenchmark)
res <- benchmark(rcpp_js_distance(m),
                 rcpp_parallel_js_distance(m),
                 replications = 10,
                 order="relative")
res[,1:4]
*/


