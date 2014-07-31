context( "sum" )

test_that( "sum works with Rcpp", {
    sourceCpp( "cpp/sum.cpp" )
       
    v <- as.numeric(c(1:10000000))
    
    expect_equal( 
        vectorSum(v), 
        parallelVectorSum(v)
        )      
})

