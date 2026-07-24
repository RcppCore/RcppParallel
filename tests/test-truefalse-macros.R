RcppParallel:::test_init()

# this file has no runtime assertions: the TRUE/FALSE macro checks are
# static_assert()s in the C++ source, so a successful compile is the test
Rcpp::sourceCpp(system.file("tests/cpp/truefalse_macros.cpp", package = "RcppParallel"))
