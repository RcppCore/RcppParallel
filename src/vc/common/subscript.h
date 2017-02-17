/*  This file is part of the Vc library. {{{
Copyright © 2013-2015 Matthias Kretz <kretz@kde.org>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}}*/

#ifndef VC_COMMON_SUBSCRIPT_H_
#define VC_COMMON_SUBSCRIPT_H_

#include <initializer_list>
#include <ratio>
#include <type_traits>
#include <vector>
#include "types.h"
#include "macros.h"
#include <assert.h>

namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
// AdaptSubscriptOperator {{{1
template <typename Base> class AdaptSubscriptOperator : public Base
{
public:
    // perfect forward all Base constructors
    template <typename... Args>
    Vc_ALWAYS_INLINE AdaptSubscriptOperator(Args &&... arguments)
        : Base(std::forward<Args>(arguments)...)
    {
    }

    // perfect forward all Base constructors
    template <typename T>
    Vc_ALWAYS_INLINE AdaptSubscriptOperator(std::initializer_list<T> l)
        : Base(l)
    {
    }

    // explicitly enable Base::operator[] because the following would hide it
    using Base::operator[];

    /// \internal forward to non-member subscript_operator function
    template <typename I,
              typename = enable_if<!std::is_arithmetic<
                  typename std::decay<I>::type>::value>  // arithmetic types
                                                         // should always use
                                                         // Base::operator[] and
                                                         // never match this one
              >
    Vc_ALWAYS_INLINE auto operator[](I &&arg_)
        -> decltype(subscript_operator(*this, std::forward<I>(arg_)))
    {
        return subscript_operator(*this, std::forward<I>(arg_));
    }

    // const overload of the above
    template <typename I, typename = enable_if<
                              !std::is_arithmetic<typename std::decay<I>::type>::value>>
    Vc_ALWAYS_INLINE auto operator[](I &&arg_) const
        -> decltype(subscript_operator(*this, std::forward<I>(arg_)))
    {
        return subscript_operator(*this, std::forward<I>(arg_));
    }
};
// apply Scale (std::ratio) functions {{{1
template <typename Scale, typename T>
Vc_ALWAYS_INLINE enable_if<Scale::num == Scale::den, Traits::decay<T>> applyScale(T &&x)
{
    return std::forward<T>(x);
}

template <typename Scale, typename T>
Vc_ALWAYS_INLINE enable_if<
    Scale::num != Scale::den && Traits::has_multiply_operator<T, std::intmax_t>::value,
    Traits::decay<T>>
    applyScale(T &&x)
{
    static_assert(Scale::num % Scale::den == 0,
                  "Non-integral index scaling requested. This typically happens only for "
                  "Vc::Scalar on 32-bit for gathers on double. You can work around the "
                  "issue by ensuring that all doubles in the structure are aligned on 8 "
                  "Bytes.");
    constexpr auto value = Scale::num / Scale::den;
    Vc_ASSERT(Vc::all_of((x * value) / value == x));
    return std::forward<T>(x) * value;
}

template <typename Scale, typename T>
Vc_ALWAYS_INLINE enable_if<
    Scale::num != Scale::den && !Traits::has_multiply_operator<T, std::intmax_t>::value,
    T>
    applyScale(T x)
{
    static_assert(Scale::num % Scale::den == 0,
                  "Non-integral index scaling requested. This typically happens only for "
                  "Vc::Scalar on 32-bit for gathers on double. You can work around the "
                  "issue by ensuring that all doubles in the structure are aligned on 8 "
                  "Bytes.");
    constexpr auto value = Scale::num / Scale::den;
    for (size_t i = 0; i < x.size(); ++i) {
        Vc_ASSERT((x[i] * value) / value == x[i]);
        x[i] *= value;
    }
    return x;
}

template <typename Scale, typename T, typename U,
          typename = enable_if<Traits::has_multiply_operator<T, std::intmax_t>::value &&
                               Traits::has_addition_operator<T, U>::value>>
Vc_ALWAYS_INLINE typename std::decay<T>::type applyScaleAndAdd(T &&x, U &&y)
{
    constexpr auto value = Scale::num / Scale::den;
    if (value == 1) {  // static evaluation
        return std::forward<T>(x) + std::forward<U>(y);
    }
    return std::forward<T>(x) * value + std::forward<U>(y);
}

template <
    typename Scale, typename T, typename U,
    typename = enable_if<
        !(Traits::has_multiply_operator<T &, std::intmax_t>::value &&
          Traits::has_addition_operator<T &, decltype(std::declval<U>()[0])>::value) &&
        Traits::has_subscript_operator<U>::value>>
Vc_ALWAYS_INLINE T applyScaleAndAdd(T x, U &&y)
{
    constexpr auto value = Scale::num / Scale::den;
    for (size_t i = 0; i < x.size(); ++i) {
        if (value == 1) {  // static evaluation
            x[i] = x[i] + y[i];
        } else {
            x[i] = x[i] * value + y[i];
        }
    }
    return x;
}

template <typename Scale, typename T, typename U>
Vc_ALWAYS_INLINE enable_if<!(Traits::has_multiply_operator<T &, std::intmax_t>::value &&
                             Traits::has_addition_operator<T &, U>::value) &&
                               !Traits::has_subscript_operator<U>::value,
                           T>
    applyScaleAndAdd(T x, U &&y)
{
    constexpr auto value = Scale::num / Scale::den;
    for (size_t i = 0; i < x.size(); ++i) {
        if (value == 1) {  // static evaluation
            x[i] = x[i] + y;
        } else {
            x[i] = x[i] * value + y;
        }
    }
    return x;
}

// IndexVectorSizeMatches {{{1
template <std::size_t MinSize,
          typename IndexT,
          bool = Traits::is_simd_vector<IndexT>::value>
struct IndexVectorSizeMatches
    : public std::true_type  // you might expect this should be false_type here, but the point is
                             // that IndexT is a type where the size is not known at compile time.
                             // Thus it may be good but we cannot know from the type. The only check
                             // we could do is a runtime check, but the type is fine.
{
};

template <std::size_t MinSize, typename V>
struct IndexVectorSizeMatches<MinSize,
                              V,
                              true> : public std::integral_constant<bool, (MinSize <= V::Size)>
{
};

template <std::size_t MinSize, typename T, std::size_t ArraySize>
struct IndexVectorSizeMatches<MinSize,
                              T[ArraySize],
                              false> : public std::integral_constant<bool, (MinSize <= ArraySize)>
{
};

template <std::size_t MinSize, typename T, std::size_t ArraySize>
struct IndexVectorSizeMatches<MinSize,
                              std::array<T, ArraySize>,
                              false> : public std::integral_constant<bool, (MinSize <= ArraySize)>
{
};

template <std::size_t MinSize, typename T, std::size_t ArraySize>
struct IndexVectorSizeMatches<MinSize,
                              Vc::array<T, ArraySize>,
                              false> : public std::integral_constant<bool, (MinSize <= ArraySize)>
{
};
// convertIndexVector {{{1
// if the argument is a Vector<T> already we definitely want to keep it that way
template <typename IV>
enable_if<
    (Traits::is_simd_vector<IV>::value && sizeof(typename IV::EntryType) >= sizeof(int)),
    const IV &>
    convertIndexVector(const IV &indexVector)
{
    return indexVector;
}

// but if the scalar (integral) type is smaller than int we convert it up to int. Otherwise it's
// very likely that the calculations we have to perform will overflow.
template <typename IV>
enable_if<
    (Traits::is_simd_vector<IV>::value && sizeof(typename IV::EntryType) < sizeof(int)),
    SimdArray<int, IV::Size>>
    convertIndexVector(const IV &indexVector)
{
    return static_cast<SimdArray<int, IV::Size>>(indexVector);
}

// helper for promoting int types to int or higher
template<typename T> using promoted_type = decltype(std::declval<T>() + 1);

// std::array, Vc::array, and C-array are fixed size and can therefore be converted to a
// SimdArray of the same size
template <typename T, std::size_t N>
enable_if<std::is_integral<T>::value, SimdArray<promoted_type<T>, N>> convertIndexVector(
    const std::array<T, N> &indexVector)
{
    return {std::addressof(indexVector[0]), Vc::Unaligned};
}
template <typename T, std::size_t N>
enable_if<std::is_integral<T>::value, SimdArray<promoted_type<T>, N>> convertIndexVector(
    const Vc::array<T, N> &indexVector)
{
    return {std::addressof(indexVector[0]), Vc::Unaligned};
}
template <typename T, std::size_t N>
enable_if<std::is_integral<T>::value, SimdArray<promoted_type<T>, N>> convertIndexVector(
    const T (&indexVector)[N])
{
    return SimdArray<promoted_type<T>, N>{std::addressof(indexVector[0]), Vc::Unaligned};
}

// a plain pointer won't work. Because we need some information on the number of values in
// the index argument
template <typename T>
enable_if<std::is_pointer<T>::value, void> convertIndexVector(T indexVector) = delete;

// an initializer_list works, but is runtime-sized (before C++14, at least) so we have to
// fall back to std::vector
template <typename T>
std::vector<promoted_type<T>> convertIndexVector(
    const std::initializer_list<T> &indexVector)
{
    return {begin(indexVector), end(indexVector)};
}

// a std::vector cannot be converted to anything better
template <typename T>
enable_if<(std::is_integral<T>::value && sizeof(T) >= sizeof(int)), std::vector<T>>
    convertIndexVector(const std::vector<T> &indexVector)
{
    return indexVector;
}
template <typename T>
enable_if<(std::is_integral<T>::value && sizeof(T) < sizeof(int)),
          std::vector<promoted_type<T>>>
    convertIndexVector(const std::vector<T> &indexVector)
{
    return {std::begin(indexVector), std::end(indexVector)};
}

template <typename T, typename = decltype(convertIndexVector(std::declval<T>()))>
std::true_type is_valid_indexvector(T &&);
std::false_type is_valid_indexvector(...);

// SubscriptOperation {{{1
template <
    typename T, typename IndexVector, typename Scale = std::ratio<1, 1>,
    bool = decltype(is_valid_indexvector(std::declval<const IndexVector &>()))::value>
class SubscriptOperation
{
    const IndexVector m_indexes;
    T *const m_address;
    using ScalarType = typename std::decay<T>::type;

    using IndexVectorScaled = Traits::decay<decltype(convertIndexVector(std::declval<const IndexVector &>()))>;

public:
    template <typename U,
              typename = enable_if<((std::is_convertible<const U &, IndexVector>::value ||
                                     std::is_same<U, IndexVector>::value) &&
                                    std::is_copy_constructible<IndexVector>::value)>>
    constexpr Vc_ALWAYS_INLINE SubscriptOperation(T *address, const U &indexes)
        : m_indexes(indexes), m_address(address)
    {
    }

    template <std::size_t... Indexes>
    constexpr Vc_ALWAYS_INLINE SubscriptOperation(T *address, const IndexVector &indexes,
                                                  index_sequence<Indexes...>)
        : m_indexes{indexes[Indexes]...}, m_address(address)
    {}

    template <typename U>
    constexpr Vc_ALWAYS_INLINE SubscriptOperation(
        T *address, const U &indexes,
        enable_if<((std::is_convertible<const U &, IndexVector>::value ||
                    std::is_same<U, IndexVector>::value) &&
                   !std::is_copy_constructible<IndexVector>::value &&
                   std::is_array<IndexVector>::value &&
                   std::extent<IndexVector>::value > 0)> = nullarg)
        : SubscriptOperation(address, indexes,
                             make_index_sequence<std::extent<IndexVector>::value>())
    {
    }

    Vc_ALWAYS_INLINE GatherArguments<T, IndexVectorScaled> gatherArguments() const
    {
        static_assert(std::is_arithmetic<ScalarType>::value,
                      "Incorrect type for a SIMD vector gather. Must be an arithmetic type.");
        return {applyScale<Scale>(convertIndexVector(m_indexes)), m_address};
    }

    Vc_ALWAYS_INLINE ScatterArguments<T, IndexVectorScaled> scatterArguments() const
    {
        static_assert(std::is_arithmetic<ScalarType>::value,
                      "Incorrect type for a SIMD vector scatter. Must be an arithmetic type.");
        return {applyScale<Scale>(convertIndexVector(m_indexes)), m_address};
    }

    template <typename V,
              typename = enable_if<(std::is_arithmetic<ScalarType>::value &&Traits::is_simd_vector<
                  V>::value &&IndexVectorSizeMatches<V::Size, IndexVector>::value)>>
    Vc_ALWAYS_INLINE operator V() const
    {
        static_assert(std::is_arithmetic<ScalarType>::value,
                      "Incorrect type for a SIMD vector gather. Must be an arithmetic type.");
        const auto indexes = applyScale<Scale>(convertIndexVector(m_indexes));
        return V(m_address, indexes);
    }

    template <typename V,
              typename = enable_if<(std::is_arithmetic<ScalarType>::value &&Traits::is_simd_vector<
                  V>::value &&IndexVectorSizeMatches<V::Size, IndexVector>::value)>>
    Vc_ALWAYS_INLINE SubscriptOperation &operator=(const V &rhs)
    {
        static_assert(std::is_arithmetic<ScalarType>::value,
                      "Incorrect type for a SIMD vector scatter. Must be an arithmetic type.");
        const auto indexes = applyScale<Scale>(convertIndexVector(m_indexes));
        rhs.scatter(m_address, indexes);
        return *this;
    }

    // precondition: m_address points to a struct/class/union
    template <
        typename U,
        typename S,  // S must be equal to T. Still we require this template parameter -
        // otherwise instantiation of SubscriptOperation would only be valid for
        // structs/unions.
        typename = enable_if<std::is_same<S, typename std::remove_cv<T>::type>::value &&(
            std::is_class<T>::value || std::is_union<T>::value)>>
    Vc_ALWAYS_INLINE auto operator[](U S::*member)
        -> SubscriptOperation<
              typename std::conditional<std::is_const<T>::value,
                                        const typename std::remove_reference<U>::type,
                                        typename std::remove_reference<U>::type>::type,
              IndexVector,
              // By passing the scale factor as a fraction of integers in the template
              // arguments the value does not lose information if the division yields a
              // non-integral value. This could happen e.g. for a struct of struct (S2 {
              // S1, char }, with sizeof(S1) = 16, sizeof(S2) = 20. Then scale would be
              // 20/16)
              std::ratio_multiply<Scale, std::ratio<sizeof(S), sizeof(U)>>>
    {
        static_assert(std::is_same<Traits::decay<decltype(m_address->*member)>,
                                   Traits::decay<U>>::value,
                      "Type mismatch that should be impossible.");
        // TODO: check whether scale really works for unions correctly
        return {&(m_address->*member), m_indexes};
    }

    /*
     * The following functions allow subscripting of nested arrays. But
     * there are two cases of containers and only one that we want to support:
     * 1. actual arrays (e.g. T[N] or std::array<T, N>)
     * 2. dynamically allocated vectors (e.g. std::vector<T>)
     *
     * For (1.) the offset calculation is straightforward.
     * For (2.) the m_address pointer points to memory where pointers are
     * stored to the actual data. Meaning the data can be scattered
     * freely in memory (and far away from what m_address points to). Supporting this leads to
     * serious trouble with the pointer (it does not really point to the start of a memory
     * region anymore) and inefficient code. The user is better off to write a loop that assigns the
     * scalars to the vector object sequentially.
     */

    // precondition: m_address points to a type that implements the subscript operator
    template <
        typename U =
            T>  // U is only required to delay name lookup to the 2nd phase (on use).
                // This is necessary because m_address[0][index] is only a correct
                // expression if has_subscript_operator<T>::value is true.
    Vc_ALWAYS_INLINE auto
        operator[](enable_if<
#ifndef Vc_IMPROVE_ERROR_MESSAGES
                       Traits::has_no_allocated_data<T>::value &&
                           Traits::has_subscript_operator<T>::value &&
#endif
                           std::is_same<T, U>::value,
                       std::size_t> index)
            -> SubscriptOperation<
                  // the following decltype expression must depend on index and cannot
                  // simply use [0][0] because it would yield an invalid expression in
                  // case m_address[0] returns a struct/union
                  typename std::remove_reference<decltype(m_address[0][index])>::type,
                  IndexVector,
                  std::ratio_multiply<Scale,
                                      std::ratio<sizeof(T), sizeof(m_address[0][index])>>>
    {
        static_assert(Traits::has_subscript_operator<T>::value,
                      "The subscript operator was called on a type that does not implement it.\n");
        static_assert(Traits::has_no_allocated_data<T>::value,
                      "Invalid container type in gather/scatter operation.\nYou may only use "
                      "nested containers that store the data inside the object (such as builtin "
                      "arrays or std::array) but not containers that store data in allocated "
                      "memory (such as std::vector).\nSince this feature cannot be queried "
                      "generically at compile time you need to spezialize the "
                      "Vc::Traits::has_no_allocated_data_impl<T> type-trait for custom types that "
                      "meet the requirements.\n");
        static_assert(std::is_lvalue_reference<decltype(m_address[0][index])>::value,
                      "The container does not return an lvalue reference to the data at "
                      "the requested offset. This makes it impossible to execute a "
                      "gather operation.\n");
        return {&(m_address[0][index]), m_indexes};
    }

    // precondition: m_address points to a type that implements the subscript operator
    template <typename IT>
    Vc_ALWAYS_INLINE enable_if<
#ifndef Vc_IMPROVE_ERROR_MESSAGES
        Traits::has_no_allocated_data<T>::value &&Traits::has_subscript_operator<T>::value &&
#endif
            Traits::has_subscript_operator<IT>::value,
        SubscriptOperation<
            typename std::remove_reference<
                decltype(m_address[0][std::declval<const IT &>()[0]]  // std::declval<IT>()[0] could
                                                                      // be replaced with 0 if it
                         // were not for two-phase lookup. We need to make the
                         // m_address[0][0] expression dependent on IT
                         )>::type,
            IndexVectorScaled,
            std::ratio<1, 1>  // reset Scale to 1 since it is applied below
            >>
        operator[](const IT &index)
    {
        static_assert(Traits::has_subscript_operator<T>::value,
                      "The subscript operator was called on a type that does not implement it.\n");
        static_assert(Traits::has_no_allocated_data<T>::value,
                      "Invalid container type in gather/scatter operation.\nYou may only use "
                      "nested containers that store the data inside the object (such as builtin "
                      "arrays or std::array) but not containers that store data in allocated "
                      "memory (such as std::vector).\nSince this feature cannot be queried "
                      "generically at compile time you need to spezialize the "
                      "Vc::Traits::has_no_allocated_data_impl<T> type-trait for custom types that "
                      "meet the requirements.\n");
        return {&(m_address[0][0]),
                applyScaleAndAdd<std::ratio_multiply<
                    Scale, std::ratio<sizeof(T), sizeof(m_address[0][0])>>>(
                    convertIndexVector(m_indexes), index)};
    }
};

// specialization for invalid IndexVector type
template <typename T, typename IndexVector, typename Scale>
class SubscriptOperation<T, IndexVector, Scale, false>;

// subscript_operator {{{1
template <
    typename Container,
    typename IndexVector,
    typename = enable_if<
        Traits::has_subscript_operator<IndexVector>::value  // The index vector must provide [] for
                                                            // the implementations of gather/scatter
        &&Traits::has_contiguous_storage<Container>::value  // Container must use contiguous
                                                            // storage, otherwise the index vector
        // cannot be used as memory offsets, which is required for efficient
        // gather/scatter implementations
        &&std::is_lvalue_reference<decltype(*begin(std::declval<
            Container>()))>::value  // dereferencing the begin iterator must yield an lvalue
                                    // reference (const or non-const). Otherwise it is not possible
                                    // to determine a pointer to the data storage (see above).
        >>
Vc_ALWAYS_INLINE SubscriptOperation<
    typename std::remove_reference<decltype(*begin(std::declval<Container>()))>::
        type,  // the type of the first value in the container is what the internal array pointer
               // has to point to. But if the subscript operator of the container returns a
               // reference we need to drop that part because it's useless information for us. But
               // const and volatile, as well as array rank/extent are interesting and need not be
               // dropped.
    typename std::remove_const<typename std::remove_reference<
        IndexVector>::type>::type  // keep volatile and possibly the array extent, but the const and
                                   // & parts of the type need to be removed because
                                   // SubscriptOperation explicitly adds them for its member type
    > subscript_operator(Container &&c, IndexVector &&indexes)
{
    Vc_ASSERT(std::addressof(*begin(c)) + 1 ==
              std::addressof(*(begin(c) + 1)));  // runtime assertion for contiguous storage, this
                                                 // requires a RandomAccessIterator - but that
                                                 // should be given for a container with contiguous
                                                 // storage
    return {std::addressof(*begin(c)), std::forward<IndexVector>(indexes)};
}


static_assert(!Traits::has_subscript_operator<SubscriptOperation<int[100][100], const int *>, int>::value, "");
static_assert(!Traits::has_subscript_operator<SubscriptOperation<int[100][100], const int *>, int[4]>::value, "");
static_assert(!Traits::has_subscript_operator<SubscriptOperation<std::vector<int>, const int *>, int[4]>::value, "");
static_assert( Traits::has_subscript_operator<SubscriptOperation<int[100][100], const int[4]>, int>::value, "");
static_assert( Traits::has_subscript_operator<SubscriptOperation<int[100][100], const int[4]>, int[4]>::value, "");
static_assert(!Traits::has_subscript_operator<SubscriptOperation<std::vector<int>, const int[4]>, int[4]>::value, "");

/**
 * \internal
 * Implement subscripts of std::initializer_list. This function must be in the global scope
 * because Container arguments may be in any scope. The other argument is in std scope.
 *
 * -----
 * std::initializer_list does not have constexpr member functions in C++11, but from C++14 onwards
 * the world is a happier place. :)
 */
template <typename Container, typename I>
Vc_ALWAYS_INLINE Vc::Common::SubscriptOperation<
    typename std::remove_reference<decltype(std::declval<Container>()[0])>::type,
    const std::initializer_list<I> &> subscript_operator(Container &&vec,
                                                   const std::initializer_list<I> &indexes)
{
    return {&vec[0], indexes};
}
//}}}1

}  // namespace Common

using Common::subscript_operator;

namespace Traits
{
template <typename T, typename IndexVector, typename Scale>
struct is_subscript_operation_internal<Common::SubscriptOperation<T, IndexVector, Scale>> : public std::true_type
{
};
}  // namespace Traits

using Common::subscript_operator;

}  // namespace Vc

#endif // VC_COMMON_SUBSCRIPT_H_

// vim: foldmethod=marker
