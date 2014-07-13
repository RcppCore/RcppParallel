#ifndef __RCPP_PARALLEL_VECTOR__
#define __RCPP_PARALLEL_VECTOR__

namespace RcppParallel {

template <typename T>
class VectorReader {
public:
   template <typename Source>
   explicit VectorReader(const Source& source)
      : data_(source.begin()), len_(source.length())
   {
   }

   VectorReader(const T* data, size_t len)
      : data_(data), len_(len)
   {
   }
   
   const T* begin() const { return data_; }
   const T* end() const { return data_ + len_; }
   
   size_t length() const { return len_; }
   
private:
   const T* data_;
   size_t len_;
};

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_VECTOR__