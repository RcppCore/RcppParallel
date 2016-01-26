

# Output the CXX flags. These flags are propagated to sourceCpp via the 
# inlineCxxPlugin (defined below) and to packages via a line in Makevars[.win]
# like this:
#
#  PKG_CXXFLAGS += $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "RcppParallel::CxxFlags()")
#
CxxFlags <- function() {
   cat(tbbCxxFlags())
}


# Output the LD flags for building against TBB. These flags are propagated
# to sourceCpp via the inlineCxxPlugin (defined below) and to packages 
# via a line in Makevars[.win] like this:
#
#   PKG_LIBS += $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "RcppParallel::LdFlags()")
#
LdFlags <- function() {
   cat(tbbLdFlags())
}

# alias for backward compatibility
RcppParallelLibs <- function() {
   LdFlags()
}

# Inline plugin used by sourceCpp.
inlineCxxPlugin <- function() {
   list(
      env = list(
         PKG_CXXFLAGS = tbbCxxFlags(),
         PKG_LIBS = tbbLdFlags()
      ),
      includes = "#include <RcppParallel.h>",
      LinkingTo = "RcppParallel",
      body = function(x) x,
      Depends = "RcppParallel"
   )
}

tbbCxxFlags <- function() {
   
   flags <- c()
   
   # opt-in to TBB on Windows
   if (Sys.info()['sysname'] == "Windows")
      flags <- paste(flags, "-DRCPP_PARALLEL_USE_TBB=1")
   
   flags
}

# Return the linker flags requried for TBB on this platform
tbbLdFlags <- function() {
   # on Windows and Solaris we need to explicitly link against tbb.dll
   if ((Sys.info()['sysname'] %in% c("Windows", "SunOS")) && !isSparc()) {
      tbb <- tbbLibPath()
      paste("-L", asBuildPath(dirname(tbb)), " -ltbb -ltbbmalloc", sep = "")
   } else {
      ""
   }
}

# Determine the platform-specific path to the TBB library
tbbLibPath <- function(suffix = "") {
   sysname <- Sys.info()['sysname']
   tbbSupported <- list(
      "Darwin" = paste("libtbb", suffix, ".dylib", sep = ""), 
      "Linux" = paste("libtbb", suffix, ".so.2", sep = ""), 
      "Windows" = paste("tbb", suffix, ".dll", sep = ""),
      "SunOS" = paste("libtbb", suffix, ".so", sep = "")
   )
   if ((sysname %in% names(tbbSupported)) && !isSparc()) {
      libDir <- "lib/"
      if (sysname == "Windows")
         libDir <- paste(libDir, .Platform$r_arch, "/", sep="")
      system.file(paste(libDir, tbbSupported[[sysname]], sep = ""), 
                  package = "RcppParallel")
   } else {
      NULL
   }
}

isSparc <- function() {
   Sys.info()['sysname'] == "SunOS" && Sys.info()[["machine"]] != "i86pc"
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
