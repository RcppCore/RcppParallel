
#ifndef __RCPP_PARALLEL__
#define __RCPP_PARALLEL__

// TinyThread implementation
#include "RcppParallel/TinyThread.h"

// Use TBB only where it's known to compile and work correctly
// (NOTE: Windows TBB is temporarily opt-in for packages for 
// compatibility with CRAN packages not previously configured
// to link to TBB in Makevars.win)
#ifndef RCPP_PARALLEL_USE_TBB
# if defined(__APPLE__) || defined(__gnu_linux__) || (defined(__sun) && defined(__SVR4) && !defined(__sparc))
#  define RCPP_PARALLEL_USE_TBB 1
# else
#  define RCPP_PARALLEL_USE_TBB 0
# endif
#endif

#if RCPP_PARALLEL_USE_TBB
# include "RcppParallel/TBB.h"
#endif

#include "RcppParallel/Backend.h"

#include "RcppParallel/RVector.h"
#include "RcppParallel/RMatrix.h"

namespace RcppParallel {

inline void parallelFor(std::size_t begin,
                        std::size_t end, 
                        Worker& worker,
                        std::size_t grainSize = 1,
                        int numThreads = -1)
{
   grainSize = resolveValue("RCPP_PARALLEL_GRAIN_SIZE", grainSize, 1u);
   numThreads = resolveValue("RCPP_PARALLEL_NUM_THREADS", numThreads, -1);
   
#if RCPP_PARALLEL_USE_TBB
   if (internal::backend() == internal::BACKEND_TBB)
      tbbParallelFor(begin, end, worker, grainSize, numThreads);
   else
      ttParallelFor(begin, end, worker, grainSize);
#else
   ttParallelFor(begin, end, worker, grainSize);
#endif
}

template <typename Reducer>
inline void parallelReduce(std::size_t begin,
                           std::size_t end, 
                           Reducer& reducer,
                           std::size_t grainSize = 1,
                           int numThreads = -1)
{
   grainSize = resolveValue("RCPP_PARALLEL_GRAIN_SIZE", grainSize, 1);
   numThreads = resolveValue("RCPP_PARALLEL_NUM_THREADS", numThreads, -1);
   
#if RCPP_PARALLEL_USE_TBB
   if (internal::backend() == internal::BACKEND_TBB)
      tbbParallelReduce(begin, end, reducer, grainSize, numThreads);
   else
      ttParallelReduce(begin, end, reducer, grainSize);
#else
   ttParallelReduce(begin, end, reducer, grainSize);
#endif
}

} // end namespace RcppParallel

#endif // __RCPP_PARALLEL__
