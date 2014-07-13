#ifndef __RCPP_PARALLEL_MATRIX__
#define __RCPP_PARALLEL_MATRIX__

namespace RcppParallel {

#include <iterator>

template <typename T>
class MatrixAccessor {
public:
   class Row {
   public:   
      class Iterator 
         : public std::iterator<std::input_iterator_tag, T, std::size_t> {
      public:
      
         Iterator(Row& row, std::size_t i)
            : start_(row.start_), parentNrow_(row.parentNrow_), index_(i)
         {
         }
         
         Iterator(const Iterator& other) 
            : start_(other.start_), 
              parentNrow_(other.parentNrow_), 
              index_(other.index_)
         {
         }
         
         Iterator& operator++() { 
            index_++;
            return *this;
         }
         
         Iterator operator++(int) {
            Iterator tmp(*this); 
            operator++(); 
            return tmp;
         }
         
         bool operator==(const Iterator& rhs) {
            return index_ == rhs.index_;
         }
         
         bool operator!=(const Iterator& rhs) {
            return index_ != rhs.index_;
         }
         
         T& operator*() { return start_[index_ * parentNrow_]; }
         
      private:
         T* start_;
         std::size_t parentNrow_;
         std::size_t index_;
      };
   
      Row(MatrixAccessor& parent, std::size_t i)
         : start_(parent.begin() + i),
           parentNrow_(parent.nrow()),
           parentNcol_(parent.ncol())
      {
      }
      
      Row(const Row& other)
         : start_(other.start_),
           parentNrow_(other.parentNrow_),
           parentNcol_(other.parentNcol_)
      {        
      }
      
      Row& operator=(const Row& rhs) {
         start_ = rhs.start_;
         parentNrow_ = rhs.parentNrow_;
         parentNcol_ = rhs.parentNcol_;
         return *this;
      }
      
      Iterator begin() {
         return Iterator(*this, 0);
      }
      
      Iterator end() {
         return Iterator(*this, parentNcol_);
      }
      
      inline T& operator[](std::size_t i) {
        return start_[i * parentNrow_];
      }
              
   private:
      T* start_;
      std::size_t parentNrow_;
      std::size_t parentNcol_;
   };
   
   class Column {
   public:
      typedef T* Iterator;
   
      Column(MatrixAccessor& parent, std::size_t i) 
         : begin_(parent.begin() + (i * parent.nrow())),
           end_(begin_ + parent.nrow())
      {   
      }
      
      Column(const Column& other) 
         : begin_(other.begin_), end_(other.end_)
      {   
      }
      
      Column& operator=(const Column& rhs) {
         begin_ = rhs.begin_;
         end_ = rhs.end_;
         return *this;
      }
      
      inline T* begin() { return begin_; }
      inline T* end() { return end_; }
      
   private:
      T* begin_;
      T* end_;
   };

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
   
   inline Column column(std::size_t i) {
      return Column(*this, i);
   }
   
   inline Row row(std::size_t i) {
      return Row(*this, i);
   }

private:
   T* data_;
   std::size_t nrow_;
   std::size_t ncol_;
};

typedef MatrixAccessor<double> NumericMatrixAccessor;
typedef MatrixAccessor<int> IntegerMatrixAccessor;

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_MATRIX__