
#include <RcppParallel.h>

#include <Rinternals.h>

#if RCPP_PARALLEL_USE_TBB // TBB support turned on

#include <string>
#include <exception>

#include <tbb/global_control.h>

extern "C" SEXP setThreadOptions(SEXP numThreadsSEXP, SEXP stackSizeSEXP) {

   static tbb::global_control* threadControl = nullptr;
   static tbb::global_control* stackControl = nullptr;
   
   int numThreads = Rf_asInteger(numThreadsSEXP);
   int stackSize = Rf_asInteger(stackSizeSEXP);
   
   try
   {
      delete threadControl;
      if (numThreads > 0)
      {
         threadControl = new tbb::global_control(
            tbb::global_control::max_allowed_parallelism,
            numThreads
         );
      }
      
      delete stackControl;
      if (stackSize > 0)
      {
         stackControl = new tbb::global_control(
            tbb::global_control::thread_stack_size,
            stackSize
         );
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
