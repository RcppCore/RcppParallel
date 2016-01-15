//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SHUFFLE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/swar/functions/details/random_permute.hpp>
#include <boost/dispatch/meta/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief shuffle generic tag

      Represents the shuffle function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct shuffle_ : ext::unspecified_<shuffle_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<shuffle_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_shuffle_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::shuffle_, Site> dispatching_shuffle_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::shuffle_, Site>();
    }
    template<class... Args>
    struct impl_shuffle_;
  }
} }

namespace
{
  /// INTERNAL ONLY - local shuffle functor type
  template<typename T>
  using shuffle_t = typename boost::dispatch
                                  ::make_functor< boost::simd::tag::shuffle_
                                                , T
                                                >::type;
}

namespace boost { namespace simd
{
  /*!
    @brief SIMD register shuffling

    Shuffle the elements of one SIMD register following a compile-time
    permutation pattern passed as a static list of integral constants.

    @par Semantic:

    Let's @c T be a SIMD register type of cardinal @c N and <tt>I1,...,In</tt> be
    @c N integral constant in \f$[-1, N[\f$. For any SIMD register @c v of type
    @c T, the following code :

    @code
    T r = shuffle<I1, ..., In>(v);
    @endcode

    is equivalent to

    @code
    r[0]   = I1 == -1 ? 0 : v[I1];
    r[1]   = I2 == -1 ? 0 : v[I2];
    ...
    r[N-1] = Ic == -1 ? 0 : v[In];
    @endcode

    @usage{shuffle_idx1.cpp}

    @tparam Indices Integral constant defining the permutation pattern
    @param  a0 First register to shuffle

    @return A SIMD register shuffled as per the permutation pattern
  **/
  template<int... Indices, typename A0>
  BOOST_FORCEINLINE
  auto shuffle(A0 const& a0)
      -> decltype(shuffle_t<A0>()(a0,details::random_permute_t<Indices...>()))
  {
    static_assert ( boost::simd::meta::cardinal_of<A0>::value == sizeof...(Indices)
                  , "Wrong number of permutation indices"
                  );

    return shuffle_t<A0>()(a0,details::random_permute_t<Indices...>());
  }

  /*!
    @brief SIMD register shuffling

    Shuffle the elements of two SIMD registers following a compile-time
    permutation pattern passed as a static list of integral constants.

    @par Semantic:

    Let's @c T be a SIMD register type of cardinal @c N and <tt>I1,...,In</tt> be
    @c N integral constant in \f$[-1, 2N-1[\f$. For any SIMD register @c v1 and @c v2
    of type @c T, the following code :

    @code
    T r = shuffle<I1, ..., In>(v1,v2);
    @endcode

    is equivalent to shuffling the agglomeration of @c v1 and @c v2 and extracting
    the lower part of the resulting vector.

    @code
    r[0]   = shuffle<I1,...,Ic>( combine(v1,v2) )[0]
    r[1]   = shuffle<I1,...,Ic>( combine(v1,v2) )[1]
    ...
    r[N-1] = shuffle<I1,...,Ic>( combine(v1,v2) )[N-1]
    @endcode

    @usage{shuffle_idx2.cpp}

    @tparam Indices Integral constant defining the permutation pattern
    @param  a0 First register to shuffle
    @param  a1 Second register to shuffle.

    @return A SIMD register shuffled as per the permutation pattern
  **/
  template<int... Indices, typename A0, typename A1>
  BOOST_FORCEINLINE
  auto shuffle(A0 const& a0, A1 const& a1)
      -> decltype(shuffle_t<A0>()(a0,a1,details::random_permute_t<Indices...>()))
  {
    static_assert (  boost::simd::meta::cardinal_of<A0>::value == sizeof...(Indices)
                  && boost::simd::meta::cardinal_of<A1>::value == sizeof...(Indices)
                  , "Wrong number of permutation indices"
                  );

    return shuffle_t<A0>()(a0,a1,details::random_permute_t<Indices...>());
  }

  /*!
    @brief SIMD register shuffling

    Shuffle the elements of one SIMD register following a compile-time
    permutation pattern passed as a @metafunction.

    @par Semantic:

    Let's @c T be a SIMD register type of cardinal @c N, @c Perm be a
    binary @metafunction. For any SIMD register @c v of type @c T, the following
    code:

    @code
    T r = shuffle<Perm>(v);
    @endcode

    is respectively equivalent to

    @code
    T r = shuffle< mpl::apply<Perm, int_<0>, int_<N> >::type::value
                 , ...
                 , mpl::apply<Perm, int_<C-1>, int_<N> >::type::value
                 >(v);
    @endcode

    @usage{shuffle_perm2.cpp}

    @tparam Perm Permutation pattern @metafunction
    @param  a0 First register to shuffle

    @return A SIMD register shuffled as per the permutation pattern
  **/
  template<typename Perm,typename A0>
  BOOST_FORCEINLINE
  auto shuffle(A0 const& a0)
      -> decltype(shuffle_t<A0>()(a0,boost::dispatch::meta::as_<Perm>()))
  {
    return shuffle_t<A0>()(a0,boost::dispatch::meta::as_<Perm>());
  }

  /*!
    @brief SIMD register shuffling

    Shuffle the elements of two SIMD registers following a compile-time
    permutation pattern passed as a @metafunction.

    @par Semantic:

    Let's @c T be a SIMD register type of cardinal @c N, @c Perm be a
    binary @metafunction. For any SIMD register @c v1 and  @c v2 of type @c T,
    the following code:

    @code
    T r = shuffle<Perm>(v1,v2);
    @endcode

    is equivalent to

    @code
    T r = shuffle< mpl::apply<Perm, int_<0>, int_<N> >::type::value
                 , ...
                 , mpl::apply<Perm, int_<C-1>, int_<N> >::type::value
                 >(v1,v2);
    @endcode

    @usage{shuffle_perm1.cpp}

    @tparam Perm Permutation pattern @metafunction
    @param  a0 First register to shuffle
    @param  a1 Second register to shuffle.

    @return A SIMD register shuffled as per the permutation pattern
  **/
  template<typename Perm, typename A0, typename A1>
  BOOST_FORCEINLINE
  auto shuffle(A0 const& a0, A1 const& a1)
      -> decltype(shuffle_t<A0>()(a0,a1,boost::dispatch::meta::as_<Perm>()))
  {
    return shuffle_t<A0>()(a0,a1,boost::dispatch::meta::as_<Perm>());
  }
} }

#endif
