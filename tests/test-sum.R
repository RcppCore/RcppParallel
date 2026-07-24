RcppParallel:::test_init()

Rcpp::sourceCpp(system.file("tests/cpp/sum.cpp", package = "RcppParallel"))

v <- as.numeric(1:10000000)

assert(all.equal(
   vectorSum(v),
   parallelVectorSum(v)
))
