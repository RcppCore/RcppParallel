

dllInfo <- NULL

.onLoad <- function(libname, pkgname) {

   # load tbb if we aren't on windows
   sysname <- Sys.info()['sysname']
   if (sysname %in% c("Linux", "Darwin")) {
     if (sysname == "Darwin")
        ext = ".dylib"
     else if (sysname == "Linux")
        ext = ".so.2"
     dll <- system.file(paste("lib/libtbb", ext, sep = ""), package = "RcppParallel")
     dllInfo <<- dyn.load(dll, local = FALSE, now = TRUE)
   }
   
   # load the package library
   library.dynam("RcppParallel", pkgname, libname)
   
   # set default thread options
   setThreadOptions()
}

.onUnload <- function(libpath) {
   
   # unload the package library
   library.dynam.unload("RcppParallel", libpath)
   
   # unload tbb if we loaded it (i.e. aren't on windows)
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
   
   if (Sys.info()['sysname'] %in% c("Linux", "Darwin")) {
      invisible(.Call("setThreadOptions", numThreads, stackSize, 
                      PACKAGE = "RcppParallel"))
   } 
   
   if (numThreads != -1)
      Sys.setenv(RCPP_PARALLEL_NUM_THREADS = numThreads)
}

defaultNumThreads <- function() {
   .Call("defaultNumThreads", PACKAGE = "RcppParallel")
}

