#ifndef __RCPP_PARALLEL_TBB__
#define __RCPP_PARALLEL_TBB__

#include "Common.h"

#include <tbb/tbb.h>
#include <tbb/scalable_allocator.h>

namespace RcppParallel {

namespace {

struct TBBWorker
{
   explicit TBBWorker(Worker& worker) : worker_(worker) {}
   
   void operator()(const tbb::blocked_range<size_t>& r) const {
      worker_(r.begin(), r.end());
   }

private:
   Worker& worker_;
};

template <typename Reducer>
struct TBBReducer 
{  
   explicit TBBReducer(Reducer& reducer) 
      : pSplitReducer_(NULL), reducer_(reducer)
   {
   }
   
   TBBReducer(TBBReducer& tbbReducer, tbb::split)
      : pSplitReducer_(new Reducer(tbbReducer.reducer_, RcppParallel::Split())),
        reducer_(*pSplitReducer_)
   {
   }
   
   virtual ~TBBReducer() { delete pSplitReducer_; }

   void operator()(const tbb::blocked_range<size_t>& r) {
      reducer_(r.begin(), r.end());
   }
   
   void join(const TBBReducer& tbbReducer) { 
      reducer_.join(tbbReducer.reducer_); 
   }
   
private:
   Reducer* pSplitReducer_;
   Reducer& reducer_;
};
   
} // anonymous namespace


inline void tbbParallelFor(std::size_t begin, std::size_t end, 
                           Worker& worker, std::size_t grainSize = 1) {
   
   TBBWorker tbbWorker(worker);
   
   tbb::parallel_for(tbb::blocked_range<size_t>(begin, end, grainSize), 
                     tbbWorker);
}

template <typename Reducer>
inline void tbbParallelReduce(std::size_t begin, std::size_t end, 
                              Reducer& reducer, std::size_t grainSize = 1) {
   
   TBBReducer<Reducer> tbbReducer(reducer);
   
   tbb::parallel_reduce(tbb::blocked_range<size_t>(begin, end, grainSize), 
                        tbbReducer);
}

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_TBB__
