

dllInfo <- NULL

.onLoad <- function(libname, pkgname) {

   # load tbb on supported platforms   
   sysname <- Sys.info()['sysname']
   tbbSupported <- list(
     "Darwin" = "libtbb.dylib", "Linux" = "libtbb.so.2", "Windows" = "tbb.dll"
   )
   if (sysname %in% names(tbbSupported)) {
     dll <- system.file(paste("lib/", tbbSupported[[sysname]], sep = ""), package = "RcppParallel")
     if (!file.exists(dll)) {
       warning(paste("TBB library", dll, "not found."))
     } else {
       dllInfo <<- dyn.load(dll, local = FALSE, now = TRUE)
     }
   }
   
   # load the package library
   library.dynam("RcppParallel", pkgname, libname)
   
   # set default thread options
   setThreadOptions()
}

.onUnload <- function(libpath) {
   
   # unload the package library
   library.dynam.unload("RcppParallel", libpath)
   
   # unload tbb if we loaded it
   if (!is.null(dllInfo))
      dyn.unload(dllInfo[["path"]])
}

setThreadOptions <- function(numThreads = "auto", stackSize = "auto") {
   
   # validate and resolve numThreads
   if (identical(numThreads, "auto"))
      numThreads <- -1L
   else if (!is.numeric(numThreads))
      stop("numThreads must be an integer")
   else
      numThreads <- as.integer(numThreads)
   
   # validate and resolve stackSize
   if (identical(stackSize, "auto"))
      stackSize = 0L
   else if (!is.numeric(stackSize))
      stop("stackSize must be an integer")
   else
      stackSize <- as.integer(stackSize)
   
   # Call setThreadOptions if using tbb
   if (!is.null(dllInfo)) {
      invisible(.Call("setThreadOptions", numThreads, stackSize, 
                      PACKAGE = "RcppParallel"))
   } 
   
   if (numThreads != -1)
      Sys.setenv(RCPP_PARALLEL_NUM_THREADS = numThreads)
}

defaultNumThreads <- function() {
   .Call("defaultNumThreads", PACKAGE = "RcppParallel")
}

