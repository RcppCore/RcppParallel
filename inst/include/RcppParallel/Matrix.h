#ifndef __RCPP_PARALLEL_MATRIX__
#define __RCPP_PARALLEL_MATRIX__

namespace RcppParallel {

template <typename T>
class MatrixAccessor {
public:
   template <typename Source>
   explicit MatrixAccessor(const Source& source)
      : data_(source.begin()), 
        nrow_(source.nrow()),
        ncol_(source.ncol())
   {
   }

   MatrixAccessor(const T* data, std::size_t nrow, std::size_t ncol)
      : data_(data), nrow_(nrow), ncol_(ncol)
   {
   }
   
   inline T* begin() { return data_; }
   inline T* end() { return data_ + length(); }
   
   inline std::size_t length() const { return nrow_ * ncol_; }
   
   inline std::size_t nrow() const { return nrow_; }
   inline std::size_t ncol() const { return ncol_; }
   
private:
   T* data_;
   std::size_t nrow_;
   std::size_t ncol_;
};

typedef MatrixAccessor<double> NumericMatrixAccessor;
typedef MatrixAccessor<int> IntegerMatrixAccessor;

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_MATRIX__