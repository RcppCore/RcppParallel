// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD 1
#include <RcppParallel.h>
#include <Rcpp.h>
using namespace Rcpp;

// http://nt2.metascale.fr/doc/html/tutorials/processing_data_the_simd_way.html
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/multiplies.hpp>

template <typename Value>
Value simd_dot(Value* first1, Value* last1, Value* first2)
{
   using boost::simd::sum;
   using boost::simd::pack;
   
   typedef pack<Value> type;
   type tmp;
   
   // Let's consider that (last1-first1) is divisible by the size of the pack.
   while (first1 != last1)
   {
      // Load current values from the datasets
      pack<Value> x1 = boost::simd::aligned_load<Value>(first1);
      pack<Value> x2 = boost::simd::aligned_load<Value>(first2);
      
      // Computation
      tmp = tmp + x1 * x2;
      
      // Advance to the next SIMD vector
      first1 += type::static_size;
      first2 += type::static_size;
   }
   
   return sum(tmp);
}

// [[Rcpp::export]]
double dot(NumericVector lhs, NumericVector rhs)
{
   // construct simd vectors
   typedef std::vector< double, boost::simd::allocator<double> > vector_t;
   vector_t a(lhs.begin(), lhs.end());
   vector_t b(rhs.begin(), rhs.end());
   
   // call dot function
   double result = simd_dot(&a[0], &a[0] + a.size(), &b[0]);
   
   return result;
}

/*** R
n <- 1024
lhs <- rnorm(n)
rhs <- rnorm(n)
result <- dot(lhs, rhs)
all.equal(result, sum(lhs * rhs))

library(microbenchmark)
lhs <- rnorm(n * 1000)
rhs <- rnorm(n * 1000)
microbenchmark(
   simd = dot(lhs, rhs),
   R = sum(lhs * rhs)
)
*/
