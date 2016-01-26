//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_HANOWA_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_HANOWA_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_hanowa hanowa
 *
 * \par Description
 *    a =  hanowa(n, d) takes an integer m and produces
 *    an (2*m)-by-(2*m)  matrix of the form:
 *              catv(cath(d*eye(m),   -diag(_(1, m))),
 *                   cath(diag(_(1, m),   d*eye(m))))
 *
 *    a has complex eigenvalues of the form: d +/- k*i,
 *    for 1 <= k <= m. the default value of d is -1.
 *    reference:
 *    E. Hairer, S.P. Norsett and G. Wanner, Solving Ordinary
 *    Differential Equations I: Nonstiff Problems,
 *    Springer-Verlag, Berlin, 1987. (pp. 86-87)
 *
 *
 * \code
 * #include <nt2/include/functions/hanowa.hpp>
 * \endcode
 *
**/
//==============================================================================
// hanowa actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag hanowa_ of functor hanowa
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct hanowa_ : ext::abstract_<hanowa_>
    {
      typedef ext::abstract_<hanowa_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_hanowa_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::hanowa_, Site> dispatching_hanowa_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::hanowa_, Site>();
    }
    template<class... Args>
    struct impl_hanowa_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::hanowa_, hanowa, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::hanowa_, hanowa, 3)


}

#endif
