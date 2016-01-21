/**
 * @title Using SIMD Instructions to Compute the Variance with RcppParallel
 * @author Kevin Ushey
 * @license GPL (>= 2)
 * @tags simd parallel
 * @summary Demonstrates how RcppParallel could be used to implement a SIMD-aware variance.
 */

// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

/**
 * This article illustrates how the 'simdMapReduce()'
 * function can be used to compute the variance for a vector
 * of numbers. First, let's look at the R code one might
 * write to compute the variance.
 */

/*** R
x <- rnorm(16)
sum((x - mean(x))^2) / (length(x) - 1)
*/

/**
 * We can decompose the operation into a few distinct steps:
 * 
 *    1. Compute the mean for our vector 'x',
 *    2. Compute the squared deviations from the mean,
 *    3. Sum the deviations about the mean,
 *    4. Divide the summation by the length minus one.
 * 
 * Naively, we could imagine writing a 'transform()' for
 * step 2, and an 'accumulate()' for step 3. However, this
 * is a bit inefficient as the transform would require
 * allocating a whole new vector, with the same length as
 * our initial vector. It'd be much better if we could
 * combine our map and reduction operations, as we could
 * then avoid that large allocation. The 'simdMapReduce()'
 * function provides an interface for doing just that, with
 * a SIMD pack providing the 'buffer' for the mapped
 * operations.
 * 
 * The 'simdMapReduce()' function expects a class providing
 * templated 'map()' and 'reduce()' functions. The 'map()'
 * operation represents the transformation we wish to make
 * on the input data (in this case, the square of the
 * deviation from the mean); while the 'reduce()' operation
 * represents how the transformed result should be combined
 * (in this case, as a summation of said deviations).
 * 
 * Let's write a class that encapsulates this 'sum of
 * squares' map-reduction operation.
 */

class SumOfSquaresMapReducer
{
public:
   
   // Since the 'map' operation requires knowledge of the mean,
   // we ensure our class must be constructed with a mean value.
   explicit SumOfSquaresMapReducer(double mean)
      : mean_(mean)
   {}
   
   // The 'map()' operation generates a squared deviation, 
   // and updates a buffer. By making this a template, 
   // specializations for SIMD packs, versus scalar values, 
   // can be generated as appropriate. We use the 
   // 'boost::simd::sqr()' function to compute the square.
   template <typename T>
   void map(const T& data, T* pBuffer)
   {
      *pBuffer += boost::simd::sqr(data - mean_);
   }
   
   // The 'reduce()' operation collapses the accumulated 
   // SIMD pack structure into a scalar value, and updates 
   // the buffer. In this case, we just need to add up the 
   // values in that pack, and add it to the buffer.
   template <typename T, typename U>
   void reduce(const T& data, U* pBuffer)
   {
      *pBuffer += boost::simd::sum(data);
   }
   
private:
   double mean_;
};

/**
 * Now that we have our 'SumOfSquares' class defined, we can
 * use it to compute the variance. We'll call our function
 * 'simdVar()', and export it using Rcpp attributes in the
 * usual way.
 */

// [[Rcpp::export]]
double simdVar(NumericVector data) {
   
   // Pull in the 'boost::simd' namespace for easier access
   // to the functions we need to use.
   using namespace boost;
   
   // First, compute the mean as we'll need that for
   // computation of the sum of squares.
   double total = simd::accumulate(data.begin(), data.end(), 0.0, simd::ops::plus());
   std::size_t n = data.size();
   double mean = total / n;
   
   // Construct our map-reducer with the generated mean.
   auto reducer = SumOfSquaresMapReducer(mean);
   
   // Use it to compute the sum of squares.
   double ssq = simdMapReduce(data.begin(), data.end(), 0.0, reducer);
   
   // Divide by 'n - 1', and we're done!
   return ssq / (n - 1);
}

/**
 * Let's confirm that this works as expected...
 */

/*** R
x <- as.numeric(1:10)
stopifnot(all.equal(var(x), simdVar(x)))
*/

/**
 * And let's benchmark, to see how performance compares.
 */

/*** R
library(microbenchmark)

small <- as.numeric(1:16)
stopifnot(all.equal(var(small), simdVar(small)))
microbenchmark(var(small), simdVar(small))

large <- rnorm(1E6)
stopifnot(all.equal(var(large), simdVar(large)))
microbenchmark(var(large), simdVar(large))
*/

/**
 * As we can see, taking advantage of our SIMD map-reducer
 * has improved the runtime quite drastically.
 */
