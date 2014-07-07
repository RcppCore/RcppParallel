
#ifndef __RCPP_PARALLEL__
#define __RCPP_PARALLEL__

// TinyThread implementation
#include "RcppParallel/TinyThread.h"

// TBB implementation (enabled by default except on Windows)
#ifndef RCPP_PARALLEL_USE_TBB
#ifdef _WIN32
  #define RCPP_PARALLEL_USE_TBB 0
#else
  #define RCPP_PARALLEL_USE_TBB 1
  #include "RcppParallel/TBB.h"
#endif
#endif

namespace RcppParallel {

inline void parallelFor(std::size_t begin, std::size_t end, Worker& worker) {
#if RCPP_PARALLEL_USE_TBB
   tbbParallelFor(begin, end, worker);
#else
   ttParallelFor(begin, end, worker);
#endif

}

template <typename Reducer>
inline void parallelReduce(std::size_t begin, std::size_t end, Reducer& reducer) {
#if RCPP_PARALLEL_USE_TBB
   tbbParallelReduce(begin, end, reducer);
#else
   ttParallelReduce(begin, end, reducer);
#endif
}

} // namespace RcppParallel

#endif // __RCPP_PARALLEL__
