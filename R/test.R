# Minimal test helpers used by the package's own test scripts in tests/.
#
# The test files (tests/test-*.R) are plain R scripts run by 'R CMD check'.
# Each one begins with a call to test_init(), which performs the shared setup
# those scripts rely on: choosing a default parallel backend, seeding the RNG
# for reproducibility, and working around environment quirks that would
# otherwise break R sub-processes spawned during testing.

# Copy every object in the RcppParallel namespace -- including internal,
# non-exported functions and constants -- into 'envir', so test scripts can
# reference them directly without the 'RcppParallel:::' prefix. Modelled on
# renv:::summon(). test_init() calls this for the test script's environment.
summon <- function(envir = parent.frame()) {
   namespace <- asNamespace("RcppParallel")
   contents <- as.list.environment(namespace, all.names = TRUE)
   list2env(contents, envir = envir)
   invisible(envir)
}

# Assert that 'cond' is true. Like a single-condition stopifnot(), but it also
# understands the all.equal() idiom: all.equal() returns TRUE when its
# arguments match and a character description of the differences when they do
# not, so a character result is reported as a failure. A logical 'cond' passes
# only if every element is TRUE (NAs count as failures), which makes it safe to
# pass a logical vector directly, e.g. assert(x > 0).
assert <- function(cond) {

   label <- paste(deparse(substitute(cond)), collapse = " ")

   # a character result (e.g. from all.equal()) describes a mismatch
   if (is.character(cond))
      stop(sprintf("assertion failed: %s\n%s", label, paste(cond, collapse = "\n")),
           call. = FALSE)

   if (!is.logical(cond) || anyNA(cond) || !all(cond))
      stop(sprintf("assertion failed: %s", label), call. = FALSE)

   invisible(TRUE)

}

test_init <- function() {

   # R CMD check sets R_TESTS=startup.Rs, which breaks R sub-processes run
   # with a different working directory (e.g. the Rscript invocations in a
   # test package's Makevars). Clearing it avoids those failures.
   # (based on practice in Rcpp)
   Sys.setenv(R_TESTS = "")

   # make tests that use random data deterministic
   set.seed(42L)

   # choose a default backend unless one was requested explicitly; tinythread
   # is always available, so tests can run even where TBB is not enabled
   backend <- Sys.getenv("RCPP_PARALLEL_BACKEND", unset = NA)
   if (is.na(backend))
      Sys.setenv(RCPP_PARALLEL_BACKEND = "tinythread")

   writeLines(paste("Using backend:", Sys.getenv("RCPP_PARALLEL_BACKEND")))

   # ensure the packages used by the C++ tests are available
   requireNamespace("Rcpp", quietly = TRUE)
   requireNamespace("RcppParallel", quietly = TRUE)

   # make all RcppParallel functions (including internal ones) directly
   # referenceable in the calling test script, without the ':::' prefix
   summon(parent.frame())

   invisible(TRUE)

}
