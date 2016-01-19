/**
 * @title Using SIMD Instructions to Sum a Vector with RcppParallel
 * @author Kevin Ushey
 * @license GPL (>= 2)
 * @tags parallel
 * @summary Demonstrates how RcppParallel could be used to implement a SIMD-aware sum.
 */

/**
 * Newer releases of [RcppParallel](http://rcppcore.github.io/RcppParallel/) now
 * bundle the [Boost.SIMD](https://www.lri.fr/~falcou/pub/pact-2012.pdf)
 * library, providing a framework for ensuring that the algorithms you write
 * take advantage of the vectorized instructions offered by new CPUs. This
 * article illustrates how you might use `Boost.SIMD` to sum all of the elements
 * in a vector.
 * 
 * First, let's review how we might use `std::accumulate()` to sum a vector of numbers.
 * We explicitly pass in the `std::plus<double>()` functor, just to make it clear that
 * the `std::accumulate()` algorithm expects a binary functor when accumulating values.
 */

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double vectorSum(NumericVector x) {
   return std::accumulate(x.begin(), x.end(), 0.0, std::plus<double>());
}

/**
 * Now, let's rewrite this to take advantage of `Boost.SIMD`. There are
 * two main steps required to take advantage of `Boost.SIMD` at a high
 * level:
 * 
 *   1. Write a functor, with a templated call operator, with the implementation
 *      written in a '`Boost.SIMD`-aware' way;
 * 
 *   2. Provide the functor as an argument to `boost::simd::transform()` or
 *      `boost::simd::accumulate()`, as appropriate.
 * 
 * Let's follow these steps in implementing our SIMD sum.
 */

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

struct simd_plus {
   template <typename T>
   T operator()(const T& lhs, const T& rhs) {
      return lhs + rhs;
   }
};

// [[Rcpp::export]]
double vectorSumSimd(NumericVector x) {
   return boost::simd::accumulate(x.begin(), x.end(), 0.0, simd_plus());
}

/**
 * As you can see, it's quite simple to take advantage of `Boost.SIMD`.
 *
 * Behind the scenes of `boost::simd::accumulate()`, `Boost.SIMD` will
 * apply your templated functor to 'packs' of values when appropriate,
 * and scalar values when not. In other words, there are effectively
 * two kinds of template specializations being generated behind the scenes:
 * one with `T = double`, and one with `T = boost::simd::pack<double>`. The
 * use of the packed representation is what allows `Boost.SIMD` to ensure
 * vectorized instructions are used and generated. `Boost.SIMD` provides
 * a host of functions and operator overloads that ensure that optimized
 * instructions are used when possible over a packed object, while falling
 * back to 'default' operations for scalar values when not.
 *
 * Now, let's compare the performance of these two implementations.
 */

/*** R
library(microbenchmark)

# allocate a large vector
set.seed(123)
v <- rnorm(1E6)

# ensure they compute the same values
stopifnot(all.equal(vectorSum(v), vectorSumSimd(v)))

# compare performance
res <- microbenchmark(vectorSum(v), vectorSumSimd(v))
print(res)
*/

/**
 * Perhaps surprisingly, the `Boost.SIMD` solution is much faster -- the gains
 * are similar to what we might have seen when computing the sum in parallel.
 * However, we're still just using a single core; we're just taking advantage of
 * vectorized instructions provided by the CPU. In this particular case, on
 * Intel CPUs, `Boost.SIMD` will ensure that we are using the `addpd`
 * instruction, which is documented in the Intel Software Developer's Manual 
 * [[PDF](http://www.intel.com/Assets/en_US/PDF/manual/253666.pdf)].
 * 
 * Note that, for the naive serial sum, the compiler would likely generate 
 * similarly efficient code when the `-ffast-math` optimization flag is set.
 * By default, the compiler is somewhat 'pessimistic' about the set of 
 * optimizations it can perform around floating point arithmetic. This is 
 * because it must respect the [IEEE floating 
 * point](https://en.wikipedia.org/wiki/IEEE_floating_point) standard, and
 * this means respecting the fact that, for example, floating point
 * operations are not assocative:
 */

/*** R
((0.1 + 0.2) + 0.3) - (0.1 + (0.2 + 0.3))
*/

/**
 * Surprisingly, the above computation does not evaluate to zero!
 *
 * In practice, you're likely safe to take advantage of the `-ffast-math`
 * optimizations, or Boost.SIMD, in your own work. However, be sure to test and
 * verify!
 */
