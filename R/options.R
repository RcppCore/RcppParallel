
isUsingTbb <- function() {
   backend <- Sys.getenv("RCPP_PARALLEL_BACKEND", "tbb")
   identical(backend, "tbb")
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
      stackSize <- 0L
   else if (!is.numeric(stackSize))
      stop("stackSize must be an integer")
   else
      stackSize <- as.integer(stackSize)
   
   # Call setThreadOptions if using tbb
   if (!is.null(dllInfo) && isUsingTbb())
      setTbbThreadOptions(numThreads, stackSize)
   
   if (numThreads == -1L)
      Sys.unsetenv("RCPP_PARALLEL_NUM_THREADS")
   else
      Sys.setenv(RCPP_PARALLEL_NUM_THREADS = numThreads)
}

setTbbThreadOptions <- function(numThreads, stackSize) {
   .Call(
      "setThreadOptions",
      as.integer(numThreads),
      as.integer(stackSize),
      PACKAGE = "RcppParallel"
   )
}

defaultNumThreads <- function() {
   .Call(
      "defaultNumThreads",
      PACKAGE = "RcppParallel"
   )
}
