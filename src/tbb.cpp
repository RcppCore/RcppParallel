
#include <tbb/task_scheduler_init.h>

#include <Rinternals.h>

static tbb::task_scheduler_init* s_pTaskScheduler = NULL;

extern "C" SEXP tbb_initialize(SEXP numThreadsSEXP, SEXP stackSizeSEXP) {
   
   if (s_pTaskScheduler)
      Rf_error("TBB already initialized");
      
   int numThreads = Rf_asInteger(numThreadsSEXP);
   int stackSize = Rf_asInteger(stackSizeSEXP);
   
   try
   {
      s_pTaskScheduler = new tbb::task_scheduler_init(numThreads, stackSize);
   }
   catch(...)
   {
   }
   
   return R_NilValue;
}

extern "C" SEXP tbb_is_active() {
   SEXP activeSEXP = Rf_allocVector(LGLSXP, 1);
   LOGICAL(activeSEXP)[0] = s_pTaskScheduler != NULL;
   return activeSEXP;
}

extern "C" SEXP tbb_default_num_threads() {
   SEXP threadsSEXP = Rf_allocVector(INTSXP, 1);
   INTEGER(threadsSEXP)[0] = tbb::task_scheduler_init::default_num_threads();
   return threadsSEXP;
}

extern "C" SEXP tbb_terminate() {
   
   if (!s_pTaskScheduler)
      Rf_error("TBB not currently initialized");
   
   try
   {
      s_pTaskScheduler->terminate();
      delete s_pTaskScheduler;
   }
   catch(...)
   {
   }
   
   s_pTaskScheduler = NULL;
   
   return R_NilValue;
}