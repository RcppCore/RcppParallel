sourceCpp(system.file("tests/cpp/malloc.cpp", package = "RcppParallel"))

test.malloc <- function() {
   tbbMalloc()   
}

