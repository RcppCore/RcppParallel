//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_IND2SUB_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_IND2SUB_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief ind2sub generic tag

      Represents the ind2sub function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct ind2sub_ : ext::tieable_<ind2sub_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<ind2sub_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_ind2sub_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::ind2sub_, Site> dispatching_ind2sub_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::ind2sub_, Site>();
    }
    template<class... Args>
    struct impl_ind2sub_;
  }

  /*!
    @brief Index to Subscript conversion

    Determines the equivalent subscript values corresponding to
    a single index into an array.

    @param a0 Size of the table to index
    @param a1 Linear index to convert
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ind2sub_, ind2sub, 2)

  /*!
    @brief Index to Subscript conversion

    Determines the equivalent subscript values corresponding to
    a single index into an array with a given base index.

    @param a0 Size of the table to index
    @param a1 Linear index to convert
    @param a2 Base index of the table to index
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ind2sub_, ind2sub, 3)
}

#endif
