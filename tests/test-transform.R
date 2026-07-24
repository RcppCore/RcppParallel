RcppParallel:::test_init()

Rcpp::sourceCpp(system.file("tests/cpp/transform.cpp", package = "RcppParallel"))

m <- matrix(as.numeric(1:1000000), nrow = 1000, ncol = 1000)

assert(all.equal(
   matrixSqrt(m),
   parallelMatrixSqrt(m)
))
