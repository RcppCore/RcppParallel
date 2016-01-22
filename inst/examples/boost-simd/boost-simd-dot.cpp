// Demonstrates how Boost.SIMD could be used to compute the dot product
// of two vectors, using a lower-level iteration over packs.
//
// See: http://nt2.metascale.fr/doc/html/tutorials/processing_data_the_simd_way.html

// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

template <typename Value>
Value simd_dot_impl(Value* first1, Value* last1, Value* first2)
{
   using boost::simd::sum;
   using boost::simd::pack;
   
   typedef pack<Value> packed_type;
   packed_type tmp;
   
   // Let's consider that (last1-first1) is divisible by the size of the pack.
   while (first1 != last1)
   {
      // Load current values from the datasets
      packed_type x1 = boost::simd::load<packed_type>(first1);
      packed_type x2 = boost::simd::load<packed_type>(first2);
      
      // Computation
      tmp = tmp + x1 * x2;
      
      // Advance to the next SIMD vector
      first1 += packed_type::static_size;
      first2 += packed_type::static_size;
   }
   
   return sum(tmp);
}

// [[Rcpp::export]]
double simd_dot(NumericVector lhs, NumericVector rhs)
{
   return simd_dot_impl(
      REAL(lhs),
      REAL(lhs) + lhs.size(),
      REAL(rhs)
   );
}

/*** R
set.seed(123)
lhs <- rnorm(1024 * 1000)
rhs <- rnorm(1024 * 1000)
stopifnot(all.equal(simd_dot(lhs, rhs), sum(lhs * rhs)))

library(microbenchmark)
microbenchmark(
   simd = simd_dot(lhs, rhs),
   R = sum(lhs * rhs)
)
*/
