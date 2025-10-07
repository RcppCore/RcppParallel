
#' Get the Path to a TBB Library
#'
#' Retrieve the path to a TBB library. This can be useful for \R packages
#' using RcppParallel that wish to use, or re-use, the version of TBB that
#' RcppParallel has been configured to use.
#'
#' @param name
#'   The name of the TBB library to be resolved. Normally, this is one of
#'   `tbb`, `tbbmalloc`, or `tbbmalloc_proxy`. When `NULL`, the library
#'   path containing the TBB libraries is returned instead.
#'
#' @export
tbbLibraryPath <- function(name = NULL) {

   # library paths for different OSes
   sysname <- Sys.info()[["sysname"]]

   # find root for TBB install
   tbbRoot <- Sys.getenv("TBB_LIB", unset = tbbRoot())
   if (is.null(name))
      return(tbbRoot)

   # form library names
   tbbLibNames <- list(
      "Darwin"  = paste0("lib", name, ".dylib"),
      "Windows" = paste0("lib", name, c("12", ""), ".a"),
      "SunOS"   = paste0("lib", name, ".so"),
      "Linux"   = paste0("lib", name, c(".so.2", ".so"))
   )

   # skip systems that we know not to be compatible
   isCompatible <- !is_sparc() && !is.null(tbbLibNames[[sysname]])
   if (!isCompatible)
      return(NULL)

   # find the request library (if any)
   libNames <- tbbLibNames[[sysname]]
   for (libName in libNames) {
      
      tbbName <- file.path(tbbRoot, libName)
      if (file.exists(tbbName))
         return(tbbName)
      
      arch <- if (nzchar(.Platform$r_arch)) .Platform$r_arch
      suffix <- paste(c("lib", arch, libName), collapse = "/")
      tbbName <- system.file(suffix, package = "RcppParallel")
      if (file.exists(tbbName))
         return(tbbName)
      
   }

}

tbbCxxFlags <- function() {

  if (!TBB_ENABLED)
      return("-DRCPP_PARALLEL_USE_TBB=0")
   
   flags <- c("-DRCPP_PARALLEL_USE_TBB=1")

   # if TBB_INC is set, apply those library paths
   tbbInc <- Sys.getenv("TBB_INC", unset = TBB_INC)
   if (!file.exists(tbbInc)) {
      tbbInc <- system.file("include", package = "RcppParallel")
   }
   
   # add include path
   if (nzchar(tbbInc) && file.exists(tbbInc)) {
      
      # prefer new interface if version.h exists -- we keep this
      # for compatibility with packages like StanHeaders, rstan
      versionPath <- file.path(tbbInc, "tbb/version.h")
      if (file.exists(versionPath))
         flags <- c(flags, "-DTBB_INTERFACE_NEW")
      
      # now add the include path
      flags <- c(flags, paste0("-I", asBuildPath(tbbInc)))
      
   }

   # return flags as string
   paste(flags, collapse = " ")

}

# Return the linker flags required for TBB on this platform
tbbLdFlags <- function() {
   
   # on Windows, we statically link to oneTBB
   if (is_windows()) {
      
      libPath <- system.file("libs", package = "RcppParallel")
      if (nzchar(.Platform$r_arch))
         libPath <- file.path(libPath, .Platform$r_arch)
      
      ldFlags <- sprintf("-L%s -lRcppParallel", asBuildPath(libPath))
      return(ldFlags)
      
   }
   
   # shortcut if TBB_LIB defined
   tbbLib <- Sys.getenv("TBB_LINK_LIB", Sys.getenv("TBB_LIB", unset = TBB_LIB))
   if (nzchar(tbbLib)) {
      if (R.version$os == "emscripten") {
         fmt <- "-L%1$s -l%2$s"
         return(sprintf(fmt, asBuildPath(tbbLib), TBB_NAME))
      }
      fmt <- "-L%1$s -Wl,-rpath,%1$s -l%2$s -l%3$s"
      return(sprintf(fmt, asBuildPath(tbbLib), TBB_NAME, TBB_MALLOC_NAME))
   }
   
   # explicitly link on macOS
   # https://github.com/RcppCore/RcppParallel/issues/206
   if (is_mac()) {
      fmt <- "-L%s -l%s -l%s"
      return(sprintf(fmt, asBuildPath(tbbLibraryPath()), TBB_NAME, TBB_MALLOC_NAME))
   }

   # nothing required on other platforms
   ""

}

tbbRoot <- function() {

   if (nzchar(TBB_LIB))
      return(TBB_LIB)

   rArch <- .Platform$r_arch
   parts <- c("lib", if (nzchar(rArch)) rArch)
   libDir <- paste(parts, collapse = "/")
   system.file(libDir, package = "RcppParallel")

}
