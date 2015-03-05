context( "transform" )

test_that( "transform works with Rcpp", {
    sourceCpp( "cpp/transform.cpp" )
       
    m <- matrix(as.numeric(c(1:1000000)), nrow = 1000, ncol = 1000)

    expect_equal(matrixSqrt(m), parallelMatrixSqrt(m))      
})

