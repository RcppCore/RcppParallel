
#include <RcppParallel/Common.h>
#include <RcppParallel/TBB.h>

namespace RcppParallel {

tbb::global_control* s_globalControl = nullptr;

ThreadStackSizeControl::ThreadStackSizeControl()
{
#ifdef RCPP_PARALLEL_USE_TBB
   int stackSize = resolveValue("RCPP_PARALLEL_STACK_SIZE", 0, 0);
   if (stackSize > 0)
   {
      s_globalControl = new tbb::global_control(
         tbb::global_control::thread_stack_size,
         stackSize
      );
   }
#endif
}

ThreadStackSizeControl::~ThreadStackSizeControl()
{
#ifdef RCPP_PARALLEL_USE_TBB
   if (s_globalControl != nullptr)
   {
      delete s_globalControl;
      s_globalControl = nullptr;
   }
#endif
}

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

} // end namespace RcppParallel
