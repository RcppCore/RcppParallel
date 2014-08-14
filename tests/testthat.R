require(methods)
require(RcppParallel)
require(testthat)

RCPP <- Sys.getenv( "RCPP" )
if( RCPP == "Rcpp" ){
  message( "testing against Rcpp" ) 
  require(Rcpp)  
} else if( RCPP == "Rcpp11" ){
  message( "testing against Rcpp11" ) 
  require(attributes)  
} else {
  stop( "Rcpp implementation not setup, please set the $RCPP environment variable" )  
}

test_dir("testthat")

