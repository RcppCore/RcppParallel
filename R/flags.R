
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
#' What is emitted depends on how TBB is resolved at runtime on each platform.
#' On Windows, every symbol has to be resolved at link time, so the flags name
#' both the TBB libraries RcppParallel ships and RcppParallel itself. On macOS,
#' they name the TBB libraries along with an `-rpath` entry, so that the
#' resulting binary can find them without relying on `RcppParallel` having been
#' loaded first. On Linux, the output is empty: TBB symbols are left undefined
#' at link time and resolved from the libraries `RcppParallel` loads.
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

