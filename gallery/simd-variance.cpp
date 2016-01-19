// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

/**
 * Let's use `Boost.SIMD` to compute the variance for a vector of numbers.
 * In contrast to the gallery article [implementing the sum](<TODO!!>),
 * we'll take advantage of some of the lower-level facilities provided
 * for interacting with packs of values.
 * 
 * The imple
 */

class simd_ssq
{
public:
   explicit simd_ssq(double avg) : avg_(avg) {}
   
   template <typename T>
   T operator()(const T& t) {
      return boost::simd::sqr(t - avg_);
   }
   
private:
   double avg_;
};

struct simd_plus
{
   template <typename T>
   T operator()(const T& lhs, const T& rhs) {
      return lhs + rhs;
   }
};

// [[Rcpp::export]]
double simdVar(NumericVector data) {
   
   // Bring in the Boost.SIMD components we need
   using boost::simd::pack;
   using boost::simd::load;
   typedef pack<double> packed_type;
   
   // Compute the mean of our dataset
   std::size_t n = data.size();
   double total = boost::simd::accumulate(data.begin(), data.end(), 0.0, simd_plus());
   double avg = total / n;
   
   // Create a functor that can be used to generate the sum of squares
   // for our above mean
   simd_ssq functor(avg);
   
   // Generate a SIMD pack to hold intermediate
   // values of our computation (ensure it is zero-initialized)
   packed_type accumulated(0);
   
   // Get 'raw' iterators to the underlying data
   double* it = REAL(data);
   double* end = REAL(data) + n;
   
   // Loop over chunks of our data, and compute the sum of squares
   while (it != end)
   {
      // Load the data
      packed_type loaded = load<packed_type>(it);
      
      // Compute the sum of squares
      accumulated += functor(loaded);
      
      // Advance our iterator to the next 'chunk' of data
      it += packed_type::static_size;
   }
   
   // Finish off by summing the accumulated values and dividing
   // by (n - 1)
   return sum(accumulated) / (n - 1);
   
}

/*** R
x <- rnorm(1E6)
var(x)
simdVar(x)
microbenchmark::microbenchmark(var(x), simdVar(x))
*/