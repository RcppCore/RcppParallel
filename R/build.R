

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
   
   env <- list(
      PKG_CXXFLAGS = tbbCxxFlags(),
      PKG_LIBS = tbbLdFlags()
   )
   
   list(
      env       = env,
      body      = identity,
      includes  = "#include <RcppParallel.h>",
      LinkingTo = "RcppParallel",
      Depends   = "RcppParallel"
   )
   
}

tbbCxxFlags <- function() {

   flags <- character()

   # opt-in to TBB on Windows
   if (is_windows())
      flags <- c(flags, "-DRCPP_PARALLEL_USE_TBB=1")
   
   # if TBB_INC is set, apply those library paths
   tbbInc <- Sys.getenv("TBB_INC", unset = NA)
   if (!is.na(tbbInc)) {
      
      # add include path
      flags <- c(flags, paste0("-I", shQuote(asBuildPath(tbbInc))))
      
      # prefer new interface if version.h exists
      versionPath <- file.path(tbbInc, "tbb/version.h")
      if (file.exists(versionPath))
         flags <- c(flags, "-DTBB_INTERFACE_NEW")
      
   }

   # return flags as string
   paste(flags, collapse = " ")
   
}

# Return the linker flags requried for TBB on this platform
tbbLdFlags <- function() {
   
   # shortcut if TBB_LIB defined
   tbbLib <- Sys.getenv("TBB_LIB", unset = NA)
   if (!is.na(tbbLib)) {
      fmt <- "-L%1$s -Wl,-rpath,%1$s -ltbb -ltbbmalloc"
      return(sprintf(fmt, asBuildPath(tbbLib)))
   }
   
   # on Windows and Solaris, we need to explicitly link
   needsExplicitFlags <- is_windows() || (is_solaris() && !is_sparc())
   if (needsExplicitFlags) {
      libPath <- asBuildPath(dirname(tbbLibPath()))
      libFlag <- paste0("-L", shQuote(libPath))
      return(paste(libFlag, "-ltbb", "-ltbbmalloc"))
   }
   
   # nothing required on other platforms
   ""
   
}

# Determine the platform-specific path to the TBB library
tbbLibPath <- function(suffix = "") {
   
   # library paths for different OSes
   sysname <- Sys.info()[["sysname"]]
   
   tbbLibNames <- list(
      "Darwin"  = paste0("libtbb", suffix, ".dylib"),
      "Windows" = paste0("tbb",    suffix, ".dll"),
      "SunOS"   = paste0("libtbb", suffix, ".so"),
      "Linux"   = paste0("libtbb", suffix, c(".so", ".so.2"))
   )

   # shortcut if TBB_LIB is defined
   tbbLib <- Sys.getenv("TBB_LIB", unset = NA)
   if (!is.na(tbbLib)) {
      libPaths <- file.path(tbbLib, tbbLibNames[[sysname]])
      for (libPath in libPaths)
         if (file.exists(libPath))
            return(asBuildPath(libPath))
   }
   
   # otherwise, construct library path as appropriate for arch
   isCompatible <-
      !is_sparc() &&
      !is.null(tbbLibNames[[sysname]])
   
   if (!isCompatible)
      return(NULL)
   
   # construct library path
   arch <- .Platform$r_arch
   components <- c("lib", if (nzchar(arch)) arch)
   libDir <- paste(components, collapse = "/")
   
   # form path to bundled tbb component
   libNames <- tbbLibNames[[sysname]]
   for (libName in libNames) {
      tbbName <- file.path(libDir, libName)
      tbbPath <- system.file(tbbName, package = "RcppParallel")
      if (file.exists(tbbPath))
         return(tbbPath)
   }

}

# Helper function to ape the behavior of the R build system
# when providing paths to libraries
asBuildPath <- function(path) {
   
   # nothing to do for non-Windows
   if (!is_windows())
      return(path)
   
   # normalize paths using forward slashes
   path <- normalizePath(path, winslash = "/", mustWork = FALSE)
   
   # prefer short path names if the path has spaces
   if (grepl(" ", path, fixed = TRUE))
      path <- utils::shortPathName(path)
   
   # return path
   return(path)
}
