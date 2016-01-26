//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_MOLER_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_MOLER_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief moler generic tag

      Represents the moler function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct moler_ : ext::abstract_<moler_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<moler_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_moler_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::moler_, Site> dispatching_moler_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::moler_, Site>();
    }
    template<class... Args>
    struct impl_moler_;
  }

  /*!
    @brief Moler matrix.

    Returns the symmetric positive definite n-by-n matrix U'*U, where
    U = triw(n,alpha).

    @par Reference:

    J. C. Nash, Compact Numerical Methods for Computers: Linear
    Algebra and Function Minimisation, second edition, Adam Hilger,
    Bristol, 1990 (Appendix 1).
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::moler_, moler, 2)

  /*!
    @brief Default Moler matrix.

    Returns the symmetric positive definite n-by-n matrix U'*U, where
    U = triw(n,-1). In this case, if

    @code
    a = moler(n);
    @endcode

    then

    @code
    a(i,j) = min(i,j)-2
    a(i,i) = i.
    @endcode

    One of the eigenvalues of a is small.

    @par Reference:

    J. C. Nash, Compact Numerical Methods for Computers: Linear
    Algebra and Function Minimisation, second edition, Adam Hilger,
    Bristol, 1990 (Appendix 1).
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::moler_, moler, 1)
}

#endif
