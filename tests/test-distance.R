RcppParallel:::test_init()

Rcpp::sourceCpp(system.file("tests/cpp/distance.cpp", package = "RcppParallel"))

n <- 1000
m <- matrix(runif(n * 10), ncol = 10)
m <- m / rowSums(m)

assert(all.equal(
   rcpp_js_distance(m),
   rcpp_parallel_js_distance(m)
))
