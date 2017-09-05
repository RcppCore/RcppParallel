
#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern "C" SEXP defaultNumThreads();
extern "C" SEXP setThreadOptions(SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
   {"defaultNumThreads", (DL_FUNC) &defaultNumThreads, 0},
   {"setThreadOptions",  (DL_FUNC) &setThreadOptions,  2},
   {NULL, NULL, 0}
};

extern "C" void R_init_RcppParallel(DllInfo *dll)
{
   R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
   R_useDynamicSymbols(dll, FALSE);
}
