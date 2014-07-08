#include <Rcpp.h>
using namespace Rcpp;

#include <algorithm>

// [[Rcpp::export]]
double innerProduct(NumericVector x, NumericVector y) {
   return std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
}

// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_TBB 0
#include <RcppParallel.h>

struct InnerProduct : public RcppParallel::Worker
{   
   // source vectors
   double * x;
   double * y;
   
   // product that I have accumulated
   double product;
   
   // constructors
   InnerProduct(double * const x, double * const y) : x(x), y(y), product(0) {}
   InnerProduct(InnerProduct& innerProduct, RcppParallel::Split) 
      : x(innerProduct.x), y(innerProduct.y), product(0) {}
   
   // process just the elements of the range I've been asked to
   void operator()(std::size_t begin, std::size_t end) {
      product += std::inner_product(x + begin, x + end, y + begin, 0.0);
   }
   
   // join my value with that of another InnerProduct
   void join(const InnerProduct& rhs) { 
     product += rhs.product; 
   }
};

// [[Rcpp::export]]
double parallelInnerProduct(NumericVector x, NumericVector y) {
   
   // declare the InnerProduct instance that takes a pointer to the vector data
   InnerProduct innerProduct(x.begin(), y.begin());
   
   // call paralleReduce to start the work
   RcppParallel::parallelReduce(0, x.length(), innerProduct);
   
   // return the computed product
   return innerProduct.product;
}

/*** R
 
x <- runif(1000000)
y <- runif(1000000)

library(rbenchmark)
res <- benchmark(sum(x*y),
                 innerProduct(x, y),
                 parallelInnerProduct(x, y),
                 order="relative")
res[,1:4]
*/


