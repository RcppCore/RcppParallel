
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
      useSymlinks <- Sys.getenv("TBB_USE_SYMLINKS", unset = "TRUE")
      if (useSymlinks) {
         file.symlink(tbbLibs, tbbDest)
      } else {
         for (tbbLib in tbbLibs) {
            system2("cp", c("-P", shQuote(tbbLib), shQuote(tbbDest)))
         }
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
      "tbb/build-tbb",
      pattern = shlibPattern,
      recursive = TRUE,
      full.names = TRUE
   )
   
   tbbDir <- dirname(tbbFiles[[1L]])
   
   dir.create("tbb/build", showWarnings = FALSE)
   unlink("tbb/build/lib_release", recursive = TRUE)
   file.rename(tbbDir, "tbb/build/lib_release")
   unlink("tbb/build-tbb", recursive = TRUE)
   writeLines("*** finished building tbb")
   
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
   source("../R/tbb-autodetected.R")
   .install.libs(tbbLib)
}
