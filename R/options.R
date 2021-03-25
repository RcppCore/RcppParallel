
#' Thread options for RcppParallel
#' 
#' Set thread options (number of threads to use for task scheduling and stack
#' size per-thread) for RcppParallel.
#' 
#' RcppParallel is automatically initialized with the default number of threads
#' and thread stack size when it loads. You can call `setThreadOptions()` at
#' any time to change the defaults.
#' 
#' The `parallelFor()` and `parallelReduce()` also accept `numThreads` as
#' an argument, if you'd like to control the number of threads specifically
#' to be made available for a particular parallel function call. Note that
#' this value is advisory, and TBB may choose a smaller number of threads
#' if the number of requested threads cannot be honored on the system.
#' 
#' @aliases setThreadOptions defaultNumThreads
#' 
#' @param numThreads
#'   Number of threads to use for task scheduling. Call `defaultNumThreads()`
#'   to determine the the default value used for "auto".
#'   
#' @param stackSize
#'   Stack size (in bytes) to use for worker threads. The
#'   default used for "auto" is 2MB on 32-bit systems and 4MB on 64-bit systems
#'   (note that this parameter has no effect on Windows).
#'   
#' @return
#'   `defaultNumThreads()` returns the default number of threads used by
#'   RcppParallel, if another value isn't specified either via
#'   `setThreadOptions()` or explicitly in calls to `parallelFor()` and
#'   `parallelReduce()`.
#'
#' @examples
#' 
#' \dontrun{
#' library(RcppParallel)
#' setThreadOptions(numThreads = 4)
#' defaultNumThreads()
#' }
#' 
#' @export setThreadOptions
setThreadOptions <- function(numThreads = "auto",
                             stackSize = "auto")
{
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

#' @rdname setThreadOptions
#' @export
defaultNumThreads <- function() {
   .Call("defaultNumThreads", PACKAGE = "RcppParallel")
}

isUsingTbb <- function() {
   backend <- Sys.getenv("RCPP_PARALLEL_BACKEND", "tbb")
   identical(backend, "tbb")
}

