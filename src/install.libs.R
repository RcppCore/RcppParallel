
# !diagnostics suppress=R_PACKAGE_DIR,SHLIB_EXT,R_ARCH
.install.libs <- function(tbbLib) {

   # copy default library
   files <- Sys.glob(paste0("*", SHLIB_EXT))
   dest <- file.path(R_PACKAGE_DIR, paste0("libs", R_ARCH))
   dir.create(dest, recursive = TRUE, showWarnings = FALSE)
   file.copy(files, dest, overwrite = TRUE)

   # copy symbols if available
   if (file.exists("symbols.rds"))
      file.copy("symbols.rds", dest, overwrite = TRUE)

   # also copy to package 'libs' folder, for devtools
   libsDest <- paste0("../libs", R_ARCH)
   dir.create(libsDest, recursive = TRUE, showWarnings = FALSE)
   file.copy(files, libsDest, overwrite = TRUE)

   # copy tbb (NOTE: do not use inst/ folder as R will resolve symlinks,
   # behavior which we do _not_ want here!)
   tbbDest <- file.path(R_PACKAGE_DIR, paste0("lib", R_ARCH))
   dir.create(tbbDest, recursive = TRUE, showWarnings = FALSE)

   # note: on Linux, TBB gets compiled with extensions like
   # '.so.2', so be ready to handle those
   shlibPattern <- switch(
      Sys.info()[["sysname"]],
      Windows = "^tbb.*\\.dll$",
      Darwin  = "^libtbb.*\\.dylib$",
      "^libtbb.*\\.so.*$"
   )
   # WASM only supports static libraries
   if (R.version$os == "emscripten") {
      shlibPattern <- "^libtbb.*\\.a$"
   }

   if (!nzchar(tbbLib)) {

      # using bundled TBB
      tbbLibs <- list.files(
         path       = "tbb/build/lib_release",
         pattern    = shlibPattern,
         full.names = TRUE
      )

      for (tbbLib in tbbLibs) {
         system2("cp", c("-P", shQuote(tbbLib), shQuote(tbbDest)))
      }

   } else {

      # using system tbb
      tbbLibs <- list.files(
         path       = tbbLib,
         pattern    = shlibPattern,
         full.names = TRUE
      )

      # don't copy symlinks
      tbbLibs <- tbbLibs[!nzchar(Sys.readlink(tbbLibs))]

      # copy / link the libraries
      useSymlinks <- Sys.getenv("TBB_USE_SYMLINKS", unset = .Platform$OS.type != "windows")
      if (useSymlinks) {
         file.symlink(tbbLibs, tbbDest)
      } else {
         for (tbbLib in tbbLibs) {
            system2("cp", c("-P", shQuote(tbbLib), shQuote(tbbDest)))
         }
      }

   }

   # on Windows, we create a stub library that links to us so that
   # older binaries (like rstan) can still load
   if (.Platform$OS.type == "windows") {
      tbbDll <- file.path(tbbDest, "tbb.dll")
      if (!file.exists(tbbDll)) {
         writeLines("** creating tbb stub library")
         status <- system("R CMD SHLIB -o tbb-compat/tbb.dll tbb-compat/tbb-compat.cpp")
         if (status != 0)
            stop("error building tbb stub library")
         file.copy("tbb-compat/tbb.dll", file.path(tbbDest, "tbb.dll"))
      }
   }

}

useTbbPreamble <- function(tbbInc) {

   dir.create("../inst/include", recursive = TRUE, showWarnings = FALSE)
   for (suffix in c("oneapi", "serial", "tbb")) {
      tbbPath <- file.path(tbbInc, suffix)
      if (file.exists(tbbPath)) {
         file.copy(tbbPath, "../inst/include", recursive = TRUE)
      }
   }

   patchTbbMachineHeader("../inst/include/oneapi/tbb/detail/_machine.h")

}

# Guard the '#include <intrin.h>' in TBB's _machine.h against GCC's
# <cpuid.h> macro on mingw. The headers we ship may come from Rtools
# rather than from the bundled copy of oneTBB, so the guard must be
# applied to the copied headers, not just the bundled sources.
patchTbbMachineHeader <- function(path) {

   if (!file.exists(path))
      return()

   contents <- readLines(path)
   if (any(grepl("push_macro", contents, fixed = TRUE)))
      return()

   index <- which(contents == "#include <intrin.h>")
   if (length(index) != 1L)
      return()

   replacement <- c(
      "// GCC's <cpuid.h> defines a function-like '__cpuid' macro that mangles the",
      "// __cpuid() declarations in mingw's <intrin.h>. Hide the macro while",
      "// including <intrin.h> so the two headers can coexist in any order.",
      "#if defined(__MINGW32__) && defined(__cpuid)",
      "#pragma push_macro(\"__cpuid\")",
      "#undef __cpuid",
      "#include <intrin.h>",
      "#pragma pop_macro(\"__cpuid\")",
      "#else",
      "#include <intrin.h>",
      "#endif"
   )

   contents <- append(contents[-index], replacement, after = index - 1L)
   writeLines(contents, path)

}

useSystemTbb <- function(tbbLib, tbbInc) {
   useTbbPreamble(tbbInc)
}

useBundledTbb <- function() {

   useTbbPreamble("tbb/include")
   dir.create("tbb/build-tbb", showWarnings = FALSE)

   cmake <- Sys.getenv("CMAKE", unset = "cmake")
   buildType <- Sys.getenv("CMAKE_BUILD_TYPE", unset = "Release")
   verbose <- Sys.getenv("VERBOSE", unset = "0")

   splitCompilerVar("CC", "CFLAGS")
   splitCompilerVar("CXX", "CXXFLAGS")

   prependFlags("CPPFLAGS", "CFLAGS")
   prependFlags("CPPFLAGS", "CXXFLAGS")

   # the ucontext APIs (getcontext, swapcontext, ...) are deprecated on macOS,
   # so use the threads-based coroutine implementation for resumable tasks
   if (Sys.info()[["sysname"]] == "Darwin") {
      flags <- c(Sys.getenv("CXXFLAGS"), "-D__TBB_RESUMABLE_TASKS_USE_THREADS=1")
      setenv("CXXFLAGS", flags[nzchar(flags)])
   }

   cmakeFlags <- c(
      forwardEnvVar("CC", "CMAKE_C_COMPILER"),
      forwardEnvVar("CXX", "CMAKE_CXX_COMPILER"),
      forwardEnvVar("CFLAGS", "CMAKE_C_FLAGS"),
      forwardEnvVar("CXXFLAGS", "CMAKE_CXX_FLAGS"),
      forwardEnvVar("CMAKE_BUILD_TYPE", "CMAKE_BUILD_TYPE"),
      # tbbbind requires hwloc, and hwloc's pkg-config file doesn't advertise
      # the macOS frameworks needed when linking it statically; RcppParallel
      # doesn't use TBB's NUMA APIs, so skip tbbbind altogether
      "-DTBB_DISABLE_HWLOC_AUTOMATIC_SEARCH=1",
      "-DTBB_TEST=0",
      "-DTBB_EXAMPLES=0",
      "-DTBB_STRICT=0",
      ".."
   )

   if (R.version$os == "emscripten") {
      cmakeFlags <- c(
         "-DEMSCRIPTEN=1",
         "-DTBBMALLOC_BUILD=0",
         "-DBUILD_SHARED_LIBS=0",
         cmakeFlags
      )
   }

   writeLines("*** configuring tbb")
   owd <- setwd("tbb/build-tbb")
   output <- system2(cmake, shQuote(cmakeFlags), stdout = TRUE, stderr = TRUE)
   status <- attr(output, "status")
   if (is.numeric(status) && status != 0L) {
      writeLines(output)
      stop("error configuring tbb (status code ", status, ")")
   } else if (!identical(verbose, "0")) {
      writeLines(output)
   }
   setwd(owd)

   if (!identical(verbose, "0")) {
      writeLines("*** dumping CMakeCache.txt")
      writeLines(readLines("tbb/build-tbb/CMakeCache.txt"))
   }

   writeLines("*** building tbb")
   owd <- setwd("tbb/build-tbb")
   output <- system2(cmake, c("--build", ".", "--config", "release"), stdout = TRUE, stderr = TRUE)
   status <- attr(output, "status")
   if (is.numeric(status) && status != 0L) {
      writeLines(output)
      stop("error building tbb (status code ", status, ")")
   } else if (!identical(verbose, "0")) {
      writeLines(output)
   }
   setwd(owd)

   shlibPattern <- switch(
      Sys.info()[["sysname"]],
      Windows = "^tbb.*\\.dll$",
      Darwin  = "^libtbb.*\\.dylib$",
      "^libtbb.*\\.so.*$"
   )

   # WASM only supports static libraries
   if (R.version$os == "emscripten") {
      shlibPattern <- "^libtbb.*\\.a$"
   }

   tbbFiles <- list.files(
      file.path(getwd(), "tbb/build-tbb"),
      pattern = shlibPattern,
      recursive = TRUE,
      full.names = TRUE
   )

   # clear any artifacts from prior builds, so that we only ship
   # the libraries produced by the build above
   unlink("tbb/build/lib_release", recursive = TRUE)

   dir.create("tbb/build/lib_release", recursive = TRUE, showWarnings = FALSE)
   file.copy(tbbFiles, "tbb/build/lib_release", overwrite = TRUE)
   unlink("tbb/build-tbb", recursive = TRUE)
   writeLines("*** finished building tbb")

}

getenv <- function(key, unset = "") {
   Sys.getenv(key, unset = unset)
}


setenv <- function(key, value) {
   args <- list(paste(value, collapse = " "))
   names(args) <- key
   do.call(Sys.setenv, args)
}


# CMake doesn't support flags specified directly as part of the compiler
# definition, so manually split it here.
splitCompilerVar <- function(compilerVar, flagsVar) {

   compiler <- Sys.getenv(compilerVar, unset = NA)
   if (is.na(compiler))
      return(FALSE)

   tokens <- scan(text = compiler, what = character(), quiet = TRUE)
   if (length(tokens) < 2L)
      return(FALSE)

   setenv(compilerVar, tokens[[1L]])

   oldFlags <- Sys.getenv(flagsVar)
   newFlags <- c(tokens[-1L], oldFlags)
   setenv(flagsVar, newFlags[nzchar(newFlags)])

   TRUE

}


# Given an environment variable like 'CC', forward that to CMake
# via the corresponding CMAKE_C_COMPILER flag.
forwardEnvVar <- function(envVar, cmakeVar) {
   envVal <- Sys.getenv(envVar, unset = NA)
   if (!is.na(envVal)) {
      sprintf("-D%s=%s", cmakeVar, envVal)
   }
}

prependFlags <- function(prependFlags, toFlags) {

   prependVal <- Sys.getenv(prependFlags, unset = NA)
   if (is.na(prependVal))
      return(FALSE)

   oldVal <- Sys.getenv(toFlags, unset = NA)
   if (is.na(oldVal)) {
      setenv(toFlags, prependVal)
   } else {
      setenv(toFlags, paste(prependVal, oldVal))
   }

   TRUE

}

# Main ----

tbbLib <- Sys.getenv("TBB_LIB")
tbbInc <- Sys.getenv("TBB_INC")

args <- commandArgs(trailingOnly = TRUE)
if (identical(args, "build")) {
   if (nzchar(tbbLib) && nzchar(tbbInc)) {
      useSystemTbb(tbbLib, tbbInc)
   } else if (.Platform$OS.type == "windows") {
      writeLines("** building RcppParallel without tbb backend")
   } else {
      useBundledTbb()
   }
} else {

   # prefer the configure-detected TBB_LIB when the environment variable
   # is unset; otherwise, e.g. on Windows (where configure detects the
   # Rtools copy of TBB), we'd wrongly take the bundled-TBB branch below,
   # and ship any stale artifacts present in tbb/build/lib_release
   source("../R/tbb-autodetected.R")
   if (!nzchar(tbbLib))
      tbbLib <- TBB_LIB

   .install.libs(tbbLib)

}
