
sourceCpp(system.file("tests/cpp/innerproduct.cpp", package = "RcppParallel"))

test.innerproduct <- function() {
   
   x <- runif(1000000)
   y <- runif(1000000)
   
   checkEquals(
      innerProduct(x, y), 
      parallelInnerProduct(x, y)
   )
}
