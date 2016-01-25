#ifndef RCPP_PARALLEL_SIMD_ALGORITHM_H
#define RCPP_PARALLEL_SIMD_ALGORITHM_H

namespace RcppParallel {

template<class T, class U, class UnOp>
U* simdTransform(T const* begin, T const* end, U* out, UnOp f)
{
   typedef boost::simd::pack<T> vT;
   typedef boost::simd::pack<U> vU;
   
   BOOST_MPL_ASSERT_MSG( vT::static_size == vU::static_size
                            , BOOST_SIMD_TRANSFORM_INPUT_OUTPUT_NOT_SAME_SIZE
                            , (T, U)
   );
   
   static const std::size_t N = vU::static_size;
   
   std::size_t shift = boost::simd::align_on(out, N * sizeof(U)) - out;
   T const* end2 = begin + std::min<size_t>(shift, end-begin);
   T const* end3 = end2 + (end - end2)/N*N;
   
   // prologue
   for(; begin!=end2; ++begin, ++out)
      *out = f(*begin);
   
   if(boost::simd::is_aligned(begin, N * sizeof(T)))
   {
      for(; begin!=end3; begin += N, out += N)
         boost::simd::aligned_store(f(boost::simd::aligned_load<vT>(begin)), out);
   }
   else
   {
      for(; begin!=end3; begin += N, out += N)
         boost::simd::aligned_store(f(boost::simd::load<vT>(begin)), out);
   }
   
   // epilogue
   for(; begin!=end; ++begin, ++out)
      *out = f(*begin);
   
   return out;
}

template<class T1, class T2, class U, class BinOp>
U* simdTransform(T1 const* begin1, T1 const* end, T2 const* begin2, U* out, BinOp f)
{
   typedef boost::simd::pack<T1> vT1;
   typedef boost::simd::pack<T2> vT2;
   typedef boost::simd::pack<U> vU;
   
   BOOST_MPL_ASSERT_MSG( vT1::static_size == vT2::static_size && vT1::static_size == vU::static_size
                            , BOOST_SIMD_TRANSFORM_INPUT_OUTPUT_NOT_SAME_SIZE
                            , (T1, T2, U)
   );
   
   static const std::size_t N = vU::static_size;
   
   std::size_t shift = boost::simd::align_on(out, N * sizeof(U)) - out;
   T1 const* end2 = begin1 + std::min<size_t>(shift, end-begin1);
   T1 const* end3 = end2 + (end - end2)/N*N;
   
   // prologue
   for(; begin1!=end2; ++begin1, ++begin2, ++out)
      *out = f(*begin1, *begin2);
   
   if(boost::simd::is_aligned(begin1, N * sizeof(T1)) && boost::simd::is_aligned(begin2, N * sizeof(T2)))
   {
      for(; begin1!=end3; begin1 += N, begin2 += N, out += N)
         boost::simd::aligned_store(f(boost::simd::aligned_load<vT1>(begin1), boost::simd::aligned_load<vT2>(begin2)), out);
   }
   else
   {
      for(; begin1!=end3; begin1 += N, begin2 += N, out += N)
         boost::simd::aligned_store(f(boost::simd::load<vT1>(begin1), boost::simd::load<vT2>(begin2)), out);
   }
   
   // epilogue
   for(; begin1!=end; ++begin1, ++begin2, ++out)
      *out = f(*begin1, *begin2);
   
   return out;
}

template<class T, class U, class F>
U simdReduce(T const* begin, T const* end, U init, F f)
{
   typedef boost::simd::pack<T> vT;
   typedef boost::simd::pack<U> vU;
   
   BOOST_MPL_ASSERT_MSG( vT::static_size == vU::static_size
                            , BOOST_SIMD_ACCUMULATE_INPUT_OUTPUT_NOT_SAME_SIZE
                            , (T, U)
   );
   
   static const std::size_t N = vT::static_size;
   T const* end2 = std::min( boost::simd::align_on(begin, N * sizeof(T)), end );
   T const* end3 = end2 + (end - end2)/N*N;
   
   vU cur = boost::simd::splat<vU>(init);
   
   // prologue
   for(; begin!=end2; ++begin)
      init = f(init, *begin);
   
   for(; begin!=end3; begin += N)
      cur = f(cur, boost::simd::aligned_load<vT>(begin));
   
   // reduce cur
   for(typename vU::const_iterator b = cur.begin(); b != cur.end(); ++b)
      init = f(init, *b);
   
   // epilogue
   for(; begin!=end; ++begin)
      init = f(init, *begin);
   
   return init;
}

template <typename T, typename F>
F simdFor(const T* it, const T* end, F&& f)
{
   typedef boost::simd::pack<T> vT;
   static const std::size_t N = vT::static_size;
   const T* aligned_begin = std::min(boost::simd::align_on(it, N * sizeof(T)), end);
   const T* aligned_end   = aligned_begin + (end - aligned_begin) / N * N;
   
   for (; it != aligned_begin; ++it)
      std::forward<F>(f)(*it);
   
   for (; it != aligned_end; it += N)
      std::forward<F>(f)(boost::simd::aligned_load<vT>(it));
   
   for (; it != end; ++it)
      std::forward<F>(f)(*it);
   
   return f;
}

template <typename T, typename U, typename F>
U simdReduce(const T* begin, const T* end, U init, F f)
{
   return boost::simd::accumulate(begin, end, init, f);
}

template <typename T, typename U, typename MapReducer>
U simdMapReduce(const T* it, const T* end, U init, MapReducer mapper)
{
   // We separate the range into three regions, to allow
   // for aligned loads of data (when possible), and scalar
   // reads otherwise.
   //
   // --------- | ------- | ---------
   // unaligned | aligned | unaligned
   //
   //           ^ ------------------- aligned_begin
   //                     ^---------- aligned_end
   
   typedef boost::simd::pack<T> vT; // SIMD vector of T
   typedef boost::simd::pack<U> vU; // SIMD vector of U
   
   static const std::size_t N = vT::static_size;
   const T* aligned_begin = std::min(boost::simd::align_on(it, N * sizeof(T)), end);
   const T* aligned_end   = aligned_begin + (end - aligned_begin) / N * N;
   
   // Buffer for the SIMD mapping operations
   vU buffer = boost::simd::splat<vU>(init);
   
   // Scalar operations for the initial unaligned region
   for (; it != aligned_begin; ++it)
      mapper.map(*it, &init);
   
   // Aligned, SIMD operations
   for (; it != aligned_end; it += N)
      mapper.map(boost::simd::aligned_load<vT>(it), &buffer);
   
   // Reduce the buffer, joining it into the scalar vale
   mapper.reduce(buffer, &init);
   
   // Leftover unaligned region
   for (; it != end; ++it)
      mapper.map(*it, &init);
   
   return init;
}

} // namespace RcppParallel

#endif /* RCPP_PARALLEL_SIMD_ALGORITHM_H */