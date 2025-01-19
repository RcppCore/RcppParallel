
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
         status <- system("R CMD SHLIB tbb-compat/tbb-compat.cpp")
         if (status != 0)
            stop("error building tbb stub library")
         file.rename("tbb-compat/tbb-compat.dll", file.path(tbbDest, "tbb.dll"))
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
   
   cxxFlags <- paste(Sys.getenv("CPPFLAGS", "CXXFLAGS", "CXXPICFLAGS"), collapse = " ")
   Sys.setenv(CXXFLAGS = cxxFlags)

   cmakeFlags <- c(
      sprintf("-DCMAKE_BUILD_TYPE=%s", buildType),
      "-DTBB_TEST=0",
      "-DTBB_EXAMPLES=0",
      "-DTBB_STRICT=0",
      ".."
   )
   
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
   
   tbbFiles <- list.files(
      file.path(getwd(), "tbb/build-tbb"),
      pattern = shlibPattern,
      recursive = TRUE,
      full.names = TRUE
   )
   
   dir.create("tbb/build/lib_release", recursive = TRUE, showWarnings = FALSE)
   file.copy(tbbFiles, "tbb/build/lib_release", overwrite = TRUE)
   unlink("tbb/build-tbb", recursive = TRUE)
   writeLines("*** finished building tbb")
   
}

useOldBundledTbb <- function() {
   
   useTbbPreamble("tbb-2019/include")
   owd <- setwd("tbb-2019/src")
   on.exit(setwd(owd), add = TRUE)
   
   makeArgs <- "stdver=c++11"
   cxxFlags <- c(
      "-DTBB_NO_LEGACY=1",
      "-DTBB_SUPPRESS_DEPRECATED_MESSAGES=1",
      Sys.getenv(c("CPPFLAGS", "CXXFLAGS"))
   )
   
   cxxFlags <- paste(cxxFlags, collapse = " ")
   Sys.setenv(
      CONLY    = Sys.getenv("CC", unset = "cc"),
      CPLUS    = Sys.getenv("CXX", unset = "c++"),
      CXXFLAGS = paste(cxxFlags, collapse = " "),
      PIC_KEY  = Sys.getenv("CXXPICFLAGS", unset = "-fPIC"),
      WARNING_SUPPRESS = ""
   )
   
   if (.Platform$OS.type == "windows") {
      
      Sys.setenv(
         MSYS2_ARG_CONV_EXCL = "*",
         CYGWIN = "nodosfilewarning",
         WINARM64_CLANG = "$(WINARM64_CLANG)"
      )
      
      makeArgs <- "rtools=true compiler=gcc runtime=mingw"

   }
   
   writeLines("** configuring tbb")
   system("make info")
   writeLines("")
   
   writeLines("** building tbb")
   makeTargets <- c("tbb_build_prefix=lib", "tbb_release", "tbbmalloc_release")
   output <- system2("make", c("-e", makeArgs, makeTargets), stdout = TRUE, stderr = TRUE)
   status <- attr(output, "status")
   if (!is.null(status) && status != 0) {
      writeLines(output, con = stderr())
      stop("error building tbb")
   }
   
   shlibPattern <- switch(
      Sys.info()[["sysname"]],
      Windows = "^tbb.*\\.dll$",
      Darwin  = "^libtbb.*\\.dylib$",
      "^libtbb.*\\.so.*$"
   )
   
   setwd(owd)
   tbbFiles <- list.files(
      file.path(getwd(), "tbb-2019/build/lib_release"),
      pattern = shlibPattern,
      recursive = TRUE,
      full.names = TRUE
   )
   
   dir.create("tbb/build/lib_release", recursive = TRUE, showWarnings = FALSE)
   file.copy(tbbFiles, "tbb/build/lib_release", overwrite = TRUE)
   unlink("tbb/build-tbb", recursive = TRUE)
   writeLines("** finished building tbb")

}


# Main ----

tbbSrc <- Sys.getenv("TBB_SRC")
tbbLib <- Sys.getenv("TBB_LIB")
tbbInc <- Sys.getenv("TBB_INC")

args <- commandArgs(trailingOnly = TRUE)
if (identical(args, "build")) {
   if (nzchar(tbbLib) && nzchar(tbbInc)) {
      useSystemTbb(tbbLib, tbbInc)
   } else if (tbbSrc == "tbb") {
      useBundledTbb()
   } else if (tbbSrc == "tbb-2019") {
      useOldBundledTbb()
   }
} else {
   source("../R/tbb-autodetected.R")
   .install.libs(tbbLib)
}
