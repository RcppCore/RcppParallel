#ifndef RCPP_PARALLEL_SIMD_FOR_EACH_H
#define RCPP_PARALLEL_SIMD_FOR_EACH_H

namespace boost {
namespace simd {

template <typename T, typename F>
F for_each(const T* it, const T* end, F f)
{
   typedef boost::simd::pack<T> vT;
   static const std::size_t N = vT::static_size;
   const T* aligned_begin = std::min(boost::simd::align_on(it, N * sizeof(T)), end);
   const T* aligned_end   = aligned_begin + (end - aligned_begin) / N * N;
   
   for (; it != aligned_begin; ++it)
      f(*it);
   
   for (; it != aligned_end; it += N)
      f(boost::simd::aligned_load<vT>(it));
   
   for (; it != end; ++it)
      f(*it);
   
   return f;
}

} // namespace simd
} // namespace boost

#endif /* RCPP_PARALLEL_SIMD_FOR_EACH_H */