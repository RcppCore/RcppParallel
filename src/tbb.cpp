
#if RCPP_PARALLEL_USE_TBB

#include <RcppParallel/Common.h>
#include <RcppParallel/TBB.h>

namespace RcppParallel {

tbb::global_control* s_globalControl = nullptr;

// TBB Tools ----

struct TBBWorker
{
   explicit TBBWorker(Worker& worker) : worker_(worker) {}

   void operator()(const tbb::blocked_range<size_t>& r) const {
      worker_(r.begin(), r.end());
   }

private:
   Worker& worker_;
};

ThreadStackSizeControl::ThreadStackSizeControl()
{
   int stackSize = resolveValue("RCPP_PARALLEL_STACK_SIZE", 0, 0);
   if (stackSize > 0)
   {
      s_globalControl = new tbb::global_control(
         tbb::global_control::thread_stack_size,
         stackSize
      );
   }
}

ThreadStackSizeControl::~ThreadStackSizeControl()
{
   if (s_globalControl != nullptr)
   {
      delete s_globalControl;
      s_globalControl = nullptr;
   }
}


// TBB Parallel For ----

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

void tbbParallelFor(std::size_t begin,
                    std::size_t end,
                    Worker& worker,
                    std::size_t grainSize,
                    int numThreads)
{
   ThreadStackSizeControl control;

   tbb::task_group group;
   TBBArenaParallelForExecutor executor(group, worker, begin, end, grainSize);

   tbb::task_arena arena(numThreads);
   arena.execute(executor);
}


// TBB Parallel Reduce ----

struct TBBReducer
{
   explicit TBBReducer(ReducerWrapper& reducer)
      : pSplitReducer_(NULL), reducer_(reducer)
   {
   }

   TBBReducer(TBBReducer& tbbReducer, tbb::split)
      : pSplitReducer_(new ReducerWrapper(tbbReducer.reducer_, RcppParallel::Split())),
        reducer_(*pSplitReducer_)
   {
   }

   virtual ~TBBReducer() { delete pSplitReducer_; }

   void operator()(const tbb::blocked_range<size_t>& r)
   {
      reducer_(r.begin(), r.end());
   }

   void join(const TBBReducer& tbbReducer)
   {
      reducer_.join(tbbReducer.reducer_);
   }

private:
   ReducerWrapper* pSplitReducer_;
   ReducerWrapper& reducer_;
};

class TBBParallelReduceExecutor
{
public:

   TBBParallelReduceExecutor(ReducerWrapper& reducer,
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
      TBBReducer tbbReducer(reducer_);
      tbb::parallel_reduce(
         tbb::blocked_range<std::size_t>(begin_, end_, grainSize_),
         tbbReducer
      );
   }

private:
   ReducerWrapper& reducer_;
   std::size_t begin_;
   std::size_t end_;
   std::size_t grainSize_;
};

class TBBArenaParallelReduceExecutor
{
public:

   TBBArenaParallelReduceExecutor(tbb::task_group& group,
                                  ReducerWrapper& reducer,
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
      TBBParallelReduceExecutor executor(reducer_, begin_, end_, grainSize_);
      group_.run_and_wait(executor);
   }

private:

   tbb::task_group& group_;
   ReducerWrapper& reducer_;
   std::size_t begin_;
   std::size_t end_;
   std::size_t grainSize_;
};

void tbbParallelReduceImpl(std::size_t begin,
                           std::size_t end,
                           ReducerWrapper& reducer,
                           std::size_t grainSize,
                           int numThreads)
{
   ThreadStackSizeControl control;

   tbb::task_group group;
   TBBArenaParallelReduceExecutor executor(group, reducer, begin, end, grainSize);

   tbb::task_arena arena(numThreads);
   arena.execute(executor);
}

} // end namespace RcppParallel

#endif /* RCPP_PARALLEL_USE_TBB */
