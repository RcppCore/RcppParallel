#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(tbb)]]
#include <tbb/tbb.h>
using namespace tbb;

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

struct Average {
    const float* input;
    float* output;
    void operator()( const blocked_range<int>& range ) const {
        for( int i=range.begin(); i!=range.end(); ++i )
            output[i] = (input[i-1]+input[i]+input[i+1])*(1/3.f);
    }
};

// Note: Reads input[0..n] and writes output[1..n-1]. 
void ParallelAverage( float* output, const float* input, size_t n ) {
    Average avg;
    avg.input = input;
    avg.output = output;
    parallel_for( blocked_range<int>( 1, n ), avg );
}


// [[Rcpp::export]]
void parallelFor() {
  std::vector<float> inputs(100, 42);
  std::vector<float> outputs(100);
  
  ParallelAverage(&outputs[0], &inputs[0], 100);
}


struct Sum {
    float value;
    Sum() : value(0) {}
    Sum( Sum& s, split ) {value = 0;}
    void operator()( const blocked_range<float*>& r ) {
        float temp = value;
        for( float* a=r.begin(); a!=r.end(); ++a ) {
            temp += *a;
        }
        value = temp;
    }
    void join( Sum& rhs ) {value += rhs.value;}
};


float ParallelSum( float array[], size_t n ) {
    Sum total;
    parallel_reduce( blocked_range<float*>( array, array+n ), 
                     total );
    return total.value;
}

// [[Rcpp::export]]
float parallelSum() {
   std::vector<float> vecs(100, 200);
   return ParallelSum(&vecs[0], vecs.size());
}

