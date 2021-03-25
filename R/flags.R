
#' Compilation flags for RcppParallel
#' 
#' Output the compiler or linker flags required to build against RcppParallel.
#' 
#' These functions are typically called from \code{Makevars} as follows:
#' 
#' ```
#' PKG_LIBS += $(shell "${R_HOME}/bin/Rscript" -e "RcppParallel::LdFlags()")
#' ```
#' 
#' On Windows, the flags ensure that the package links with the built-in TBB
#' library. On Linux and macOS, the output is empty, because TBB is loaded
#' dynamically.
#' 
#' To ensure portability, load \pkg{RcppParallel} before loading
#' your package, e.g. by including \code{importFrom(RcppParallel,
#' RcppParallelLibs)} in your \code{NAMESPACE} file. See
#' \url{https://github.com/RcppCore/RcppParallel/issues/129} for details.
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



tbbCxxFlags <- function() {
   
   flags <- character()
   
   # opt-in to TBB on Windows
   if (is_windows())
      flags <- c(flags, "-DRCPP_PARALLEL_USE_TBB=1")
   
   # if TBB_INC is set, apply those library paths
   tbbInc <- Sys.getenv("TBB_INC", unset = NA)
   if (!is.na(tbbInc)) {
      
      # add include path
      flags <- c(flags, paste0("-I", shQuote(asBuildPath(tbbInc))))
      
      # prefer new interface if version.h exists
      versionPath <- file.path(tbbInc, "tbb/version.h")
      if (file.exists(versionPath))
         flags <- c(flags, "-DTBB_INTERFACE_NEW")
      
   }
   
   # return flags as string
   paste(flags, collapse = " ")
   
}

# Return the linker flags requried for TBB on this platform
tbbLdFlags <- function() {
   
   # shortcut if TBB_LIB defined
   tbbLib <- Sys.getenv("TBB_LIB", unset = NA)
   if (!is.na(tbbLib)) {
      fmt <- "-L%1$s -Wl,-rpath,%1$s -ltbb -ltbbmalloc"
      return(sprintf(fmt, shQuote(asBuildPath(tbbLib))))
   }
   
   # on Windows and Solaris, we need to explicitly link
   needsExplicitFlags <- is_windows() || (is_solaris() && !is_sparc())
   if (needsExplicitFlags) {
      libPath <- asBuildPath(dirname(tbbLibPath()))
      libFlag <- paste0("-L", shQuote(libPath))
      return(paste(libFlag, "-ltbb", "-ltbbmalloc"))
   }
   
   # nothing required on other platforms
   ""
   
}

tbbRoot <- function() {
   rArch <- .Platform$r_arch
   libDir <- paste(c("lib", if (nzchar(rArch)) rArch), collapse = "/")
   system.file(libDir, package = "RcppParallel")
}

# Determine the platform-specific path to the TBB library
tbbLibPath <- function(suffix = "") {
   
   # library paths for different OSes
   sysname <- Sys.info()[["sysname"]]
   
   tbbLibNames <- list(
      "Darwin"  = paste0("libtbb", suffix, ".dylib"),
      "Windows" = paste0("tbb",    suffix, ".dll"),
      "SunOS"   = paste0("libtbb", suffix, ".so"),
      "Linux"   = paste0("libtbb", suffix, c(".so.2", ".so"))
   )
   
   # skip systems that we know not to be compatible
   isCompatible <-
      !is_sparc() &&
      !is.null(tbbLibNames[[sysname]])
   
   if (!isCompatible)
      return(NULL)
   
   # find root for TBB install
   tbbRoot <- Sys.getenv("TBB_LIB", unset = tbbRoot())
   libNames <- tbbLibNames[[sysname]]
   for (libName in libNames) {
      tbbName <- file.path(tbbRoot, libName)
      if (file.exists(tbbName))
         return(tbbName)
   }
   
}

# Helper function to ape the behavior of the R build system
# when providing paths to libraries
asBuildPath <- function(path) {
   
   # nothing to do for non-Windows
   if (!is_windows())
      return(path)
   
   # normalize paths using forward slashes
   path <- normalizePath(path, winslash = "/", mustWork = FALSE)
   
   # prefer short path names if the path has spaces
   if (grepl(" ", path, fixed = TRUE))
      path <- utils::shortPathName(path)
   
   # return path
   return(path)
   
}
