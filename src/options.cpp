
#include <RcppParallel.h>

#include <Rinternals.h>

#if RCPP_PARALLEL_USE_TBB // TBB support turned on

#include <string>
#include <exception>

#include <tbb/task_scheduler_init.h>

extern "C" SEXP setThreadOptions(SEXP numThreadsSEXP, SEXP stackSizeSEXP) {

   static tbb::task_scheduler_init* s_pTaskScheduler = NULL;

   int numThreads = Rf_asInteger(numThreadsSEXP);
   
   int stackSize = Rf_asInteger(stackSizeSEXP);
   
   try
   {
      if (!s_pTaskScheduler) {
         s_pTaskScheduler = new tbb::task_scheduler_init(numThreads, stackSize);
      } else {
         s_pTaskScheduler->terminate();
         s_pTaskScheduler->initialize(numThreads, stackSize); 
      }
   }
   catch(const std::exception& e)
   {
      Rf_error(("Error loading TBB: " + std::string(e.what())).c_str());
   }
   catch(...)
   {
      Rf_error("Error loading TBB: (Unknown error)");
   }
   
   return R_NilValue;
}

extern "C" SEXP defaultNumThreads() {
   SEXP threadsSEXP = Rf_allocVector(INTSXP, 1);
   INTEGER(threadsSEXP)[0] = tbb::task_scheduler_init::default_num_threads();
   return threadsSEXP;
}

#else // TBB support not turned on

#include <tthread/tinythread.h>

extern "C" SEXP setThreadOptions(SEXP numThreadsSEXP, SEXP stackSizeSEXP) {
   return R_NilValue;   
}

extern "C" SEXP defaultNumThreads() {
   SEXP threadsSEXP = Rf_allocVector(INTSXP, 1);
   INTEGER(threadsSEXP)[0] = tthread::thread::hardware_concurrency();
   return threadsSEXP;
}

#endif
