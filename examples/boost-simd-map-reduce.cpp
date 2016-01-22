// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

class SumOfSquaresReducer
{
public:
   
   explicit SumOfSquaresReducer(double mean)
      : mean_(mean)
   {}
   
   template <typename T>
   void map(const T& self, T* pBuffer)
   {
      *pBuffer += boost::simd::sqr(self - mean_);
   }
   
   template <typename T, typename U>
   void reduce(const T& data, U* pBuffer)
   {
      *pBuffer += boost::simd::sum(data);
   }
   
private:
   double mean_;
};

// [[Rcpp::export]]
double simdVar(NumericVector x)
{
   double total = simdReduce(x.begin(), x.end(), 0.0, simd_ops::plus());
   double n = x.size();
   double mean = total / n;
   
   double ssq = simdMapReduce(x.begin(), x.end(), 0.0, SumOfSquaresReducer(mean));
   
   return ssq / (n - 1);
}

/*** R
x <- rnorm(1024 * 10000)
var(x)
simdVar(x)
library(microbenchmark)
microbenchmark(var(x), simdVar(x))
*/
