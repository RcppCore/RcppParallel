/**
 *
 * This file contains example code showcasing how RcppParallel
 * can be used. In this file, we define and export a function called
 * 'parallelVectorSum()', which computes the sum of a numeric vector
 * in parallel.
 *
 * Please see https://rcppcore.github.io/RcppParallel/ for more
 * details on how to use RcppParallel in an R package, and the
 * Rcpp gallery at http://gallery.rcpp.org/ for more examples.
 *
 */

// [[Rcpp::depends(RcppParallel)]]
#include <Rcpp.h>
#include <RcppParallel.h>

using namespace Rcpp;
using namespace RcppParallel;

struct Sum : public Worker
{
   // source vector
   const RVector<double> input;

   // accumulated value
   double value;

   // constructors
   Sum(const NumericVector input) : input(input), value(0) {}
   Sum(const Sum& sum, Split) : input(sum.input), value(0) {}

   // accumulate just the element of the range I've been asked to
   void operator()(std::size_t begin, std::size_t end) {
      value += std::accumulate(input.begin() + begin, input.begin() + end, 0.0);
   }

   // join my value with that of another Sum
   void join(const Sum& rhs) {
      value += rhs.value;
   }
};

// [[Rcpp::export]]
double parallelVectorSum(NumericVector x) {

   // declare the SumBody instance
   Sum sum(x);

   // call parallel_reduce to start the work
   parallelReduce(0, x.length(), sum);

   // return the computed sum
   return sum.value;
}
