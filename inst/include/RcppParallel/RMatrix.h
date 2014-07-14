#ifndef __RCPP_PARALLEL_RMATRIX__
#define __RCPP_PARALLEL_RMATRIX__

namespace RcppParallel {

#include <iterator>

template <typename T>
class RMatrix {
public:
   class Row {
   
   public:   
      
      class iterator 
         : public std::iterator<std::input_iterator_tag, T, std::size_t> {
      
      public:
         inline iterator(Row& row, std::size_t i)
            : start_(row.start_), parentNrow_(row.parent_.nrow()), index_(i)
         {
         }
         
         inline iterator(const iterator& other) 
            : start_(other.start_), 
              parentNrow_(other.parentNrow_), 
              index_(other.index_)
         {
         }
         
         inline iterator& operator++() { 
            index_++;
            return *this;
         }
         
         inline iterator operator++(int) {
            iterator tmp(*this); 
            operator++(); 
            return tmp;
         }
         
         inline bool operator==(const iterator& rhs) {
            return index_ == rhs.index_;
         }
         
         inline bool operator!=(const iterator& rhs) {
            return index_ != rhs.index_;
         }
         
         inline T& operator*() { return start_[index_ * parentNrow_]; }
         
      private:
         T* start_;
         std::size_t parentNrow_;
         std::size_t index_;
      };
   
      inline Row(RMatrix& parent, std::size_t i)
         : parent_(parent),
           start_(parent.begin() + i)
      {
      }
      
      inline Row(const Row& other)
         : parent_(other.parent_),
           start_(other.start_)
      {        
      }
      
      inline iterator begin() {
         return iterator(*this, 0);
      }
      
      inline iterator end() {
         return iterator(*this, parent_.ncol());
      }
      
      inline size_t length() {
         return parent_.ncol();
      }
      
      inline T& operator[](std::size_t i) {
        return start_[i * parent_.nrow()];
      }
              
   private:
      RMatrix& parent_;
      T* start_;
   };
   
   class Column {
   
   public:
   
      typedef T* iterator;
   
      inline Column(RMatrix& parent, std::size_t i) 
         : begin_(parent.begin() + (i * parent.nrow())),
           end_(begin_ + parent.nrow())
      {   
      }
      
      inline Column(const Column& other) 
         : begin_(other.begin_), end_(other.end_)
      {   
      }
      
      inline Column& operator=(const Column& rhs) {
         begin_ = rhs.begin_;
         end_ = rhs.end_;
         return *this;
      }
      
      inline iterator begin() { return begin_; }
      inline iterator end() { return end_; }
      
      inline size_t length() { return end_ - begin_; }
      
      inline T& operator[](std::size_t i) {
        return begin_ + i;
      }
      
   private:
      T* begin_;
      T* end_;
   };

   typedef T* iterator;

   template <typename Source>
   inline explicit RMatrix(const Source& source) 
      : data_(source.begin()),
        nrow_(source.nrow()),
        ncol_(source.ncol())
   {
   }

   inline RMatrix(const T* data, std::size_t nrow, std::size_t ncol) 
      : data_(data), nrow_(nrow), ncol_(ncol) 
   {
   }
   
   inline std::size_t length() const { return nrow_ * ncol_; }
   
   inline iterator begin() { return data_; }
   inline iterator end() { return data_ + length(); }
     
   inline std::size_t nrow() const { return nrow_; }
   
   inline Row row(std::size_t i) {
      return Row(*this, i);
   }
   
   inline std::size_t ncol() const { return ncol_; }
   
   inline Column column(std::size_t i) {
      return Column(*this, i);
   }
   
private:
   T* data_;
   std::size_t nrow_;
   std::size_t ncol_;
};

} // namespace RcppParallel

#endif // __RCPP_PARALLEL_RMATRIX__