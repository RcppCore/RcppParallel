#ifndef RCPP_PARALLEL_SIMD_H
#define RCPP_PARALLEL_SIMD_H

// Bring in the headers that automatically include the most
// commonly used SIMD functions. We do this for a couple reasons:
//
//    1. Including each desired header 'by hand' can be tedious
//       for the user,
//
//    2. Certain headers depend on others in such a way that attempting
//       to include one without the other can lead to obscure compiler
//       errors.
//
// The downside is the increased compile time, but this is something that users
// have implicitly accepted given the heavy use of template meta-programming in
// Boost.SIMD and its dependent libraries.
#include <boost/simd/sdk/simd/algorithm.hpp>

#include <boost/simd/memory/memory.hpp>
#include <boost/simd/memory/allocator.hpp>

#include <boost/simd/arithmetic/arithmetic.hpp>

#include <boost/simd/bitwise/bitwise.hpp>

#include <boost/simd/boolean/boolean.hpp>

#include <boost/simd/reduction/reduction.hpp>

#include <boost/simd/swar/swar.hpp>






namespace RcppParallel {

template <typename DataType>
class SimdTransformer
{
public:
   typedef DataType value_type;
   typedef boost::simd::pack<DataType> packed_type;
};

template <typename DataType, class Transformer>
DataType simdTransformAndReduce(const DataType* it, const DataType* end, Transformer transformer)
{
   using boost::simd::pack;
   using boost::simd::load;
   
   pack<DataType> accumulated = transformer.initialize(it, end);
   for (; it != end; it += pack<DataType>::static_size)
      transformer.update(load<pack<DataType>>(it), &accumulated);
   return transformer.reduce(accumulated);
}

} // namespace RcppParallel

#endif /* RCPP_PARALLEL_SIMD_H */
