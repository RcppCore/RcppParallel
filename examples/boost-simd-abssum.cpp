// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double simd_abssum(NumericVector x)
{
   using boost::simd::pack;
   using boost::simd::load;
   using boost::simd::aligned_load;
   
   typedef std::vector<double, boost::simd::allocator<double>> vector_type;
   typedef pack<double> packed_type;
   
   vector_type data(x.begin(), x.end());
   
   packed_type packed;
   double* it = &data[0];
   double* end = &data[0] + data.size();
   
   while (it != end)
   {
      packed_type loaded = load<packed_type>(it);
      packed = packed + boost::simd::abs(loaded);
      it += packed_type::static_size;
   }
   
   return sum(packed);
}

/*** R
n <- 1024 * 1000
x <- rnorm(n)

library(microbenchmark)
microbenchmark(
   R = sum(abs(x)),
   simd = simd_abssum(x)
)
*/
