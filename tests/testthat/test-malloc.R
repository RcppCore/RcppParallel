context( "malloc" )

test_that( "tbbmalloc works", {
    sourceCpp( "cpp/malloc.cpp" )
})

