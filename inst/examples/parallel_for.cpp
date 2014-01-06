#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(tbb)]]

#include <tbb/tbb_stddef.h>

// Below is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar)

// For more on using Rcpp click the Help button on the editor toolbar

// [[Rcpp::export]]
int timesTwo(int x) {
   
   //R_GetCCallable("tbb", "__ZN3tbb8internal15runtime_warningEPKcz");
   
   tbb::internal::runtime_warning("no way!!!");
   
   return 0;
}
