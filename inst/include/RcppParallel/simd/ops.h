#ifndef RCPP_PARALLEL_SIMD_OPS_H
#define RCPP_PARALLEL_SIMD_OPS_H

// Auto-generated functors for functions provided by Boost.SIMD.
// See 'gen/simd-ops.R' for implementation.

namespace RcppParallel {
namespace simd_ops {

struct sum {
template <typename T>
inline T operator()(const T& data) {
    return sum(data);
}
};

struct plus {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs + rhs;
}
};

struct minus {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs - rhs;
}
};

struct times {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs * rhs;
}
};

struct divide {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs / rhs;
}
};


} // namespace simd_ops
} // namespace RcppParallel

#endif /* RCPP_PARALLEL_SIMD_OPS_H */
