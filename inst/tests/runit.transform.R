
sourceCpp(system.file("tests/cpp/transform.cpp", package = "RcppParallel"))

test.transform <- function() {
   
   m <- matrix(as.numeric(c(1:1000000)), nrow = 1000, ncol = 1000)
   
   checkEquals(
      matrixSqrt(m), 
      parallelMatrixSqrt(m)
   )   
}
