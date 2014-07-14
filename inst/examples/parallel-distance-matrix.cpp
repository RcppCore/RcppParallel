
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

#include <cmath>

// [[Rcpp::export]]
double kl_divergence(NumericVector vec1, NumericVector vec2) {
  if(vec1.size() != vec2.size()) {
      throw std::invalid_argument("Two vectors are not of the same length!");
  }  
  double rval = 0;
  for (int i = 0; i < vec1.size(); i++) {
      double r = 0;
      if (vec1[i] > 0 && vec2[i] > 0) {
        r = log(vec1[i]/vec2[i]) * vec1[i];
      }
      rval += r;
  }
  return rval;  
}

// [[Rcpp::export]]
NumericMatrix js_distance(NumericMatrix mat) {
  // allocate the matrix we will return
  NumericMatrix rmat(mat.nrow(), mat.nrow());

  for (int i = 0; i < rmat.nrow(); i++) {
    for (int j = 0; j < i; j++) {
      NumericVector avg = (mat(i,_) + mat(j,_))/2;
      double d1 = kl_divergence(mat(i,_), avg);
      double d2 = kl_divergence(mat(j,_), avg);
      rmat(i,j) = sqrt(.5 * (d1 + d2));
    }
  }
  return rmat;
}

struct JsDistance : public Worker {
   
   RMatrix<double> input;
   RMatrix<double> output;
   
   JsDistance(NumericMatrix input, NumericMatrix output)
      : input(input), output(output) {}
   
   void operator()(std::size_t begin, std::size_t end) {
      
      for (int i = begin; i < end; i++) {
         
         for (int j = 0; j < i; j++) {
         
            RMatrix<double>::Row row1 = input.row(i);
            RMatrix<double>::Row row2 = input.row(j);
            
            std::vector<double> avg(row1.length());
            std::transform(row1.begin(), row1.end(), row2.begin(),
                           avg.begin(), average);
              
            double d1 = divergence(row1, avg);
            double d2 = divergence(row2, avg);
               
            output(i,j) = sqrt(.5 * (d1 + d2));
         }
      }
   }
   
   double divergence(RMatrix<double>::Row row, const std::vector<double>& avg) {
      double rval = 0;
      for (int i = 0; i < row.length(); i++) {
         double r = 0;
         if (row[i] > 0 && avg[i] > 0)
            r = log(row[i]/avg[i]) * row[i];
         rval += r;
      }
      return rval;  
   }
   
   static double average(double val1, double val2) {
      return (val1 + val2) / 2;
   }
};


// [[Rcpp::export]]
NumericMatrix parallel_js_distance(NumericMatrix mat) {
  
   // allocate the matrix we will return
   NumericMatrix rmat(mat.nrow(), mat.nrow());

   // create the worker
   JsDistance jsDistance(mat, rmat);
   
   jsDistance(0, mat.nrow());
   
   // call it in parallel
   //parallelFor(0, mat.nrow(), jsDistance);

   return rmat;
}


/*** R

n  = 1000
m = matrix(runif(n*10), ncol = 10)
m = m/rowSums(m)
mt = t(m)
all.equal(js_distance(m), parallel_js_distance(m)) 

library(rbenchmark)
res <- benchmark(js_distance(m),
                 parallel_js_distance(m),
                 replications = 2,
                 order="relative")
res[,1:4]
*/


