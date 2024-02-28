/**
 * @title Test for TRUE and FALSE macros
 * @author Travers Ching
 * @license GPL (>= 2)
 */

// TRUE and FALSE macros that may come with system headers on some systems
// But conflict with R.h (R_ext/Boolean.h)
// TRUE and FALSE macros should be undef in RcppParallel.h

#include <Rcpp.h>
#include <RcppParallel.h>

// [[Rcpp::depends(RcppParallel)]]

#ifndef TRUE
static_assert(true, "Macro TRUE does not exist");
#else
static_assert(false, "Macro TRUE exists");
#endif

#ifndef FALSE
static_assert(true, "Macro FALSE does not exist");
#else
static_assert(false, "Macro FALSE exists");
#endif

// [[Rcpp::export]]
int hush_no_export_warning() {
  return 1;
}