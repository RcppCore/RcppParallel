//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DATA_HPP_INCLUDED
#define NT2_SDK_MEMORY_DATA_HPP_INCLUDED

#include <nt2/sdk/memory/forward/container.hpp>

namespace nt2
{
  namespace details
  {
    template<typename T, typename Enable = void>
    struct  data_from
    {
      typedef T* type;

      static type call(T& c)        { return &c; }
    };

    template<typename T, typename Enable>
    struct  data_from<T const, Enable>
    {
      typedef T const* type;

      static type call(T const& c) { return &c; }
    };

    template<typename T>
    struct data_from< T
                    , typename  boost::dispatch::meta::
                      enable_if_type<typename T::pointer>::type
                    >
    {
      typedef typename T::pointer type;

      static type call(T& c) { return c.data(); }
    };

    template<typename T>
    struct data_from< T const
                    , typename  boost::dispatch::meta::
                      enable_if_type<typename T::pointer>::type
                    >
    {
      typedef typename T::const_pointer type;

      static type call(T const& c) { return c.data(); }
    };
  }

  namespace memory
  {
    /*!
      @brief Generic access to internal data pointer

      Return a possibly const-qualified pointer to the data of any object.

      @par Semantic:

      For any instance @c t of type @c T,

      @code
      T* p = data(t);
      @endcode

      is equivalent to :

      @code
      T* p = t.data();
      @endcode

      if T provides a @c data() member function.

      Otherwise, it is equivalent to :

      @code
      T* p = &t;
      @endcode

      If @c t is @c const, the returned pointer is const-qualified.

      @param t Object to access

      @return a possibly const-qualified pointer to its arguments data
    **/
    template<typename T>
    BOOST_FORCEINLINE typename details::data_from<T>::type data(T& t)
    {
      return details::data_from<T>::call(t);
    }

    /// @overload
    template<typename T>
    BOOST_FORCEINLINE typename details::data_from<T const>::type data(T const& t)
    {
      return details::data_from<T const>::call(t);
    }

    // container_ref and container_shared_ref have special behavior w/r to
    // pointer and const_pointer. Those specialization are required for them
    // to work correctly.

    /// @overload
    template<typename Kind, typename T, typename S>
    BOOST_FORCEINLINE typename memory::container_ref<Kind, T, S>::pointer
    data(memory::container_ref<Kind, T, S> const& c)
    {
      return c.data();
    }

    /// @overload
    template<typename Kind, typename T, typename S>
    BOOST_FORCEINLINE typename memory::container_ref<Kind, T, S>::pointer
    data(memory::container_ref<Kind, T, S>& c)
    {
      return c.data();
    }

    /// @overload
    template<typename Kind, typename T, typename S, bool Own>
    BOOST_FORCEINLINE
    typename memory::container_shared_ref<Kind, T, S, Own>::pointer
    data(memory::container_shared_ref<Kind, T, S, Own> const& c)
    {
      return c.data();
    }

    /// @overload
    template<typename Kind, typename T, typename S, bool Own>
    BOOST_FORCEINLINE
    typename memory::container_shared_ref<Kind, T, S, Own>::pointer
    data(memory::container_shared_ref<Kind, T, S, Own>& c)
    {
      return c.data();
    }
  }
}

#endif
