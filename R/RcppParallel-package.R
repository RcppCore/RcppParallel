
#' Parallel programming tools for Rcpp
#' 
#' High level functions for doing parallel programming with Rcpp.  For example,
#' the `parallelFor()` function can be used to convert the work of a
#' standard serial "for" loop into a parallel one, and the `parallelReduce()`
#' function can be used for accumulating aggregate or other values.
#' 
#' The high level interface enables safe and robust parallel programming
#' without direct manipulation of operating system threads. On Windows, macOS,
#' and Linux systems the underlying implementation is based on Intel TBB
#' (Threading Building Blocks). On other platforms, a less-performant fallback
#' implementation based on the TinyThread library is used.
#' 
#' For additional documentation, see the package website at:
#' 
#' <https://rcppcore.github.io/RcppParallel/>
#' 
#' 
#' @name RcppParallel-package
#' @docType package
#' @aliases RcppParallel RcppParallel-package
#' @keywords package parallel
NULL
