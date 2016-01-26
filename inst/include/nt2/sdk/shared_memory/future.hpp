//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_FUTURE_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_FUTURE_HPP_INCLUDED

#include <type_traits>
#include <utility>
#include <vector>

namespace nt2
{
    template<class Arch, class result_type>
    struct make_future;

    template<class Arch>
    struct async_impl;

    template<class Arch, typename result_type>
    struct make_ready_future_impl;

    template< typename Arch, typename result_type>
    inline typename make_future< Arch,result_type>::type
    make_ready_future(result_type value)
    {
       return make_ready_future_impl<Arch,result_type>()
              .call(std::move(value) );
    }

    template<class Arch>
    struct when_all_impl;

    template<class Arch, typename ... A>
    struct when_all_result
    {
      typedef typename make_future<Arch,int>::type type;
    };

    template<class Arch, class Future>
    struct when_all_vec_result
    {
      typedef typename make_future<Arch,int>::type type;
    };

    template < typename Arch, typename Future>
    inline typename when_all_vec_result<Arch,Future>::type
    when_all( std::vector<Future> && lazy_values )
    {
        return when_all_impl<Arch>().call(
          std::forward< std::vector<Future> > (lazy_values)
          );
    }

    template< typename Arch,typename ... A >
    inline typename when_all_result<Arch,A...>::type
    when_all(A && ... a)
    {
      return when_all_impl<Arch>().call(a ...);
    }

    template< typename Arch,typename F, typename ... A >
    inline typename make_future<  Arch,
                                  typename std::result_of< F(A ...) >::type
                               >::type
    async( F && f, A && ... a)
    {
        return async_impl<Arch>().call( std::forward<F>(f)
                                      , std::forward<A>(a)...
                                      );
    }
}


#endif
