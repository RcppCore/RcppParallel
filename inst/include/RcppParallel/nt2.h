#ifndef RCPP_PARALLEL_NT2_H
#define RCPP_PARALLEL_NT2_H

// Bring in the headers that automatically include the most
// commonly used SIMD functions. We do this for a couple reasons:
//
//    1. Including each desired header 'by hand' can be tedious
//       for the user,
//
//    2. Certain headers depend on others in such a way that attempting
//       to include one without the other can lead to obscure compiler
//       errors.
//
// The downside is the increased compile time, but this is something that users
// have implicitly accepted given the heavy use of template meta-programming in
// Boost.SIMD and its dependent libraries.
#include <boost/simd/sdk/simd/algorithm.hpp>
#include <boost/simd/memory/memory.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/arithmetic/arithmetic.hpp>
#include <boost/simd/bitwise/bitwise.hpp>
#include <boost/simd/boolean/boolean.hpp>
#include <boost/simd/reduction/reduction.hpp>
#include <boost/simd/swar/swar.hpp>
#include <boost/simd/include/pack.hpp>

#include <nt2/arithmetic/arithmetic.hpp>
#include <nt2/bessel/bessel.hpp>
#include <nt2/bitwise/bitwise.hpp>
#include <nt2/boolean/boolean.hpp>
#include <nt2/combinatorial/combinatorial.hpp>
#include <nt2/complex/complex.hpp>
#include <nt2/constant/constant.hpp>
#include <nt2/elliptic/elliptic.hpp>
#include <nt2/euler/euler.hpp>
#include <nt2/exponential/exponential.hpp>
#include <nt2/fuzzy/fuzzy.hpp>
#include <nt2/hyperbolic/hyperbolic.hpp>
#include <nt2/ieee/ieee.hpp>
#include <nt2/integration/integration.hpp>
#include <nt2/interpol/interpol.hpp>
// #include <nt2/linalg/linalg.hpp>
#include <nt2/memory/memory.hpp>
#include <nt2/operator/operator.hpp>
#include <nt2/optimization/optimization.hpp>
// #include <nt2/polynom/polynom.hpp>
// #include <nt2/polynomials/polynomials.hpp>
#include <nt2/predicates/predicates.hpp>
#include <nt2/reduction/reduction.hpp>
#include <nt2/signal/signal.hpp>
#include <nt2/statistics/statistics.hpp>
#include <nt2/swar/swar.hpp>
#include <nt2/trigonometric/trigonometric.hpp>

// Auto-generated functors for use in 'transform()', 'accumulate()'
#include <RcppParallel/simd/ops.h>
#include <RcppParallel/simd/algorithm.h>

#endif /* RCPP_PARALLEL_NT2_H */
