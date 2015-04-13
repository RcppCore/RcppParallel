context( "malloc" )

test_that( "tbbmalloc works", {
    
    skip_on_cran()
   
    sourceCpp( "cpp/malloc.cpp" )
})

