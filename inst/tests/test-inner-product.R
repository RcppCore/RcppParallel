context( "inner product" )

test_that( "parallelInnerProduct works with Rcpp", {
    sourceCpp( "cpp/innerproduct.cpp" )
       
    x <- runif(1000000)
    y <- runif(1000000)

    expect_equal(innerProduct(x, y), parallelInnerProduct(x, y))      
})

