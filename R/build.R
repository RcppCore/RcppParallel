


inlineCxxPlugin <- function() {

   # For sourceCpp on Windows we need to explicitly link against tbb.dll
   if (Sys.info()['sysname'] == "Windows") {
      tbb <- tbbLibPath()
      pkgLibs <- paste("-L", asBuildPath(dirname(tbb)), 
                       " -ltbb", sep="")
      env <- list(PKG_LIBS = pkgLibs)
   } else {
      env <- list() 
   }
   
   list(
      env = env,
      includes = "#include <RcppParallel.h>",
      LinkingTo = "RcppParallel",
      body = function( x ) x,
      Depends = "RcppParallel"
   )
}


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

asBuildPath <- function(path) {
   
   if (.Platform$OS.type == "windows") {
      path <- normalizePath(path)
      if (grepl(' ', path, fixed=TRUE))
         path <- utils::shortPathName(path)
      path <- gsub("\\\\", "/", path)
   }
   
   return(path)
}
