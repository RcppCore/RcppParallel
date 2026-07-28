
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
   #
   # on Windows the library we install is the 'tbb.dll' stub -- TBB itself is
   # inside RcppParallel.dll -- so look for that first. the static archives are
   # still tried afterwards, for a TBB_LIB pointed at an Rtools tree at runtime
   tbbLibNames <- list(
      "Darwin"  = paste0("lib", name, ".dylib"),
      "Windows" = c(paste0(name, ".dll"), paste0("lib", name, c("12", ""), ".a")),
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

      tbbName <- archSystemFile("lib", libName)
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

      libPath <- archSystemFile("libs")

      ldFlags <- sprintf("-L%s -lRcppParallel", asBuildPath(libPath))

      # also offer the stub library, which exports the TBB runtime wholesale.
      # this is not just a safety net: R CMD SHLIB links RcppParallel.dll
      # against an export list generated from our own objects, so the TBB
      # entry points pulled in from the static library are not re-exported,
      # and a downstream package linking '-lRcppParallel' alone resolves none
      # of them (which is what broke rstan). the stub is what makes those
      # symbols reachable at all.
      #
      # it still comes last, so that anything RcppParallel.dll does export
      # wins, and so no import of the stub is recorded unless something needs
      # it. that matters because the stub carries its own copy of the oneTBB
      # runtime: a package split across both would register observers with one
      # scheduler while its tasks ran in the other.
      # .github/scripts/tbb-downstream-check.R asserts that does not happen
      tbbPath <- archSystemFile("lib")
      if (file.exists(file.path(tbbPath, "tbb.dll")))
         ldFlags <- paste(ldFlags, sprintf("-L%s -ltbb", asBuildPath(tbbPath)))

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
   #
   # the bundled libraries record an '@rpath'-relative install name (e.g.
   # '@rpath/libtbb.dylib'), so '-L' alone is not enough: the client library
   # ends up with no runtime search path for TBB at all, and only loads
   # because RcppParallel -- and hence TBB -- normally happens to be loaded
   # into the process first. Emit a matching '-rpath' so the client can
   # resolve TBB on its own. (#209)
   if (is_mac()) {
      fmt <- "-L%1$s -Wl,-rpath,%1$s -l%2$s -l%3$s"
      return(sprintf(fmt, asBuildPath(tbbLibraryPath()), TBB_NAME, TBB_MALLOC_NAME))
   }

   # nothing required on other platforms
   ""

}

tbbRoot <- function() {

   # on Windows, always answer with our own library directory. TBB is linked
   # statically into RcppParallel.dll there, and the only TBB library we
   # install is the tbb.dll stub, so that directory is the whole story. TBB_LIB
   # is worse than useless here: it records the Rtools tree of whichever
   # machine ran configure, which for a pre-built binary is a path that need
   # not exist on the user's machine at all (#270)
   if (is_windows())
      return(archSystemFile("lib"))

   if (nzchar(TBB_LIB))
      return(TBB_LIB)

   archSystemFile("lib")

}
