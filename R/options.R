
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
   
   # set RCPP_PARALLEL_NUM_THREADS
   if (numThreads == -1L)
      Sys.unsetenv("RCPP_PARALLEL_NUM_THREADS")
   else
      Sys.setenv(RCPP_PARALLEL_NUM_THREADS = numThreads)
   
   # set RCPP_PARALLEL_STACK_SIZE
   if (stackSize == 0L)
      Sys.unsetenv("RCPP_PARALLEL_STACK_SIZE")
   else
      Sys.setenv(RCPP_PARALLEL_STACK_SIZE = stackSize)
   
}

defaultNumThreads <- function() {
   .Call("defaultNumThreads", PACKAGE = "RcppParallel")
}
