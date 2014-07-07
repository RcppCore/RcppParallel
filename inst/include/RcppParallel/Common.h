#ifndef __RCPP_PARALLEL_COMMON__
#define __RCPP_PARALLEL_COMMON__


namespace RcppParallel {

// Work executed within a background thread. We implement dynamic
// dispatch using vtables so we can have a stable type to cast
// to from the void* passed to the worker thread (required because
// the tinythreads interface allows to pass only a void* to the
// thread main rather than a generic type / template)

struct Worker {
   virtual ~Worker() {}
   virtual void operator()(std::size_t begin, std::size_t end) = 0;
};

} // namespace RcppParallel


#endif // __RCPP_PARALLEL_COMMON__
