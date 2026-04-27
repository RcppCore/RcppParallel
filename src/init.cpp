#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

#ifndef _WIN32
# include <sys/types.h>
# include <unistd.h>
#endif

namespace RcppParallel {

#ifndef _WIN32
static pid_t s_loadPid = 0;

bool isForkedChild()
{
   return getpid() != s_loadPid;
}
#else
bool isForkedChild()
{
   return false;
}
#endif

} // namespace RcppParallel

/* .Call calls */
extern "C" SEXP defaultNumThreads();

extern "C" SEXP isForkedChild()
{
   int forked = RcppParallel::isForkedChild() ? TRUE : FALSE;
   return Rf_ScalarLogical(forked);
}

static const R_CallMethodDef CallEntries[] = {
   {"defaultNumThreads", (DL_FUNC) &defaultNumThreads, 0},
   {"isForkedChild",     (DL_FUNC) &isForkedChild,     0},
   {NULL, NULL, 0}
};

extern "C" void R_init_RcppParallel(DllInfo *dll)
{
#ifndef _WIN32
   RcppParallel::s_loadPid = getpid();
#endif

   R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
   R_useDynamicSymbols(dll, FALSE);
}
