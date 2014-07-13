
#include <Rcpp.h>
using namespace Rcpp;

#include <iostream>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;


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


// [[Rcpp::export]]
void testMatrix(NumericMatrix x) {
   
   RMatrix<double> m(x);
    
   //NumericMatrixAccessor::Column column = m.column(3);
   
   for (RMatrix<double>::Column::Iterator it = m.column(3).begin();
        it != m.column(3).end(); ++it) {
      std::cout << *it << std::endl;  
   }
   
   
   //NumericMatrixAccessor::Row row = m.row(3);
   
   for (RMatrix<double>::Row::Iterator it = m.row(3).begin();
        it != m.row(3).end(); ++it) {
      std::cout << *it << std::endl;  
   }
   
   
}



/*** R


m = matrix(as.numeric(c(1:16)), nrow = 4, ncol = 4)
testMatrix(m)

#n  = 1000
#m = matrix(runif(n*10), ncol = 10)
#m = m/rowSums(m)
#js_distance(m) 
*/


