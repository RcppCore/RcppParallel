//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_BUFFER_HPP_INCLUDED

#include <nt2/memory/functions/copy.hpp>
#include <nt2/sdk/memory/destruct.hpp>
#include <nt2/sdk/memory/local_ptr.hpp>
#include <nt2/sdk/memory/construct.hpp>
#include <nt2/sdk/memory/is_safe.hpp>
#include <nt2/sdk/memory/adapted/buffer.hpp>
#include <nt2/sdk/memory/fixed_allocator.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/detail/iterator.hpp>
#include <boost/assert.hpp>
#include <boost/swap.hpp>
#include <cstddef>

// Growth factor is globally optimizable
#ifndef NT2_BUFFER_GROWTH_FACTOR
#define NT2_BUFFER_GROWTH_FACTOR 2
#endif

namespace nt2 { namespace memory
{
  //============================================================================
  /**!
   * @brief buffer is a dynamically-sized sequence using dynamic storage.
   **/
  //===========================================================================
  template<class T, class Allocator>
  class buffer : private Allocator
  {
  public:
    //==========================================================================
    // Container types
    //==========================================================================
    typedef typename Allocator::template rebind<T>::other allocator_type;
    typedef typename allocator_type::value_type           value_type;
    typedef typename allocator_type::reference            reference;
    typedef typename allocator_type::const_reference      const_reference;
    typedef typename allocator_type::pointer              pointer;
    typedef typename allocator_type::const_pointer        const_pointer;
    typedef typename allocator_type::pointer              iterator;
    typedef typename allocator_type::const_pointer        const_iterator;
    typedef std::reverse_iterator<iterator>               reverse_iterator;
    typedef std::reverse_iterator<const_iterator>         const_reverse_iterator;
    typedef typename allocator_type::size_type            size_type;
    typedef typename allocator_type::difference_type      difference_type;

    //==========================================================================
    // Default constructor
    //==========================================================================
    buffer( allocator_type a = allocator_type())
          : allocator_type(a)
          , begin_(0), end_(0), capacity_(0)
    {}

  private:
    //==========================================================================
    // Local helper for constructor dealing with memory
    //==========================================================================
    struct deleter
    {
      std::size_t size_;
      allocator_type& alloc_;

      deleter(std::size_t s, allocator_type& a) : size_(s), alloc_(a) {}
      void operator()(pointer ptr) { alloc_.deallocate(ptr,size_); }
    private:
      deleter& operator=(deleter const&);
    };

  public:
    //==========================================================================
    // Size constructor
    //==========================================================================
    buffer( size_type n, allocator_type a = allocator_type())
          : allocator_type(a)
          , begin_(0), end_(0), capacity_(0)
    {
      if(!n) return;

      local_ptr<T,deleter> that ( allocator_type::allocate(n)
                                , deleter(n,get_allocator())
                                );

      self_construct( that.get(), that.get() + n
                    , typename boost::is_same < Allocator
                                              , fixed_allocator<T>
                                              >::type()
                    );

      begin_ = that.release();
      end_ = capacity_ = begin_ + n;
    }

    //==========================================================================
    // Copy constructor with extra capacity
    //==========================================================================
    buffer( buffer const& src, std::size_t capa )
          : allocator_type(src.get_allocator())
          , begin_(0), end_(0), capacity_(0)
    {
      if(!capa) return;

      local_ptr<T,deleter> that ( allocator_type::allocate(capa)
                                , deleter(capa,get_allocator())
                                );

      nt2::memory::copy_construct ( src.begin(),src.end()
                                  , that.get()
                                  , get_allocator()
                                  );

      begin_    = that.release();
      end_      = begin_ + src.size();
      capacity_ = begin_ + capa;
    }

    //==========================================================================
    // Copy constructor
    //==========================================================================
    buffer( buffer const& src )
          : allocator_type(src.get_allocator())
          , begin_(0), end_(0), capacity_(0)
    {
      if(!src.size()) return;

      local_ptr<T,deleter> that ( allocator_type::allocate(src.size())
                                , deleter(src.size(),get_allocator())
                                );

      nt2::memory::copy_construct ( src.begin(),src.end()
                                  , that.get()
                                  , get_allocator()
                                  );

      begin_ = that.release();
      end_ = capacity_ = begin_ + src.size();
    }

    //==========================================================================
    // Destructor
    //==========================================================================
    ~buffer()
    {
      if(begin_)
      {
        self_destruct ( typename boost::is_same < Allocator
                                                , fixed_allocator<T>
                                                >::type()
                      );

        allocator_type::deallocate(begin_,capacity());
      }
    }

    //==========================================================================
    // Assignment
    //==========================================================================
    buffer& operator=(buffer const& src)
    {
      resize(src.size());
      nt2::memory::copy(src.begin(),src.end(),begin());
      return *this;
    }

    //==========================================================================
    // Non-conservative resize
    //==========================================================================
    void resize( size_type sz )
    {
      if(sz > capacity() )
      {
        // Resize to twice the requested size to optimize capacity usage
        buffer that(sz,get_allocator());
        swap(that);
        return;
      }

      finish_resize ( sz
                    , typename boost::is_same < Allocator
                                              , fixed_allocator<T>
                                              >::type()
                    );

      end_ = begin_ + sz;
    }

    //==========================================================================
    // Resizes and add one element at the end
    //==========================================================================
    void push_back( T const& t )
    {
      std::ptrdiff_t osz = size();

      if( end_ >= capacity_ )
      {
        typename boost::is_same<Allocator,fixed_allocator<T> >::type is_fixed;
        buffer that(*this, new_size(osz, 1, is_fixed));
        swap(that);
      }

      new(end_) T(t);
      ++end_;
    }

    //==========================================================================
    // Resizes and add a range of elements at the end
    //==========================================================================
    template<typename Iterator> void append( Iterator b, Iterator e )
    {
      std::ptrdiff_t osz = size();
      std::ptrdiff_t sz = e-b;

      if( end_ >= capacity_ )
      {
        typename boost::is_same<Allocator,fixed_allocator<T> >::type is_fixed;
        buffer that(*this, new_size(osz, sz, is_fixed));
        swap(that);
      }

      nt2::memory::copy(b,e,begin_+osz);

      end_ += sz;
    }

    //==========================================================================
    // Swap
    //==========================================================================
    void swap( buffer& src )
    {
      boost::swap(begin_          , src.begin_          );
      boost::swap(end_            , src.end_            );
      boost::swap(capacity_       , src.capacity_       );
      boost::swap(get_allocator() , src.get_allocator() );
    }

    //==========================================================================
    // Iterators
    //==========================================================================
    iterator        begin()       { return begin_;  }
    const_iterator  begin() const { return begin_;  }
    iterator        end()         { return end_;    }
    const_iterator  end()   const { return end_;    }

    reverse_iterator rbegin()     { return reverse_iterator(end());   }
    reverse_iterator rend()       { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const
    {
      return const_reverse_iterator(begin());
    }

    //==========================================================================
    // Allocator access
    //==========================================================================
    allocator_type& get_allocator()
    {
      return static_cast<allocator_type&>(*this);
    }

    allocator_type const& get_allocator() const
    {
      return static_cast<allocator_type const&>(*this);
    }

    //==========================================================================
    // Raw values
    //==========================================================================
    pointer        data()       { return begin_;  }
    const_pointer  data() const { return begin_;  }

    //==========================================================================
    // Size related members
    //==========================================================================
    inline size_type  size()      const { return end_ - begin_;       }
    inline size_type  capacity()  const { return capacity_ - begin_;  }
    inline bool       empty()     const { return size() == 0;         }

    //==========================================================================
    // Random access
    //==========================================================================
    inline reference       operator[](size_type i)
    {
      BOOST_ASSERT_MSG( nt2::memory::is_safe(*this,i)
                      , "Out of range acces on buffer"
                      );
      return begin_[i];
    }

    inline const_reference operator[](size_type i) const
    {
      BOOST_ASSERT_MSG(  nt2::memory::is_safe(*this,i)
                      , "Out of range acces on buffer"
                      );
      return begin_[i];
    }

  private:

    inline std::size_t new_size ( std::size_t osz, std::size_t
                                , boost::mpl::true_ const&
                                )
    {
      return osz;
    }

    inline std::size_t new_size ( std::size_t osz, std::size_t extra
                                , boost::mpl::false_ const&
                                )
    {
      return NT2_BUFFER_GROWTH_FACTOR*(osz + extra);
    }

    inline void self_destruct(boost::mpl::false_ const&)
    {
      nt2::memory::destruct(begin_,end_,get_allocator());
    }

    inline void self_destruct(boost::mpl::true_ const&) {}

    inline void self_construct( T* b, T* e, boost::mpl::false_ const& )
    {
      nt2::memory::default_construct(b,e,get_allocator());
    }

    inline void self_construct( T*, T*, boost::mpl::true_ const&) {}

    inline void finish_resize(size_type sz, boost::mpl::false_ const&)
    {
      if(sz < size())
        nt2::memory::destruct(begin_ + sz, end_, get_allocator());
      else
        nt2::memory::default_construct(end_, begin_ + sz, get_allocator());
    }

    inline void finish_resize(size_type, boost::mpl::true_ const&) {}

    private:
    pointer     begin_, end_, capacity_;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   * \param x First \c pointer_buffer to swap
   * \param y Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T, class A> inline void swap(buffer<T,A>& x, buffer<T,A>& y)
  {
    x.swap(y);
  }
} }

#endif
