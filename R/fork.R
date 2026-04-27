#' Is the Current Process a Forked Child?
#'
#' Returns `TRUE` if the current process is a `fork()` of the process in which
#' RcppParallel was originally loaded.
#'
#' Intel TBB — the parallel backend used by `parallelFor()` and
#' `parallelReduce()` — does not support being used in a child process after
#' `fork()`. Packages that may be invoked from within `parallel::mclapply()`
#' or similar fork-based parallelism should call `isForkedChild()` and fall
#' back to a serial code path when it returns `TRUE`.
#'
#' On Windows, which has no `fork()`, this always returns `FALSE`.
#'
#' @return A length-one logical.
#'
#' @examples
#' \dontrun{
#' library(RcppParallel)
#' isForkedChild()
#' parallel::mclapply(1:2, function(i) RcppParallel::isForkedChild())
#' }
#'
#' @export
isForkedChild <- function() {
   .Call("isForkedChild", PACKAGE = "RcppParallel")
}
