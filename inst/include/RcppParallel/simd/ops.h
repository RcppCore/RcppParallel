#ifndef RCPP_PARALLEL_SIMD_OPS_H
#define RCPP_PARALLEL_SIMD_OPS_H

// Auto-generated functors for functions provided by Boost.SIMD.
// See 'gen/simd-ops.R' for implementation.

namespace boost {
namespace simd {
namespace ops {

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


} // namespace ops
} // namespace simd
} // namespace boost

#endif /* RCPP_PARALLEL_SIMD_OPS_H */
