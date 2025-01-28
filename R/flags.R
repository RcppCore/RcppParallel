
#' Compilation flags for RcppParallel
#'
#' Output the compiler or linker flags required to build against RcppParallel.
#'
#' These functions are typically called from `Makevars` as follows:
#'
#' ```
#' PKG_LIBS += $(shell "${R_HOME}/bin/Rscript" -e "RcppParallel::LdFlags()")
#' ```
#'
#' On Windows, the flags ensure that the package links with the built-in TBB
#' library. On Linux and macOS, the output is empty, because TBB is loaded
#' dynamically on load by `RcppParallel`.
#'
#' \R packages using RcppParallel should also add the following to their
#' `NAMESPACE` file:
#'
#' ```
#' importFrom(RcppParallel, RcppParallelLibs)
#' ```
#'
#' This is necessary to ensure that \pkg{RcppParallel} (and so, TBB) is loaded
#' and available.
#'
#' @name flags
#' @rdname flags
#' @aliases RcppParallelLibs LdFlags CxxFlags
#'
#' @return Returns \code{NULL}, invisibly. These functions are called for
#'   their side effects (writing the associated flags to stdout).
#'
NULL


#' @name flags
#' @export
CxxFlags <- function() {
   cat(tbbCxxFlags())
}

#' @name flags
#' @export
LdFlags <- function() {
   cat(tbbLdFlags())
}

#' @name flags
#' @export
RcppParallelLibs <- function() {
   LdFlags()
}

