
# make sure we call correct version of R
rExe <- if (.Platform$OS.type == "windows") "R.exe" else "R"
define(R = file.path(R.home("bin"), rExe))

# check whether user has Makevars file that might cause trouble
makevars <- Sys.getenv("R_MAKEVARS_USER", unset = "~/.R/Makevars")
if (file.exists(makevars)) {
   contents <- readLines(makevars, warn = FALSE)
   pattern <- "^(PKG_CPPFLAGS|PKG_CXXFLAGS)\\s*="
   bad <- grep(pattern, contents, perl = TRUE, value = TRUE)
   if (length(bad)) {
      
      text <- c(
         "",
         sprintf("NOTE: '%s' contains variable declarations incompatible with RcppParallel:", makevars),
         "",
         paste0("\t", bad),
         "",
         "Makevars variables prefixed with 'PKG_' should be considered reserved for use by R packages.",
         ""
      )
      
      writeLines(text, con = stdout())
      
   }
}

# NOTE: we deliberately do not look for a TBB provided by Rtools. Rtools
# ships static libraries only, and the TBB it provides varies with the
# toolchain: Rtools42 has Intel TBB 2017, whose headers downstream packages
# cannot build against, while later versions have oneTBB. Building the
# bundled copy instead gives every platform the same oneTBB, shipped as a
# shared library and linked the same way, and makes the TBB ABI a property
# of RcppParallel rather than of the user's toolchain. TBB_LIB / TBB_INC are
# still honoured for anyone wanting to supply their own.

# try and figure out path to TBB
tbbRoot  <- Sys.getenv("TBB_ROOT", unset = NA)
tbbLib   <- Sys.getenv("TBB_LIB", unset = NA)
tbbInc   <- Sys.getenv("TBB_INC", unset = NA)

tbbName  <- Sys.getenv("TBB_NAME", unset = "tbb")
tbbMallocName <- Sys.getenv("TBB_MALLOC_NAME", unset = "tbbmalloc")

# check TBB_ROOT first if defined
if (!is.na(tbbRoot)) {
   
   if (is.na(tbbLib)) {
      tbbLib <- file.path(tbbRoot, "lib")
   }
   
   if (is.na(tbbInc)) {
      tbbInc <- file.path(tbbRoot, "include")
   }
   
}

# if TBB_LIB is defined, guess TBB_INC
if (!is.na(tbbLib) && is.na(tbbInc)) {
   tbbIncCandidate <- file.path(tbbLib, "../include")
   if (file.exists(tbbIncCandidate)) {
      tbbInc <- normalizePath(tbbIncCandidate)
   }
}

# if TBB_LIB and TBB_INC are still not defined, try auto-detecting
tryAutoDetect <-
   .Platform$OS.type == "unix" &&
   Sys.getenv("TBB_AUTODETECT", unset = "FALSE") == "TRUE" &&
   is.na(tbbLib) &&
   is.na(tbbInc)

if (tryAutoDetect) {
   
   sysInfo <- as.list(Sys.info())
   
   homebrewPrefix <- if (sysInfo$sysname == "Darwin") {
      "/opt/homebrew"
   } else {
      "/usr/local"
   }
   
   tbbLibSearch <- if (sysInfo$sysname == "Darwin") {
      file.path(homebrewPrefix, "opt/tbb/lib/libtbb.dylib")
   } else {
      Sys.glob(c(
         "/usr/*/libtbb.so",
         "/usr/*/*/libtbb.so",
         "/usr/*/*/*/libtbb.so"
      ))
   }
   
   tbbIncSearch <- if (sysInfo$sysname == "Darwin") {
      file.path(homebrewPrefix, "opt/tbb/include/tbb")
   } else {
      Sys.glob(c(
         "/usr/include/tbb.h",
         "/usr/include/*/tbb.h"
      ))
   }
   
   if (length(tbbLibSearch) &&
       length(tbbIncSearch) &&
       file.exists(tbbLibSearch[[1L]]) &&
       file.exists(tbbIncSearch[[1L]]))
   {
      tbbLib <- dirname(tbbLibSearch[[1L]])
      tbbInc <- dirname(tbbIncSearch[[1L]])
   }
   
}

# if we didn't find a TBB to use, we'll build the bundled copy from sources --
# which requires cmake, on every platform. this is what 'SystemRequirements:
# CMake (>= 3.5)' in DESCRIPTION declares, so a missing or unusable cmake is an
# unmet system requirement and fails the install rather than quietly producing
# a package with no TBB backend. (the tinythread backend is still selectable at
# runtime via RCPP_PARALLEL_BACKEND; it is only no longer a build outcome.)
define(CMAKE = "")
buildBundledTbb <- FALSE

if (is.na(tbbLib)) {

   cmake <- local({

      # check for envvar
      cmake <- Sys.getenv("CMAKE", unset = NA)
      if (!is.na(cmake))
         return(cmake)

      # check for path
      cmake <- Sys.which("cmake")
      if (nzchar(cmake))
         return(cmake)

      # check for macOS cmake
      cmake <- "/Applications/CMake.app/Contents/bin/cmake"
      if (file.exists(cmake))
         return(cmake)

      NA

   })

   # make sure we have an appropriate version of cmake installed
   # (use the resolved path; cmake may not be on the PATH)
   #
   # any failure here -- a CMAKE pointing at nothing runnable, version output
   # we can't parse -- is reported as 'no usable cmake', so that the error
   # names the actual problem rather than surfacing as a parse failure
   cmakeVersion <- NA
   if (!is.na(cmake)) {
      cmakeVersion <- tryCatch({
         output <- system(paste(shQuote(cmake), "--version"), intern = TRUE)
         numeric_version(sub("cmake version ", "", output[[1L]]))
      }, condition = function(cnd) NA)
   }

   buildBundledTbb <- !is.na(cmakeVersion) && cmakeVersion >= "3.5"

   if (!buildBundledTbb) {

      reason <- if (is.na(cmake)) {
         "cmake was not found"
      } else if (is.na(cmakeVersion)) {
         sprintf("couldn't determine the version of the cmake at '%s'", cmake)
      } else {
         sprintf("cmake %s is too old (need >= 3.5)", cmakeVersion)
      }

      stop("error: RcppParallel requires cmake (>= 3.5); ", reason)

   }

   define(CMAKE = cmake)

}

# now, define TBB_LIB and TBB_INC as appropriate
define(
   TBB_LIB         = if (!is.na(tbbLib)) tbbLib else "",
   TBB_INC         = if (!is.na(tbbInc)) tbbInc else "",
   TBB_NAME        = tbbName,
   TBB_MALLOC_NAME = tbbMallocName
)

# set PKG_LIBS
pkgLibs <- if (!is.na(tbbLib)) {

   # a TBB supplied via TBB_LIB / TBB_ROOT. an rpath is meaningless on Windows,
   # where the loader has no equivalent -- see R/zzz.R for how we resolve there
   c(
      "-Wl,-L\"$(TBB_LIB)\"",
      if (.Platform$OS.type != "windows")
         sprintf("-Wl,-rpath,%s", shQuote(tbbLib)),
      "-l$(TBB_NAME)",
      "-l$(TBB_MALLOC_NAME)"
   )

} else if (R.version$os == "emscripten") {

   c(
      "-Wl,-Ltbb/build/lib_release",
      "-l$(TBB_NAME)"
   )

} else {

   c(
      "-Wl,-Ltbb/build/lib_release",
      "-l$(TBB_NAME)",
      "-l$(TBB_MALLOC_NAME)"
   )

}


# on Windows, link to ssp for the stack-protector helpers (__stack_chk_fail
# and friends), which mingw does not provide in libgcc
if (.Platform$OS.type == "windows") {
   pkgLibs <- c(pkgLibs, "-lssp")
}

define(PKG_LIBS = paste(pkgLibs, collapse = " "))
   

# now, set up PKG_CPPFLAGS
if (!is.na(tbbLib)) {
   define(PKG_CPPFLAGS = "-I../inst/include -I\"$(TBB_INC)\"")
} else {
   define(PKG_CPPFLAGS = "-I../inst/include")
}

# PKG_CXXFLAGS
#
# TBB is always enabled: either one was supplied via TBB_LIB / TBB_ROOT, or we
# built the bundled copy, and failing to do either is fatal above
define(TBB_ENABLED = TRUE)
define(PKG_CXXFLAGS = "-DRCPP_PARALLEL_USE_TBB=1")

# macOS needs some extra flags set
if (Sys.info()[["sysname"]] == "Darwin") {
   define(PKG_LIBS_EXTRA = "-Wl,-rpath,@loader_path/../lib")
} else if (Sys.info()[["sysname"]] == "Linux") {
   define(PKG_LIBS_EXTRA = "-Wl,-rpath,$(ORIGIN)/../lib")
} else {
   define(PKG_LIBS_EXTRA = "")
   
}
