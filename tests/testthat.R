library(testthat)
library(Rcpp)
library(RcppParallel)

Sys.setenv("R_TESTS"="")

test_check("RcppParallel")

