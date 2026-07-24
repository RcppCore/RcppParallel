RcppParallel:::test_init()

Rcpp::sourceCpp(system.file("tests/cpp/innerproduct.cpp", package = "RcppParallel"))

x <- runif(1000000)
y <- runif(1000000)

assert(all.equal(
   innerProduct(x, y),
   parallelInnerProduct(x, y)
))
