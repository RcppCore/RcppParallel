
#include <tbb/task_scheduler_init.h>

#include <Rinternals.h>

static tbb::task_scheduler_init* s_pTaskScheduler = NULL;

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
