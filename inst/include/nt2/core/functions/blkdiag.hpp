//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BLKDIAG_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief blkdiag generic tag

     Represents the blkdiag function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct  blkdiag_ : ext::unspecified_<blkdiag_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<blkdiag_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_blkdiag_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }

  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::blkdiag_, Site> dispatching_blkdiag_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::blkdiag_, Site>();
   }
   template<class... Args>
   struct impl_blkdiag_;
  }
  /*!
    Builds a block diagonal matrix

    @par Semantic:


    @code
    auto r = blkdiag(a0,a1);
    @endcode

    Build a block diagonal matrix by concatenating two matrix along their
    diagonal.

    @see @funcref{cat}, @funcref{cath}, @funcref{catv}, @funcref{from_diag}, @funcref{diag_of}
    @param a0

    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::blkdiag_, blkdiag, 2)

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::blkdiag_, blkdiag, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::blkdiag_,Domain,N,Expr>
  {
    // TODO: case for dual static of_size_
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      if( !numel(boost::proto::child_c<0>(e).extent()) )
      {
        return boost::proto::child_c<1>(e).extent();
      }
      else if( !numel(boost::proto::child_c<1>(e).extent()) )
      {
        return boost::proto::child_c<0>(e).extent();
      }
      // otherwise compute the size properly
      else
      {
        result_type sizee(boost::proto::child_c<0>(e).extent());
        sizee[0] += boost::fusion::at_c<0>(boost::proto::child_c<1>(e).extent());
        sizee[1] += boost::fusion::at_c<1>(boost::proto::child_c<1>(e).extent());

        return sizee;
      }
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::blkdiag_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,0>::value_type::value_type  type;
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,1>::value_type::value_type  other_type;

    BOOST_MPL_ASSERT_MSG
    ( (boost::is_same<type,other_type>::value)
    , NT2_INCOMPATIBLE_TYPE_IN_BLKDIAG_EXPRESSION
    , (type,other_type)
    );
  };
} }

#endif
