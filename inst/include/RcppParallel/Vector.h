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

   VectorReader(const T* data, std::size_t len)
      : data_(data), len_(len)
   {
   }
   
   inline const T* begin() const { return data_; }
   inline const T* end() const { return data_ + len_; }
   
   inline const T* operator[](std::size_t i) const { 
      return data_ + i ; 
   }
   
   inline std::size_t length() const { return len_; }
   
private:
   const T* data_;
   std::size_t len_;
};

typedef VectorReader<double> NumericVectorReader;
typedef VectorReader<int> IntegerVectorReader;

template <typename T>
class VectorWriter {
public:
   template <typename Source>
   explicit VectorWriter(Source& source)
      : data_(source.begin()), len_(source.length())
   {
   }

   VectorWriter(T* data, size_t len)
      : data_(data), len_(len)
   {
   }
   
   inline T* begin() { return data_; }
   inline T* end(){ return data_ + len_; }
   
   inline T* operator[](std::size_t i) { 
      return data_ + i; 
   }
   
   inline std::size_t length() const { return len_; }
   
private:
   T* data_;
   std::size_t len_;
};

typedef VectorWriter<double> NumericVectorWriter;
typedef VectorWriter<int> IntegerVectorWriter;

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_VECTOR__