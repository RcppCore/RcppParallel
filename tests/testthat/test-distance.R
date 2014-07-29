context( "distance" )

test_that( "distance works with Rcpp", {
    sourceCpp( "cpp/distance.cpp" )
       
    n  = 1000
    m = matrix(runif(n*10), ncol = 10)
    m = m/rowSums(m)
    
    expect_equal( 
        rcpp_js_distance(m), 
        rcpp_parallel_js_distance(m)
        )      
})

