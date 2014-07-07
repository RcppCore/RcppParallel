#ifndef __RCPP_PARALLEL_TBB__
#define __RCPP_PARALLEL_TBB__

#include "Common.h"

#include <tbb/tbb.h>

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
    : pReducer_(&reducer), wasSplit_(false)
   {
   }
   
   virtual ~TBBReducer() {
      try
      {
         if (wasSplit_)
            delete pReducer_;
      }
      catch(...)
      {
      }
   }
   
   void operator()(const tbb::blocked_range<size_t>& r) {
      pReducer_->operator()(r.begin(), r.end());
   }
   
   TBBReducer(TBBReducer& reducer, tbb::split) 
      : pReducer_(new Reducer()), wasSplit_(true) 
   {  
      pReducer_->split(*reducer.pReducer_);   
   }

   void join(const TBBReducer& reducer) { 
      pReducer_->join(*reducer.pReducer_); 
   }
   
private:
   Reducer* pReducer_;
   bool wasSplit_;
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
