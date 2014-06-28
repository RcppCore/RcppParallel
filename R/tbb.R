

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
   dll <- system.file(paste("lib/libtbb", ext, sep = ""), package = "tbb")
   dllInfo <<- dyn.load(dll, local = FALSE, now = TRUE)
   
   # load the tbb package library
   library.dynam("tbb", pkgname, libname)
   
   # set default thread options
   setThreadOptions()
}

.onUnload <- function(libpath) {
   
   # unload the tbb package library
   library.dynam.unload("tbb", libpath)
   
   # unload tbb
   dyn.unload(dllInfo[["path"]])
}

setThreadOptions <- function(numThreads = "auto", threadStackSize = "auto") {
   
   # validate and resolve numThreads
   if (identical(numThreads, "auto"))
      numThreads <- -1L
   else if (!is.numeric(numThreads))
      stop("numThreads must be an integer")
   else
      numThreads <- as.integer(numThreads)
   
   # validate and resolve threadStackSize
   if (identical(threadStackSize, "auto"))
      threadStackSize = 0L
   else if (!is.numeric(threadStackSize))
      stop("threadStackSize must be an integer")
   else
      threadStackSize <- as.integer(threadStackSize)
   
   invisible(.Call("setThreadOptions", numThreads, threadStackSize, 
                   PACKAGE = "tbb"))
}

defaultNumThreads <- function() {
   .Call("defaultNumThreads", PACKAGE = "tbb")
}

