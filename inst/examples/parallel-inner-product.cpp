#include <Rcpp.h>
using namespace Rcpp;

#include <algorithm>

// [[Rcpp::export]]
double innerProduct(NumericVector x, NumericVector y) {
   return std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
}


// [[Rcpp::depends(RcppParallel)]]
#include <tbb/tbb.h>

struct InnerProductBody {
   
   // source vectors
   double * const x;
   double * const y;
   
   // sum that I have accumulated
   double product;
   
   // standard and splitting constructor  
   InnerProductBody(double * const x, double * const y) 
      : x(x), y(y), product(0) {}
   InnerProductBody(InnerProductBody& body, tbb::split) 
      : x(body.x), y(body.y), product(0) {}
   
   // accumulate just the element of the range I've been asked to
   void operator()(const tbb::blocked_range<size_t>& r) {
      product += std::inner_product(x + r.begin(), 
                                    x + r.end(), 
                                    y + r.begin(), 0.0);
   }
   
   // join my inner product with another one
   void join(InnerProductBody& rhs) { product += rhs.product; }
};

// [[Rcpp::export]]
double parallelInnerProduct(NumericVector x, NumericVector y) {
   
   // declare the InnerProductBody instance that takes a pointer to the vector data
   InnerProductBody innerProductBody(x.begin(), y.begin());
   
   // call parallel_reduce to start the work
   tbb::parallel_reduce(tbb::blocked_range<size_t>(0, x.length()), 
                        innerProductBody);
   
   // return the computed product
   return innerProductBody.product;
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


