#ifndef RCPP_PARALLEL_SIMD_ADAPTORS_H
#define RCPP_PARALLEL_SIMD_ADAPTORS_H

namespace boost {
namespace simd {

template <typename T>
auto begin(T& data) -> decltype(&data[0])
{
   return &data[0];
}

template <typename T>
auto begin(const T& data) -> decltype(&data[0])
{
   return &data[0];
}

template <typename T>
auto end(T& data) -> decltype(&data[0])
{
   return &data[0] + data.size();
}

template <typename T>
auto end(const T& data) -> decltype(&data[0])
{
   return &data[0] + data.size();
}

} // namespace simd
} // namespace boost

#endif /* RCPP_PARALLEL_SIMD_ADAPTORS_H */
