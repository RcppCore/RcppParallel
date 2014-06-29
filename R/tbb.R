

dllInfo <- NULL

.onLoad <- function(libname, pkgname) {
   
   # load tbb and make it's symbols available globally
   sysname <- Sys.info()['sysname']
   if (sysname == "Darwin")
      ext = ".dylib"
   else if (sysname == "Linux")
      ext = ".so.2"
   else if (sysname == "Windows")
      ext = ".dll"
   else
      ext = .Platform$dynlib.ext
   dll <- system.file(paste("lib/libtbb", ext, sep = ""), package = "TBB")
   dllInfo <<- dyn.load(dll, local = FALSE, now = TRUE)
   
   # load the tbb package library
   library.dynam("TBB", pkgname, libname)
   
   # set default thread options
   setThreadOptions()
}

.onUnload <- function(libpath) {
   
   # unload the tbb package library
   library.dynam.unload("TBB", libpath)
   
   # unload tbb
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
   
   invisible(.Call("setThreadOptions", numThreads, stackSize, PACKAGE = "TBB"))
}

defaultNumThreads <- function() {
   .Call("defaultNumThreads", PACKAGE = "TBB")
}

