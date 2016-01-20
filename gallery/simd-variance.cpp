// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

class VarianceTransformer : public SimdTransformer<double>
{
public:
   packed_type initialize(const value_type* begin, const value_type* end)
   {
      n_ = end - begin;
      mean_ = boost::simd::accumulate(begin, end, 0.0, boost::simd::functors::plus()) / n_;
      return packed_type(0);
   }
   
   void update(const packed_type& data, packed_type* pBuffer)
   {
      *pBuffer += sqr(data - mean_);
   }
   
   value_type reduce(const packed_type& data)
   {
      return sum(data) / (n_ - 1);
   }
   
private:
   double mean_;
   std::size_t n_;
};

// [[Rcpp::export]]
double simdVar(NumericVector data) {
   return simdTransformAndReduce(data.begin(), data.end(), VarianceTransformer());
}

/*** R
x <- rnorm(1E6)
var(x)
simdVar(x)
result <- microbenchmark::microbenchmark(var(x), simdVar(x))
print(result, unit = "relative")
*/