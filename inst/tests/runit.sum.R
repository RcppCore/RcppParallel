
sourceCpp(system.file("tests/cpp/sum.cpp", package = "RcppParallel"))

test.sum <- function() {
   
   v <- as.numeric(c(1:10000000))
   
   checkEquals(
      vectorSum(v), 
      parallelVectorSum(v)
   )
}
