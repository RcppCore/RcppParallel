
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
using namespace RcppParallel;

// [[Rcpp::export]]
void tbbMalloc() {
   
#if RCPP_PARALLEL_USE_TBB
   
   std::vector<int,tbb::tbb_allocator<int> > vec;
   vec.push_back(42);
   
   std::vector<int,tbb::scalable_allocator<int> > scalableVec;
   scalableVec.push_back(42);
   
   std::vector<int,tbb::cache_aligned_allocator<int> > cacheAlignedVec;
   cacheAlignedVec.push_back(42);
   
#endif 
  
}

