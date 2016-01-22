// Investigate a couple methods for computing the variance.

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
double simdVarTwoPass(NumericVector x)
{
   double total = simdReduce(x.begin(), x.end(), 0.0, simd_ops::plus());
   double n = x.size();
   double mean = total / n;
   
   double ssq = simdMapReduce(x.begin(), x.end(), 0.0, SumOfSquaresReducer(mean));
   
   return ssq / (n - 1);
}

// A one-pass method for computation of the variance.
// Numerically unstable, relative to other methods.
class SumOfSquares
{
public:
   
   SumOfSquares(double shift, std::size_t n)
      : lhs_(0.0), pLhs_(0.0),
        rhs_(0.0), pRhs_(0.0),
        shift_(shift), n_(n)
   {}
   
   void operator()(double data) {
      lhs_ += (data - shift_) * (data - shift_);
      rhs_ += (data - shift_);
   }
   
   void operator()(const boost::simd::pack<double>& data) {
      pLhs_ += (data - shift_) * (data - shift_);
      pRhs_ += (data - shift_);
   }
   
   operator double() const {
      double lhs = lhs_ + boost::simd::sum(pLhs_);
      double rhs = rhs_ + boost::simd::sum(pRhs_);
      return lhs - (rhs * rhs) / n_;
   }
   
private:
   double lhs_;
   boost::simd::pack<double> pLhs_;
   
   double rhs_;
   boost::simd::pack<double> pRhs_;
   
   double shift_;
   std::size_t n_;
};

// [[Rcpp::export]]
double simdVarOnePass(NumericVector x, double shift = 0.0)
{
   std::size_t n = x.size();
   double ssq = simdFor(x.begin(), x.end(), SumOfSquares(shift, n));
   return ssq / (n - 1);
}

/*** R
x <- rnorm(1E7, mean = 1E6)
simdVarTwoPass(x)
simdVarOnePass(x) # ouch!
simdVarOnePass(x, 1E6)
microbenchmark(
   simdVarOnePass(x),
   simdVarOnePass(x, 1E6),
   simdVarTwoPass(x)
)
*/