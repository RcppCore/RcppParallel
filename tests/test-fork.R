# Unit tests for isProcessForkedChild().
#
# The contract: it returns FALSE in the process where RcppParallel was loaded,
# and TRUE in a fork() of that process (e.g. a parallel::mclapply worker). On
# Windows there is no fork(), so it always returns FALSE.

RcppParallel:::test_init()

# in the parent process, we are never a forked child
assert(isProcessForkedChild() == FALSE)

# parallel::mclapply uses fork() on unix, so its workers must report TRUE.
# on Windows there is no fork() (mclapply falls back to serial), so skip: the
# workers there run in the parent process and would correctly report FALSE.
if (!is_windows()) {

   results <- parallel::mclapply(1:2, function(i) {
      RcppParallel::isProcessForkedChild()
   }, mc.cores = 2L)

   assert(all(vapply(results, isTRUE, logical(1L))))

}

# forking must not disturb the parent's own view of itself
assert(isProcessForkedChild() == FALSE)
