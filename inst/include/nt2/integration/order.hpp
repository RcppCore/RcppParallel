//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_ORDER_HPP_INCLUDED
#define NT2_INTEGRATION_ORDER_HPP_INCLUDED

namespace nt2
{
  namespace details
  {
    //Put the way points points in increasing order
    template <class W>
    inline bool order_points(W&, bool sort = false)
    {
      bool reverse = false;
       if (sort)
       {
//Thist is not in use for now, but may be in othr integration processes not yet implanted
//         reverse = wpts(begin_) > wpts(end_);
//         if (reverse)
//           std::swap(wpts(begin_), wpts(end_));
//         if (numel(wpts) > 3)
//         {
//           tab_t wpts0 = nt2::rowvect(wpts(begin_+1, end_-1));
//           tab_t wpts1 = nt2::sort(wpts0(nt2::logical_and(nt2::gt(wpts0, wpts(begin_)), nt2::lt(wpts0, wpts(end_)))));
//           wpts0 = nt2::cath(nt2::cath(wpts(begin_),wpts1), wpts(end_));
//           wpts =  wpts0; //ALIASING
//         }
       }
      return reverse;
    }
  }
}

#endif
