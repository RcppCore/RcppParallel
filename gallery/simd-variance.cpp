/**
 * @title Using SIMD Instructions to Compute the Variance with RcppParallel
 * @author Kevin Ushey
 * @license GPL (>= 2)
 * @tags simd parallel
 * @summary Demonstrates how RcppParallel could be used compute
 *     the variance, using SIMD instructions.
 */

// [[Rcpp::depends(RcppParallel)]]
#define RCPP_PARALLEL_USE_SIMD
#include <RcppParallel.h>
using namespace RcppParallel;

#include <Rcpp.h>
using namespace Rcpp;

/**
 * This article illustrates how we might take advantage of
 * `Boost.SIMD` in computing the variance for a vector of
 * numers. First, let's look at the R code one might write
 * to compute the variance.
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
 * our initial vector. When neither 'accumulate()' nor
 * 'transform()' seem to be a good fit, we can fall back to
 * 'for_each()'. We can pass a stateful functor to handle
 * accumulation of the transformed results.
 * 
 * Let's write a class that encapsulates this 'sum of
 * squares' operation.
 */

class SumOfSquaresAccumulator
{
public:
   
   // Since the 'transform()' operation requires knowledge
   // of the mean, we ensure our class must be constructed
   // with a mean value. We will also hold the final result
   // within the 'result_' variable.
   explicit SumOfSquaresAccumulator(double mean)
      : mean_(mean), result_(0.0), pack_(0.0)
   {}
   
   // We need to provide two call operators: one to handle
   // SIMD packs, and one to handle scalar values. We do this
   // as we want to accumulate SIMD results in a SIMD data
   // structure, and scalar results in a scalar data object.
   //
   // We _could_ just accumulate all our results in a single
   // 'double', but this is actually less efficient -- it
   // pays to use packed structures when possible.
   void operator()(double data)
   {
      double diff = data - mean_;
      result_ += diff * diff;
   }
   
   void operator()(const boost::simd::pack<double>& data)
   {
      pack_ += boost::simd::sqr(data - mean_);
   }
   
   // Provide a 'conversion to double' operator -- this lets
   // us easily extract the resulting value after computation.
   // This is also where we combine our scalar, and packed,
   // representations of the data.
   operator double() const {
      return result_ + boost::simd::sum(pack_);
   }
   
private:
   double mean_;
   double result_;
   boost::simd::pack<double> pack_;
};

/**
 * Now that we have our accumulator class defined, we can
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
   double total = simd::accumulate(data.begin(),
                                   data.end(),
                                   0.0,
                                   simd::ops::plus());
   
   std::size_t n = data.size();
   double mean = total / n;
   
   // Use our accumulator to compute the sum of squares.
   double ssq = simd::for_each(data.begin(),
                               data.end(),
                               SumOfSquaresAccumulator(mean));
   
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
 * As we can see, taking advantage of SIMD instructions
 * has improved the runtime quite drastically.
 */
