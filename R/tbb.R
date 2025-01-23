
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
      "Windows" = paste0(       name, ".dll"),
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
   }

}

tbbCxxFlags <- function() {

   flags <- character()

   # opt-in to TBB on Windows
   if (is_windows()) {
      flags <- c(flags, "-DRCPP_PARALLEL_USE_TBB=1")
      if (R.version$arch == "aarch64") {
         # TBB does not have assembly code for Windows ARM64
         # so we need to use compiler builtins
         flags <- c(flags, "-DTBB_USE_GCC_BUILTINS")
      }
   }

   # if TBB_INC is set, apply those library paths
   tbbInc <- Sys.getenv("TBB_INC", unset = TBB_INC)
   if (nzchar(tbbInc)) {

      # add include path
      flags <- c(flags, paste0("-I", asBuildPath(tbbInc)))

      # prefer new interface if version.h exists
      versionPath <- file.path(tbbInc, "tbb/version.h")
      if (file.exists(versionPath))
         flags <- c(flags, "-DTBB_INTERFACE_NEW")

   }

   # return flags as string
   paste(flags, collapse = " ")

}

# Return the linker flags required for TBB on this platform
tbbLdFlags <- function() {

   tbbFlags <- tbbLdFlagsImpl()

   if (is_windows()) {
      libDir <- system.file("libs", .Platform$r_arch, package = "RcppParallel")
      libName <- paste0("RcppParallel", .Platform$dynlib.ext)
      newFlags <- sprintf("-L%s -lRcppParallel", shQuote(libDir))
      tbbFlags <- paste(newFlags, tbbFlags)
   }

   tbbFlags

}

tbbLdFlagsImpl <- function() {

   # shortcut if TBB_LIB defined
   tbbLib <- Sys.getenv("TBB_LINK_LIB", Sys.getenv("TBB_LIB", unset = TBB_LIB))
   if (nzchar(tbbLib)) {

      fmt <- if (is_windows()) {
         "-L%1$s -ltbb -ltbbmalloc"
      } else {
         "-L%1$s -Wl,-rpath,%1$s -ltbb -ltbbmalloc"
      }

      return(sprintf(fmt, asBuildPath(tbbLib)))
   }

   # on Mac, Windows and Solaris, we need to explicitly link (#206)
   needsExplicitFlags <- is_mac() || is_windows() || (is_solaris() && !is_sparc())
   if (needsExplicitFlags) {
      libPath <- asBuildPath(tbbLibraryPath())
      libFlag <- paste0("-L", libPath)
      return(paste(libFlag, "-ltbb", "-ltbbmalloc"))
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
