#ifndef __RCPP_PARALLEL_TBB__
#define __RCPP_PARALLEL_TBB__

#include "Common.h"

#ifndef TBB_PREVIEW_GLOBAL_CONTROL
# define TBB_PREVIEW_GLOBAL_CONTROL 1
#endif

#include <tbb/tbb.h>
#include <tbb/global_control.h>
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

class TBBParallelForExecutor
{
public:
   
   TBBParallelForExecutor(Worker& worker,
                          std::size_t begin,
                          std::size_t end,
                          std::size_t grainSize)
      : worker_(worker),
        begin_(begin),
        end_(end),
        grainSize_(grainSize)
   {
   }
   
   void operator()() const
   {
      TBBWorker tbbWorker(worker_);
      tbb::parallel_for(
         tbb::blocked_range<std::size_t>(begin_, end_, grainSize_),
         tbbWorker
      );
   }
   
private:
   Worker& worker_;
   std::size_t begin_;
   std::size_t end_;
   std::size_t grainSize_;
};

template <typename Reducer>
class TBBParallelReduceExecutor
{
public:
   
   TBBParallelReduceExecutor(Reducer& reducer,
                             std::size_t begin,
                             std::size_t end,
                             std::size_t grainSize)
      : reducer_(reducer),
        begin_(begin),
        end_(end),
        grainSize_(grainSize)
   {
   }
   
   void operator()() const
   {
      TBBReducer<Reducer> tbbReducer(reducer_);
      tbb::parallel_reduce(
         tbb::blocked_range<std::size_t>(begin_, end_, grainSize_),
         tbbReducer
      );
   }
   
private:
   Reducer& reducer_;
   std::size_t begin_;
   std::size_t end_;
   std::size_t grainSize_;
};

class TBBArenaParallelForExecutor
{
public:
   
   TBBArenaParallelForExecutor(tbb::task_group& group,
                               Worker& worker,
                               std::size_t begin,
                               std::size_t end,
                               std::size_t grainSize)
      : group_(group),
        worker_(worker),
        begin_(begin),
        end_(end),
        grainSize_(grainSize)
   {
   }
   
   void operator()() const
   {
      TBBParallelForExecutor executor(worker_, begin_, end_, grainSize_);
      group_.run_and_wait(executor);
   }
   
private:
   
   tbb::task_group& group_;
   Worker& worker_;
   std::size_t begin_;
   std::size_t end_;
   std::size_t grainSize_;
};

template <typename Reducer>
class TBBArenaParallelReduceExecutor
{
public:
   
   TBBArenaParallelReduceExecutor(tbb::task_group& group,
                                  Reducer& reducer,
                                  std::size_t begin,
                                  std::size_t end,
                                  std::size_t grainSize)
      : group_(group),
        reducer_(reducer),
        begin_(begin),
        end_(end),
        grainSize_(grainSize)
   {
   }
   
   void operator()() const
   {
      TBBParallelReduceExecutor<Reducer> executor(reducer_, begin_, end_, grainSize_);
      group_.run_and_wait(executor);
   }
   
private:
   
   tbb::task_group& group_;
   Reducer& reducer_;
   std::size_t begin_;
   std::size_t end_;
   std::size_t grainSize_;
};

class ThreadStackSizeControl
{
public:
   
   ThreadStackSizeControl()
      : control_(nullptr)
   {
      int stackSize = resolveValue("RCPP_PARALLEL_STACK_SIZE", 0, 0);
      if (stackSize > 0)
      {
         control_ = new tbb::global_control(
            tbb::global_control::thread_stack_size,
            stackSize
         );
      }
   }
   
   ~ThreadStackSizeControl()
   {
      if (control_ != nullptr)
      {
         delete control_;
         control_ = nullptr;
      }
   }

private:
   
   // COPYING: not copyable
   ThreadStackSizeControl(const ThreadStackSizeControl&);
   ThreadStackSizeControl& operator=(const ThreadStackSizeControl&);
   
   // private members
   tbb::global_control* control_;
   
};
   
} // anonymous namespace


inline void tbbParallelFor(std::size_t begin,
                           std::size_t end, 
                           Worker& worker,
                           std::size_t grainSize = 1,
                           int numThreads = tbb::task_arena::automatic)
{
   ThreadStackSizeControl control;
   
   tbb::task_arena arena(numThreads);
   tbb::task_group group;
   
   TBBArenaParallelForExecutor executor(group, worker, begin, end, grainSize);
   arena.execute(executor);
}

template <typename Reducer>
inline void tbbParallelReduce(std::size_t begin,
                              std::size_t end, 
                              Reducer& reducer,
                              std::size_t grainSize = 1,
                              int numThreads = tbb::task_arena::automatic)
{
   ThreadStackSizeControl control;
   
   tbb::task_arena arena(numThreads);
   tbb::task_group group;
   
   TBBArenaParallelReduceExecutor<Reducer> executor(group, reducer, begin, end, grainSize);
   arena.execute(executor);
}

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_TBB__
