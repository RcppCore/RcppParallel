

# Output the LD flags for building against TBB. These flags are propagated
# to sourceCpp via the inlineCxxPlugin (defined below) and to packages 
# via a line in Makevars.win like this:
#
#   PKG_LIBS += $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "RcppParallel::LdFlags()")
#
# Note that this is only required for Windows builds (on Linux and OS X no 
# explicit link to TBB is required).
RcppParallelLibs <- function() {
   cat(tbbLdFlags())
}


# Inline plugin used by sourceCpp to link to the TBB library
inlineCxxPlugin <- function() {
   list(
      env = list(
         PKG_CXXFLAGS = "-DRCPP_PARALLEL_USE_TBB=1",
         PKG_LIBS = tbbLdFlags()
      ),
      includes = "#include <RcppParallel.h>",
      LinkingTo = "RcppParallel",
      body = function( x ) x,
      Depends = "RcppParallel"
   )
}


# Return the linker flags requried for TBB on this platform
tbbLdFlags <- function() {
   # on Windows we need to explicitly link against tbb.dll
   if (Sys.info()['sysname'] == "Windows") {
      tbb <- tbbLibPath()
      paste("-L", asBuildPath(dirname(tbb)), " -ltbb", sep="")
   } else {
      ""
   }
}


# Determine the platform-specific path to the TBB library
tbbLibPath <- function() {
   sysname <- Sys.info()['sysname']
   tbbSupported <- list(
      "Darwin" = "libtbb.dylib", 
      "Linux" = "libtbb.so.2", 
      "Windows" = "tbb.dll"
   )
   if (sysname %in% names(tbbSupported)) {
      libDir <- "lib/"
      if (sysname == "Windows")
         libDir <- paste(libDir, .Platform$r_arch, "/", sep="")
      system.file(paste(libDir, tbbSupported[[sysname]], sep = ""), 
                  package = "RcppParallel")
   } else {
      NULL
   }
}


# Helper function to ape the behavior of the R build system
# when providing paths to libraries
asBuildPath <- function(path) {
   if (.Platform$OS.type == "windows") {
      path <- normalizePath(path)
      if (grepl(' ', path, fixed=TRUE))
         path <- utils::shortPathName(path)
      path <- gsub("\\\\", "/", path)
   }
   return(path)
}
