

#include <RcppParallel/Common.h>

#ifndef TBB_PREVIEW_GLOBAL_CONTROL
# define TBB_PREVIEW_GLOBAL_CONTROL 1
#endif

#include <tbb/tbb.h>
#include <tbb/global_control.h>
#include <tbb/scalable_allocator.h>

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

} // end namespace RcppParallel
