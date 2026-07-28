
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

      # also offer the stub library. RcppParallel.dll re-exports whichever TBB
      # objects happened to be pulled out of the static library when it was
      # linked, which is an incidental export surface rather than a declared
      # one; the stub exports the runtime wholesale, so anything missing from
      # RcppParallel.dll can still be resolved. this comes last deliberately:
      # the linker satisfies symbols in order, so RcppParallel's own exports
      # still win, and no dependency on the stub is recorded unless something
      # actually needs it
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
   if (is_mac()) {
      fmt <- "-L%s -l%s -l%s"
      return(sprintf(fmt, asBuildPath(tbbLibraryPath()), TBB_NAME, TBB_MALLOC_NAME))
   }

   # nothing required on other platforms
   ""

}

# Resolve the directory containing the TBB libraries this installation uses.
#
# 'tbbLib' and 'rtoolsLib' are parameters so that the resolution order below
# can be exercised in tests on any platform; callers should use the defaults.
tbbRoot <- function(tbbLib = TBB_LIB, rtoolsLib = rtoolsTbbRoot()) {

   # an explicitly-set TBB_LIB always wins: unlike the value recorded at
   # configure time, it describes this machine, right now
   envLib <- Sys.getenv("TBB_LIB", unset = "")
   if (nzchar(envLib))
      return(envLib)

   # if the package wasn't configured against an external TBB, then the
   # libraries it uses (if any) are the ones shipped within the package
   if (!nzchar(tbbLib))
      return(archSystemFile("lib"))

   # TBB_LIB is resolved by configure and baked into the installed package, so
   # it describes the machine that _built_ the package. That's the same machine
   # for a source install, but not for a binary one: CRAN's Windows builders
   # find Rtools on 'D:/', where users typically have it on 'C:/'. Only trust
   # the recorded path if it's still there (#270)
   if (dir.exists(tbbLib))
      return(tbbLib)

   # the recorded path is gone, so it was a binary build elsewhere. On Windows
   # an external TBB means the Rtools one, so look for the toolchain installed
   # here instead of the one used at build time
   if (!is.null(rtoolsLib))
      return(rtoolsLib)

   archSystemFile("lib")

}

# Locate the library directory of an Rtools-provided oneTBB, mirroring the
# detection in tools/config/configure.R. Returns NULL when not on Windows, or
# when no usable Rtools TBB is found.
#
# 'gcc' is a parameter so this can be tested against a synthetic toolchain
# tree on any platform; callers should use the default.
rtoolsTbbRoot <- function(gcc = if (is_windows()) Sys.which("gcc") else "") {

   # note that Rtools is on the PATH while a package is being compiled, which
   # is when this lookup is normally consulted (e.g. from a Makevars)
   if (!nzchar(gcc))
      return(NULL)

   # TBB sits alongside the rest of the toolchain, two directories above the
   # compiler: '<rtools>/<target>/bin/gcc.exe' -> '<rtools>/<target>/lib'
   root <- dirname(dirname(gcc))
   tbbLib <- file.path(root, "lib")

   # apply the same gate configure does: only a oneTBB is usable here, as
   # older Rtools TBBs are deliberately passed over (see configure.R)
   hasTbb <-
      length(list.files(tbbLib, pattern = "^libtbb")) &&
      file.exists(file.path(root, "include", "oneapi"))

   if (!hasTbb)
      return(NULL)

   normalizePath(tbbLib, winslash = "/", mustWork = FALSE)

}
