//==============================================================================
//         Copyright 2015   J.T Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ATAN2D_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ATAN2D_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief atan2d generic tag

     Represents the atan2d function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct atan2d_ : ext::elementwise_<atan2d_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<atan2d_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_atan2d_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::atan2d_, Site> dispatching_atan2d_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::atan2d_, Site>();
   }
   template<class... Args>
   struct impl_atan2d_;
  }
  /*!
    atan2d function : atan2 in degrees.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 r = atan2d(x, y);
    @endcode

    is similar but not fully equivalent to:

    @code
    T0 r =  atand(y/x);;
    @endcode

    as it is quadrant aware.

    For any real arguments @c x and @c y not both equal to zero, <tt>atan2d(x, y)</tt>
    is the angle in degrees between the positive x-axis of a plane and the point
    given by the coordinates  <tt>(y, x)</tt>.

    It is also the angle in \f$[-180,180[\f$ such that
    \f$x/\sqrt{x^2+y^2}\f$ and \f$y/\sqrt{x^2+y^2}\f$
    are respectively the sine and the cosine.

    @see @funcref{nbd_atan2}, @funcref{atand}
    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atan2d_, atan2d, 2)
}

#endif

