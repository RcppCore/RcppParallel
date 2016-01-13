// [[Rcpp::depends(RcppParallel)]]
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
   using boost::simd::load;
   
   typedef pack<Value> type;
   type tmp;
   
   // Let's consider that (last1-first1) is divisible by the size of the pack.
   while (first1 != last1)
   {
      // Load current values from the datasets
      pack<Value> x1 = load<type>(first1);
      pack<Value> x2 = load<type>(first2);
      
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
   double result = simd_dot(
      &a[0],
      &a[0] + a.size(),
      &b[0]
   );
   
   return result;
}

/*** R
lhs <- rnorm(10)
rhs <- rnorm(10)
result <- dot(lhs, rhs)
all.equal(result, sum(lhs * rhs))

library(microbenchmark)
lhs <- rnorm(1024 * 1000)
rhs <- rnorm(1024 * 1000)
microbenchmark(
   simd = dot(lhs, rhs),
   R = sum(lhs * rhs)
)
*/
