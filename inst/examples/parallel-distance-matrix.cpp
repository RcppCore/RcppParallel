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

// helper function for taking the average of two numbers
inline double average(double val1, double val2) {
   return (val1 + val2) / 2;
}

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
      
      // accululate if appropirate
      if (d1 > 0 && d2 > 0)
         rval += std::log(d1 / d2) * d1;
   }
  
   return rval;  
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
 * - Other than organzing the code as a function object and using `RMatrix`, 
 * the parallel code is almost identical to the serial code. The main
 * difference is that the outer loop starts with the `begin` index passed
 * to the worker function rather than 0.
 * 
 * Here is the definition of the `JsDistance` function object:
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
 * Comparing the results on a MacBook Pro with 4 cores (8 with hyperthreading) 
 * we see a roughly 5x performance gain:
 */

/*** R

# create a matrix
n  = 1000
m = matrix(runif(n*10), ncol = 10)
m = m/rowSums(m)

# ensure that serial and parallel versions give the same result
all.equal(rcpp_js_distance(m), rcpp_parallel_js_distance(m)) 

# compare performance
library(rbenchmark)
res <- benchmark(rcpp_js_distance(m),
                 rcpp_parallel_js_distance(m),
                 replications = 10,
                 order="relative")
res[,1:4]
*/


