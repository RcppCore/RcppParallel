//==============================================================================
//         Copyright 2014        LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014        NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_EXHAUSTIVE_EXHAUSTIVE_HPP_INCLUDED
#define NT2_SDK_EXHAUSTIVE_EXHAUSTIVE_HPP_INCLUDED

#include <nt2/include/functions/simd/load.hpp>
#include <nt2/include/functions/simd/extract.hpp>
#include <nt2/include/functions/simd/successor.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/scalar/is_invalid.hpp>
#include <nt2/include/functions/scalar/ulpdist.hpp>
#include <nt2/include/functions/scalar/iround.hpp>
#include <nt2/include/functions/scalar/ilog2.hpp>
#include <nt2/include/functions/scalar/min.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/bitwise_cast.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstddef>
#include "omp.hpp"

namespace nt2
{
  /*!
    @brief Exhaustive precision test for single precision

    Perform a ULP test on every representable single precision value
    in a given interval. Results are reported using a bucket histogram that
    gives hint on how many values fall in a given range of ULPs,
    the smallest and greatest inputs in the chosen range
    leading to this precision and  the result from this minimum input
    against the awaited result.

    @par Note:
    Currently this function is designed to take care of single precision only as
    running such a test on double precision values take an absurd amount of time.

    @tparam Type          Data type used for computation
    @param  mini Lower    bound of the test interval
    @param  maxi Upper    bound of the test interval
    @param  test_f        Function to test
    @param  reference_f   Reference function to compare to

    @par Example:

    Here is an example to test SIMD single-precision nt2::log against scalar double-precision std::log.

    @code
    #include <boost/simd/sdk/simd/native.hpp>
    #include <nt2/include/functions/log.hpp>
    #include <nt2/include/constants/zero.hpp>
    #include <nt2/include/constants/valmax.hpp>

    #include <nt2/sdk/exhaustive/exhaustive.hpp>

    // specific to nt2 tests: specify assert handling
    #define NT2_ASSERTS_AS_TRAP
    #include <nt2/sdk/error/assert_as_trap.hpp>

    #include <cmath>
    #include <cstdlib>

    // function object used for the reference
    struct std_log
    {
      float operator()(float x) const
      {
        return float(std::log(double(x)));
      }
    };

    int main(int argc, char* argv[])
    {
      // define boundaries from command-line arguments,
      // fallback to default values if not provided
      float mini = argc >= 2 ? std::atof(argv[1]) : nt2::Zero<float>();
      float mini = argc >= 3 ? std::atof(argv[2]) : nt2::Valmin<float>();

      // type to call the function object to test with
      typedef boost::simd::native<float, BOOST_SIMD_DEFAULT_EXTENSION> n_t;

      // run the test
      nt2::exhaustive_test<n_t>( mini
                               , maxi
                               , nt2::functor<nt2::tag::log_>() // function object to test
                               , std_log()
                               );
    }
    @endcode
  **/
  template<typename Type, typename TestF, typename RefF> inline
  void exhaustive_test(float mini, float maxi, TestF test_f, RefF reference_f)
  {
    typedef Type                                                    n_t;
    typedef typename boost::dispatch::meta::as_integer<Type>::type  in_t;

    static const nt2::uint32_t M = 128;
    static const nt2::uint32_t N = boost::simd::meta::cardinal_of<n_t>::value;
    in_t vN = nt2::splat<in_t>(N);

    nt2::uint32_t histo[M+2];
    float maxin[M+2], minin[M+2], minref[M+2], minval[M+2];

    for(auto& e : histo ) e = 0;
    for(auto& e : minin ) e = nt2::Valmax<float>();
    for(auto& e : maxin ) e = nt2::Valmin<float>();
    for(auto& e : minval) e = nt2::Nan<float>();
    for(auto& e : minref) e = nt2::Valmax<float>();

    auto t_min = nt2::bitwise_cast<nt2::uint32_t>(nt2::abs(mini));
    auto t_max = nt2::bitwise_cast<nt2::uint32_t>(nt2::abs(maxi));

    auto diff  = (mini*maxi < 0)  ? std::max(t_max,t_min) + std::min(t_max,t_min)
                                  : std::max(t_max,t_min) - std::min(t_max,t_min);

    std::cout << "Exhaustive test for: " << nt2::type_id(test_f)      << "\n"
              << "             versus: " << nt2::type_id(reference_f) << "\n"
              << "             With T: " << nt2::type_id<Type>()      << "\n"
              << "           in range: [" << mini << ", " << maxi << "]" << "\n"
              << "         # of tests: " << diff << "\n";
    std::cout << std::endl;

    nt2::uint32_t k = 0;

    #ifdef _OPENMP
    #pragma omp parallel firstprivate(mini,maxi,diff)
    #endif
    {
      bool  hit_loc[M+2];
      nt2::uint32_t histo_loc[M+2];
      float maxin_loc[M+2] , minin_loc[M+2], minref_loc[M+2], minval_loc[M+2];

      for(auto& e : hit_loc   ) e = false;
      for(auto& e : histo_loc ) e = 0;
      for(auto& e : minin_loc ) e = nt2::Valmax<float>();
      for(auto& e : maxin_loc ) e = nt2::Valmin<float>();
      for(auto& e : minval_loc) e = nt2::Nan<float>();
      for(auto& e : minref_loc) e = nt2::Valmax<float>();

      std::size_t numThreads  = get_num_threads();
      std::size_t my_id       = get_thread_num();
      std::size_t num_inc     = diff / numThreads;

      float my_mini = nt2::successor(mini,my_id*num_inc);
      float my_maxi = nt2::successor(my_mini,num_inc);
      if (my_id == numThreads -1) my_maxi = maxi;

      // Fill up the reference SIMD register data
      float a[N];
      a[0] = my_mini;
      for(std::size_t i = 1; i < N; i++) a[i] = nt2::successor(a[i-1], 1);
      n_t a0 = nt2::load<n_t>(&a[0],0);

      nt2::uint32_t k_loc = 0, j = 0;

      while( nt2::extract(a0,1) < my_maxi )
      {
        n_t z = test_f(a0);

        for(std::size_t i = 0; i < N; i++)
        {
          if (nt2::extract(a0,i)> my_maxi) break;
          float v = reference_f(nt2::extract(a0,i));
          float sz = nt2::extract(z,i);

          double u = nt2::ulpdist(v, sz)*2.0+1.0;

          if(nt2::is_invalid(u))
          {
            ++histo_loc[M+1];
            if (!hit_loc[M+1])
            {
              maxin_loc [M+1] = minin_loc [M+1] = nt2::extract(a0,i);
              minref_loc[M+1] = v;
              minval_loc[M+1] = nt2::extract(z,i);
              hit_loc[M+1] = true;
            }
            else
            {
              maxin_loc [M+1] = nt2::extract(a0,i);
            }
          }
          else
          {
            int p = nt2::min(int(M), int(nt2::ilog2(nt2::iround(u))));

            if (!hit_loc[p])
            {
              maxin_loc [p] = minin_loc [p] = nt2::extract(a0,i);
              minref_loc[p] = v;
              minval_loc[p] = nt2::extract(z,i);
              hit_loc[p] = true;
            }
            else
            {
              maxin_loc [p] = nt2::extract(a0,i);
            }
            ++histo_loc[p];
          }

          ++k_loc;
        }
        a0 = nt2::successor(a0, vN);
      }

      #ifdef _OPENMP
      #pragma omp critical
      #endif
      {
        for (std::size_t kk=0;kk<M+2;kk++)
        {
          maxin[kk] = std::max(maxin_loc[kk],maxin[kk]);

          if (minin_loc[kk]<minin[kk])
          {
            minin[kk] = std::min(minin_loc[kk],minin[kk]);
            minval[kk] = minval_loc[kk];
          }

          minref[kk] = std::min(minref_loc[kk],minref[kk]);
          histo[kk] += histo_loc[kk];
        }
        k += k_loc;
      }
    } //end omp parallel

    std::cout << k << "/" << diff << " values computed.\n";

    double d = 1;
    for(std::size_t i = 0; i < M+1; i++, d*= 2.0)
    {
      if(histo[i])
      {
        printf("%10u values (%.2f%%)\twithin %1.1f ULPs\t"
              , histo[i], (histo[i]*100.0/k), (d < 2 ? 0 : d/4)
              );
        if(i)
          std::cout << std::scientific << std::setprecision(9)
                    << "in range [" << minin[i] << ", "<< maxin[i] << "]" << "."
                    << " Example: "<< minin[i] << " returns " << minval[i]
                    << " instead of " << minref[i];
        std::cout << std::endl;
      }
    }

    if( histo[M+1])
    {
      printf("%10u values (%.2f%%)\twith invalid result.\t"
            , histo[M+1], (histo[M+1]*100.0/k)
            );
      std::cout << std::scientific << std::setprecision(9)
                << "in range [" << minin[M+1] << ", "<< maxin[M+1] << "]" << "."
                << " Example: "<< minin[M+1] << " returns " << minval[M+1]
                << " instead of " << minref[M+1]
                << std::endl;
    }
  }
}

#endif
