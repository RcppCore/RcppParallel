#ifndef __RCPP_PARALLEL_FORK__
#define __RCPP_PARALLEL_FORK__

namespace RcppParallel {

// Returns true if the current process is a fork() of the process in which
// RcppParallel was originally loaded. Always returns false on Windows, which
// has no fork().
//
// Intel TBB does not support being used after fork(). Code paths reachable
// from fork()'d children (for example, via parallel::mclapply) should call
// this and fall back to a serial implementation when it returns true.
bool isForkedChild();

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_FORK__
