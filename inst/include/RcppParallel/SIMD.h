#ifndef RCPP_PARALLEL_SIMD_H
#define RCPP_PARALLEL_SIMD_H

#include <boost/simd/sdk/simd/algorithm.hpp>

namespace RcppParallel {
namespace simd {

template <class T, class UnaryFunction>
T transform(const T& data, UnaryFunction f)
{
   T result(data.size());
   boost::simd::transform(data.begin(), data.end(), result.begin(), f);
   return result;
}

template <class T, class BinaryFunction>
T transform(const T& lhs, const T& rhs, BinaryFunction f)
{
   T result(lhs.size());
   boost::simd::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), f);
   return result;
}

template <class T, class U, class F>
U accumulate(const T& data, U init, F f)
{
   return boost::simd::accumulate(data.begin(), data.end(), init, f);
}

} // namespace simd
} // namespace RcppParallel

#endif /* RCPP_PARALLEL_SIMD_H */