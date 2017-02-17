/*  This file is part of the Vc library. {{{
Copyright © 2009-2015 Matthias Kretz <kretz@kde.org>
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

#ifndef VC_SCALAR_MASK_H_
#define VC_SCALAR_MASK_H_

#include "types.h"
#include "macros.h"

namespace Vc_VERSIONED_NAMESPACE
{
template <typename T> class Mask<T, VectorAbi::Scalar>
{
    friend class Mask<  double, VectorAbi::Scalar>;
    friend class Mask<   float, VectorAbi::Scalar>;
    friend class Mask< int32_t, VectorAbi::Scalar>;
    friend class Mask<uint32_t, VectorAbi::Scalar>;
    friend class Mask< int16_t, VectorAbi::Scalar>;
    friend class Mask<uint16_t, VectorAbi::Scalar>;

public:
    using abi = VectorAbi::Scalar;

    static constexpr size_t Size = 1;
    static constexpr size_t MemoryAlignment = 1;
    static constexpr std::size_t size() { return 1; }

    /**
     * The \c EntryType of masks is always bool, independent of \c T.
     */
    typedef bool EntryType;

    using EntryReference = bool &;

    /**
     * The \c VectorEntryType, in contrast to \c EntryType, reveals information about the SIMD
     * implementation. This type is useful for the \c sizeof operator in generic functions.
     */
    typedef bool VectorEntryType;

    /**
     * The \c VectorType reveals the implementation-specific internal type used for the SIMD type.
     */
    using VectorType = bool;

    /**
     * The associated Vector<T> type.
     */
    using Vector = Scalar::Vector<T>;

    Vc_INTRINSIC Mask() = default;
    Vc_INTRINSIC explicit Mask(bool b) : m(b) {}
    Vc_INTRINSIC explicit Mask(VectorSpecialInitializerZero) : m(false) {}
    Vc_INTRINSIC explicit Mask(VectorSpecialInitializerOne) : m(true) {}
    Vc_INTRINSIC static Mask Zero() { return Mask(false); }
    Vc_INTRINSIC static Mask One() { return Mask(true); }

    // implicit cast
    template <typename U>
    Vc_INTRINSIC Mask(U &&rhs, Common::enable_if_mask_converts_implicitly<T, U> = nullarg)
        : m(rhs.m) {}

    // explicit cast, implemented via simd_cast (in scalar/simd_cast_caller.h)
    template <typename U>
    Vc_INTRINSIC_L explicit Mask(U &&rhs,
                                 Common::enable_if_mask_converts_explicitly<T, U> =
                                     nullarg) Vc_INTRINSIC_R;

        Vc_ALWAYS_INLINE explicit Mask(const bool *mem) : m(mem[0]) {}
        template<typename Flags> Vc_ALWAYS_INLINE explicit Mask(const bool *mem, Flags) : m(mem[0]) {}

        Vc_ALWAYS_INLINE void load(const bool *mem) { m = mem[0]; }
        template<typename Flags> Vc_ALWAYS_INLINE void load(const bool *mem, Flags) { m = mem[0]; }

        Vc_ALWAYS_INLINE void store(bool *mem) const { *mem = m; }
        template<typename Flags> Vc_ALWAYS_INLINE void store(bool *mem, Flags) const { *mem = m; }

        Vc_ALWAYS_INLINE bool operator==(const Mask &rhs) const { return m == rhs.m; }
        Vc_ALWAYS_INLINE bool operator!=(const Mask &rhs) const { return m != rhs.m; }

        Vc_ALWAYS_INLINE Mask operator&&(const Mask &rhs) const { return Mask(m && rhs.m); }
        Vc_ALWAYS_INLINE Mask operator& (const Mask &rhs) const { return Mask(m && rhs.m); }
        Vc_ALWAYS_INLINE Mask operator||(const Mask &rhs) const { return Mask(m || rhs.m); }
        Vc_ALWAYS_INLINE Mask operator| (const Mask &rhs) const { return Mask(m || rhs.m); }
        Vc_ALWAYS_INLINE Mask operator^ (const Mask &rhs) const { return Mask(m ^  rhs.m); }
        Vc_ALWAYS_INLINE Mask operator!() const { return Mask(!m); }

        Vc_ALWAYS_INLINE Mask &operator&=(const Mask &rhs) { m &= rhs.m; return *this; }
        Vc_ALWAYS_INLINE Mask &operator|=(const Mask &rhs) { m |= rhs.m; return *this; }
        Vc_ALWAYS_INLINE Mask &operator^=(const Mask &rhs) { m ^= rhs.m; return *this; }

        Vc_ALWAYS_INLINE bool isFull () const { return  m; }
        Vc_ALWAYS_INLINE bool isNotEmpty() const { return m; }
        Vc_ALWAYS_INLINE bool isEmpty() const { return !m; }
        Vc_ALWAYS_INLINE bool isMix  () const { return false; }

        Vc_ALWAYS_INLINE bool data () const { return m; }
        Vc_ALWAYS_INLINE bool dataI() const { return m; }
        Vc_ALWAYS_INLINE bool dataD() const { return m; }

        Vc_ALWAYS_INLINE EntryReference operator[](size_t) { return m; }
        Vc_ALWAYS_INLINE bool operator[](size_t) const { return m; }

        Vc_ALWAYS_INLINE int count() const { return m ? 1 : 0; }

        /**
         * Returns the index of the first one in the mask.
         *
         * The return value is undefined if the mask is empty.
         */
        Vc_ALWAYS_INLINE int firstOne() const { return 0; }
        Vc_ALWAYS_INLINE int toInt() const { return m ? 1 : 0; }

        template <typename G> static Vc_INTRINSIC Mask generate(G &&gen)
        {
            return Mask(gen(0));
        }

        Vc_INTRINSIC Vc_PURE Mask shifted(int amount) const
        {
            if (amount == 0) {
                return *this;
            } else {
                return Zero();
            }
        }

        ///\internal Called indirectly from operator[]
        void setEntry(size_t, bool x) { m = x; }

    private:
        bool m;
};
template <typename T> constexpr size_t Mask<T, VectorAbi::Scalar>::Size;
template <typename T> constexpr size_t Mask<T, VectorAbi::Scalar>::MemoryAlignment;

}  // namespace Vc

#endif // VC_SCALAR_MASK_H_
