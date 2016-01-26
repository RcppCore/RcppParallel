//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBAL_HPP_INCLUDED

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the global functor
    **/
    struct global_ : ext::abstract_<global_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<global_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_global_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::global_, Site> dispatching_global_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::global_, Site>();
    }
    template<class... Args>
    struct impl_global_;
  }

  /*!
    @brief Apply a reduction operation with one or two parametersto
    every elements of an expression

    @param a0 Functor tag to apply
    @param a1 Expression to process
    @param a2 additionnal parameter if needed by a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::global_, global, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::global_, global, 2)
}

#endif
