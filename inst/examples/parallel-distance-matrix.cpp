/**
 * @title Parallel Distance Matrix Calculation with RcppParallel
 * @author JJ Allaire and Jim Bullard
 * @license GPL (>= 2)
 * @tags parallel featured
 * @summary Demonstrates computing an n x n distance matrix from an n x p data
 *   matrix.
 *
 * The [RcppParallel](https://github.com/RcppCore/RcppParallel) package includes
 * high level functions for doing parallel programming with Rcpp. For example, 
 * the `parallelFor` function can be used to convert the work of a standard 
 * serial "for" loop into a parallel one.
 * 
 * This article describes using RcppParallel to compute pairwise distances for
 * each row in an input data matrix and return an n x n lower-triangular
 * distance matrix which can be used with clustering tools from within R, e.g., 
 * [hclust](http://stat.ethz.ch/R-manual/R-patched/library/stats/html/hclust.html).
 */
  
/**
 * Calculating distance matrices is a common practice in clustering applications
 * (unsupervised learning). Certain clustering methods, such as partitioning 
 * around medoids (PAM) and hierarchical clustering, operate directly on this 
 * matrix.
 * 
 * A distance matrix stores the n*(n-1)/2 pairwise distances/similarities 
 * between observations in an n x p matrix where n correspond to the independent
 * observational units and p represent the covariates measured on each 
 * individual. Typically, we are limited by the size of n as the algorithm 
 * scales quadratically in both time and space in n.
 * 
 * In this example, we compute the Jensen-Shannon distance (JSD); a metric not a
 * part of base R. First, we present the R-only version:
 */

/*** R
js_distance <- function(mat) {
  kld = function(p,q) sum(ifelse(p == 0 | q == 0, 0, log(p/q)*p))
  res = matrix(0, nrow(mat), nrow(mat))
  for (i in 1:(nrow(mat) - 1)) {
    for (j in (i+1):nrow(mat)) {
      m = (mat[i,] + mat[j,])/2
      d1 = kld(mat[i,], m)
      d2 = kld(mat[j,], m)
      res[j,i] = sqrt(.5*(d1 + d2))
    }
  }
  res
}
*/


/**
 * Now a serial C++ implementation of jsDistR using Rcpp:
 */

#include <Rcpp.h>
using namespace Rcpp;

#include <cmath>

/**
 * We will benchmark the the Jensen-Shannon Distance metric 
 * (https://en.wikipedia.org/wiki/Jensen%E2%80%93Shannon_divergence)
 * 
 * Abstractly, a Distance function will take two vectors in R<sup>J</sup> and 
 * return a value in R<sup>+</sup>. In this implementation, we don't support
 * arbitrary distance metrics, i.e., the JSD code computes the values from
 * within the parallel kernel.
 * 
 * Our implementation takes three parameters: iterators to the beginning and end
 * of vector 1 and an iterator to the beginning of vector 2 (the end position of
 * vector2 is implied by the end position of vector1).
 *
 */

// generic function for kl_divergence
template <typename InputIterator1, typename InputIterator2>
inline double kl_divergence(InputIterator1 begin1, InputIterator1 end1, 
                            InputIterator2 begin2) {
  
   // value to return
   double rval = 0;
   
   // set iterators to beginning of ranges
   InputIterator1 it1 = begin1;
   InputIterator2 it2 = begin2;
   
   // for each input item
   while (it1 != end1) {
      
      // take the value and increment the iterator
      double d1 = *it1++;
      double d2 = *it2++;
      
      // accumulate if appropirate
      if (d1 > 0 && d2 > 0)
         rval += std::log(d1 / d2) * d1;
   }
   return rval;  
}

// helper function for taking the average of two numbers
inline double average(double val1, double val2) {
   return (val1 + val2) / 2;
}


// [[Rcpp::export]]
NumericMatrix rcpp_js_distance(NumericMatrix mat) {
  
   // allocate the matrix we will return
   NumericMatrix rmat(mat.nrow(), mat.nrow());
   
   for (int i = 0; i < rmat.nrow(); i++) {
      for (int j = 0; j < i; j++) {
      
         // rows we will operate on
         NumericMatrix::Row row1 = mat.row(i);
         NumericMatrix::Row row2 = mat.row(j);
         
         // compute the average using std::tranform from the STL
         std::vector<double> avg(row1.size());
         std::transform(row1.begin(), row1.end(), // input range 1
                        row2.begin(),             // input range 2
                        avg.begin(),              // output range 
                        average);                 // function to apply
      
         // calculate divergences
         double d1 = kl_divergence(row1.begin(), row1.end(), avg.begin());
         double d2 = kl_divergence(row2.begin(), row2.end(), avg.begin());
        
         // write to output matrix
         rmat(i,j) = std::sqrt(.5 * (d1 + d2));
      }
   }
   
   return rmat;
}


/**
 * Adapting the serial version to run in parallel is straightforward. A few 
 * notes about the implementation:
 * 
 * - To implement a parallel version we need to create a [function 
 * object](http://en.wikipedia.org/wiki/Function_object) that can process 
 * discrete chunks of work (i.e. ranges of input).
 * 
 * - Since the parallel version will be called from background threads, we can't
 * use R and Rcpp APIs directly. Rather, we use the threadsafe `RMatrix` 
 * accessor class provided by RcppParallel to read and write to directly the 
 * underlying matrix memory.
 * 
 * - Other than organzing the code as a function object and using `RMatrix`, the
 * parallel code is almost identical to the serial code. The main difference is 
 * that the outer loop starts with the `begin` index passed to the worker 
 * function rather than 0.
 * 
 * Parallelizing in this case has big payoff: we observe performance of about 5x
 * the serial version on a machine with 4 cores (8 with hyperthreading). Here is
 * the definition of the `JsDistance` function object:
 */

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

struct JsDistance : public Worker {
   
   // input matrix to read from
   RMatrix<double> mat;
   
   // output matrix to write to
   RMatrix<double> rmat;
   
   // initialize from Rcpp input and output matrixes (the RMatrix class
   // can be automatically converted to from the Rcpp matrix type)
   JsDistance(NumericMatrix mat, NumericMatrix rmat)
      : mat(mat), rmat(rmat) {}
   
   // function call operator that work for the specified range (begin/end)
   void operator()(std::size_t begin, std::size_t end) {
      for (int i = begin; i < end; i++) {
         for (int j = 0; j < i; j++) {
            
            // rows we will operate on
            RMatrix<double>::Row row1 = mat.row(i);
            RMatrix<double>::Row row2 = mat.row(j);
            
            // compute the average using std::tranform from the STL
            std::vector<double> avg(row1.length());
            std::transform(row1.begin(), row1.end(), // input range 1
                           row2.begin(),             // input range 2
                           avg.begin(),              // output range 
                           average);                 // function to apply
              
            // calculate divergences
            double d1 = kl_divergence(row1.begin(), row1.end(), avg.begin());
            double d2 = kl_divergence(row2.begin(), row2.end(), avg.begin());
               
            // write to output matrix
            rmat(i,j) = sqrt(.5 * (d1 + d2));
         }
      }
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
 * We now compare the performance of the three different implementations: pure
 * R, serial Rcpp, and parallel Rcpp. We won't be able to compare large matrices
 * to the R-only version as it is too slow for large matrices.
 */

/*** R

# create a matrix
n  = 1000
m = matrix(runif(n*10), ncol = 10)
m = m/rowSums(m)

# ensure that serial and parallel versions give the same result
r_res <- js_distance(m)
rcpp_res <- rcpp_js_distance(m)
rcpp_parallel_res <- rcpp_parallel_js_distance(m)
stopifnot(all(rcpp_res == rcpp_parallel_res))
stopifnot(all(rcpp_parallel_res - r_res < 1e-10)) ## precision differences

# compare performance
library(rbenchmark)
res <- benchmark(js_distance(m),
                 rcpp_js_distance(m),
                 rcpp_parallel_js_distance(m),
                 replications = 2,
                 order="relative")
res[,1:4]
*/

/**
 * The serial Rcpp version give a 30 to 40x speedup over straight R code.
 * On a machine with 4 cores (8 with hyperthreading) the parallel Rcpp version 
 * yields another 4x speedup comparison for a total of 140x improvement 
 * in performance over the original R version.
 */
 
 /**
 * If you interested in learning more about using RcppParallel see 
 * [https://github.com/RcppCore/RcppParallel](https://github.com/RcppCore/RcppParallel).
 */ 
