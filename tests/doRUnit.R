stopifnot(require(RUnit, quietly = TRUE))
stopifnot(require(Rcpp, quietly = TRUE))
stopifnot(require(RcppParallel, quietly = TRUE))

## Set a seed to make the test deterministic
set.seed(42)

## Set a default backend
backend <- Sys.getenv("RCPP_PARALLEL_BACKEND", unset = NA)
if (is.na(backend))
   Sys.setenv(RCPP_PARALLEL_BACKEND = "tinythread")

writeLines(paste("Using backend:", Sys.getenv("RCPP_PARALLEL_BACKEND")))

## Define tests
suite <- defineTestSuite(
   name = "RcppParallel Unit Tests",
   dirs = system.file("tests", package = "RcppParallel")
)

## Based on practice in Rcpp to avoid some test failures
Sys.setenv("R_TESTS" = "")

## Run tests
tests <- runTestSuite(suite)

## Print results
printTextProtocol(tests)

## Return success or failure to R CMD CHECK
if (getErrors(tests)$nFail > 0) {
   stop("TEST FAILED!")
}

if (getErrors(tests)$nErr > 0) {
   stop("TEST HAD ERRORS!")
}

if (getErrors(tests)$nTestFunc < 1) {
   stop("NO TEST FUNCTIONS RUN!")
}
