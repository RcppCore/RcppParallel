
sourceCpp(system.file("tests/cpp/distance.cpp", package = "RcppParallel")) 

test.distance <- function() {
   
   n  = 1000
   m = matrix(runif(n*10), ncol = 10)
   m = m/rowSums(m)
   
   checkEquals(
      rcpp_js_distance(m), 
      rcpp_parallel_js_distance(m)
   )
}
