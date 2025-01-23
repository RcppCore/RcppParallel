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

// This class is primarily used to implement type erasure. The goals here were:
//
// 1. Hide the tbb symbols / implementation details from client R packages.
//    That is, they should get the tools they need only via RcppParallel.
//
// 2. Do this in a way that preserves binary compatibility with pre-existing
//    classes that make use of parallelReduce().
//
// 3. Ensure that those packages, when re-compiled without source changes,
//    can still function as expected.
//
// The downside here is that all the indirection through std::function<>
// and the requirement for RTTI is probably expensive, but I couldn't find
// a better way forward that could also preserve binary compatibility with
// existing pre-built pacakges.
//
// Hopefully, in a future release, we can do away with this wrapper, once
// packages have been rebuilt and no longer implicitly depend on TBB internals.
struct ReducerWrapper {

   template <typename T>
   ReducerWrapper(T* reducer)
   {
      self_ = reinterpret_cast<void*>(reducer);
      owned_ = false;

      work_ = [&](void* self, std::size_t begin, std::size_t end)
      {
         (*reinterpret_cast<T*>(self))(begin, end);
      };

      split_ = [&](void* object, Split split)
      {
         return new T(*reinterpret_cast<T*>(object), split);
      };

      join_ = [&](void* self, void* other)
      {
         (*reinterpret_cast<T*>(self)).join(*reinterpret_cast<T*>(other));
      };

      deleter_ = [&](void* object)
      {
         delete (T*) object;
      };
   }

   ~ReducerWrapper()
   {
      if (owned_)
      {
         deleter_(self_);
         self_ = nullptr;
      }
   }

   void operator()(std::size_t begin, std::size_t end) const
   {
      work_(self_, begin, end);
   }

   ReducerWrapper(const ReducerWrapper& rhs, Split split)
   {
      self_  = rhs.split_(rhs.self_, split);
      owned_ = true;

      work_    = rhs.work_;
      split_   = rhs.split_;
      join_    = rhs.join_;
      deleter_ = rhs.deleter_;
   }

   void join(const ReducerWrapper& rhs) const
   {
      join_(self_, rhs.self_);
   }

private:
   void* self_ = nullptr;
   bool owned_ = false;

   std::function<void (void*, std::size_t, std::size_t)> work_;
   std::function<void*(void*, Split)> split_;
   std::function<void (void*, void*)> join_;
   std::function<void(void*)> deleter_;
};

void tbbParallelFor(std::size_t begin,
                    std::size_t end,
                    Worker& worker,
                    std::size_t grainSize = 1,
                    int numThreads = -1);

void tbbParallelReduceImpl(std::size_t begin,
                           std::size_t end,
                           ReducerWrapper& wrapper,
                           std::size_t grainSize = 1,
                           int numThreads = -1);

template <typename Reducer>
void tbbParallelReduce(std::size_t begin,
                       std::size_t end,
                       Reducer& reducer,
                       std::size_t grainSize = 1,
                       int numThreads = -1)
{
   ReducerWrapper wrapper(&reducer);
   tbbParallelReduceImpl(begin, end, wrapper, grainSize, numThreads);
}

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_TBB__
