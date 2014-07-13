#ifndef __RCPP_PARALLEL_MATRIX__
#define __RCPP_PARALLEL_MATRIX__

namespace RcppParallel {

template <typename T>
class MatrixReader {
public:
   template <typename Source>
   explicit MatrixReader(const Source& source)
      : data_(source.begin()), 
        len_(source.nrow() * source.ncol()),
        nrow_(source.nrow()),
        ncol_(source.ncol())
   {
   }

   MatrixReader(const T* data, std::size_t nrow, std::size_t ncol)
      : data_(data), len_(nrow * ncol), nrow_(nrow), ncol_(ncol)
   {
   }
   
   inline const T* begin() const { return data_; }
   inline const T* end() const { return data_ + len_; }
   
   inline const T* operator[](std::size_t i) const { 
      return data_ + i ; 
   }
   
   inline std::size_t length() const { return len_; }
   inline std::size_t nrow() const { return nrow_; }
   inline std::size_t ncol() const { return ncol_; }
   
private:
   const T* data_;
   std::size_t len_;
   std::size_t nrow_;
   std::size_t ncol_;
};

typedef MatrixReader<double> NumericMatrixReader;
typedef MatrixReader<int> IntegerMatrixReader;


template <typename T>
class MatrixWriter {
public:
   template <typename Source>
   explicit MatrixWriter(const Source& source)
      : data_(source.begin()), 
        len_(source.nrow() * source.ncol()),
        nrow_(source.nrow()),
        ncol_(source.ncol())
   {
   }

   MatrixWriter(T* data, std::size_t nrow, std::size_t ncol)
      : data_(data), len_(nrow * ncol), nrow_(nrow), ncol_(ncol)
   {
   }
   
   inline T* begin() { return data_; }
   inline T* end() { return data_ + len_; }
   
   inline T* operator[](std::size_t i) { 
      return data_ + i ; 
   }
   
   inline std::size_t length() const { return len_; }
   inline std::size_t nrow() const { return nrow_; }
   inline std::size_t ncol() const { return ncol_; }
   
private:
   T* data_;
   std::size_t len_;
   std::size_t nrow_;
   std::size_t ncol_;
};

typedef MatrixWriter<double> NumericMatrixWriter;
typedef MatrixWriter<int> IntegerMatrixWriter;




} // namespace RcppParallel

#endif // __RCPP_PARALLEL_MATRIX__