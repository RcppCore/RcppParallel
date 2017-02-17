/*  This file is part of the Vc library. {{{
Copyright © 2012-2015 Matthias Kretz <kretz@kde.org>
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

#include "unittest-old.h"

//#define QUICK 1

using namespace Vc;

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;

static_assert(!std::is_convertible< float_v, double_v>::value, "!std::is_convertible< float_v, double_v>");
static_assert(!std::is_convertible<   int_v, double_v>::value, "!std::is_convertible<   int_v, double_v>");
static_assert(!std::is_convertible<  uint_v, double_v>::value, "!std::is_convertible<  uint_v, double_v>");
static_assert(!std::is_convertible< short_v, double_v>::value, "!std::is_convertible< short_v, double_v>");
static_assert(!std::is_convertible<ushort_v, double_v>::value, "!std::is_convertible<ushort_v, double_v>");

static_assert(!std::is_convertible<double_v,  float_v>::value, "!std::is_convertible<double_v,  float_v>");
static_assert(!std::is_convertible<   int_v,  float_v>::value, "!std::is_convertible<   int_v,  float_v>");
static_assert(!std::is_convertible<  uint_v,  float_v>::value, "!std::is_convertible<  uint_v,  float_v>");
static_assert(!std::is_convertible< short_v,  float_v>::value, "!std::is_convertible< short_v,  float_v>");
static_assert(!std::is_convertible<ushort_v,  float_v>::value, "!std::is_convertible<ushort_v,  float_v>");

static_assert(!std::is_convertible<double_v,    int_v>::value, "!std::is_convertible<double_v,    int_v>");
static_assert(!std::is_convertible< float_v,    int_v>::value, "!std::is_convertible< float_v,    int_v>");
static_assert( std::is_convertible<  uint_v,    int_v>::value, " std::is_convertible<  uint_v,    int_v>");
static_assert(!std::is_convertible< short_v,    int_v>::value, "!std::is_convertible< short_v,    int_v>");
static_assert(!std::is_convertible<ushort_v,    int_v>::value, "!std::is_convertible<ushort_v,    int_v>");

static_assert(!std::is_convertible<double_v,   uint_v>::value, "!std::is_convertible<double_v,   uint_v>");
static_assert(!std::is_convertible< float_v,   uint_v>::value, "!std::is_convertible< float_v,   uint_v>");
static_assert( std::is_convertible<   int_v,   uint_v>::value, " std::is_convertible<   int_v,   uint_v>");
static_assert(!std::is_convertible< short_v,   uint_v>::value, "!std::is_convertible< short_v,   uint_v>");
static_assert(!std::is_convertible<ushort_v,   uint_v>::value, "!std::is_convertible<ushort_v,   uint_v>");

static_assert(!std::is_convertible<double_v,  short_v>::value, "!std::is_convertible<double_v,  short_v>");
static_assert(!std::is_convertible< float_v,  short_v>::value, "!std::is_convertible< float_v,  short_v>");
static_assert(!std::is_convertible<   int_v,  short_v>::value, "!std::is_convertible<   int_v,  short_v>");
static_assert(!std::is_convertible<  uint_v,  short_v>::value, "!std::is_convertible<  uint_v,  short_v>");
static_assert( std::is_convertible<ushort_v,  short_v>::value, " std::is_convertible<ushort_v,  short_v>");

static_assert(!std::is_convertible<double_v, ushort_v>::value, "!std::is_convertible<double_v, ushort_v>");
static_assert(!std::is_convertible< float_v, ushort_v>::value, "!std::is_convertible< float_v, ushort_v>");
static_assert(!std::is_convertible<   int_v, ushort_v>::value, "!std::is_convertible<   int_v, ushort_v>");
static_assert(!std::is_convertible<  uint_v, ushort_v>::value, "!std::is_convertible<  uint_v, ushort_v>");
static_assert( std::is_convertible< short_v, ushort_v>::value, " std::is_convertible< short_v, ushort_v>");

#ifdef QUICK
#define _TYPE_TEST(a, b, c)
#else
#if defined(Vc_GCC) && Vc_GCC == 0x40801
// Skipping tests involving operator& because of a bug in GCC 4.8.1 (http://gcc.gnu.org/bugzilla/show_bug.cgi?id=57532)
#define _TYPE_TEST(a, b, c) \
    static_assert(std::is_same<decltype(a() *  b()), c>::value, #a " *  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() /  b()), c>::value, #a " /  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() +  b()), c>::value, #a " +  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() -  b()), c>::value, #a " -  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() |  b()), c>::value, #a " |  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() ^  b()), c>::value, #a " ^  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() == b()), c::Mask>::value, #a " == " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() != b()), c::Mask>::value, #a " != " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() <= b()), c::Mask>::value, #a " <= " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() >= b()), c::Mask>::value, #a " >= " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() <  b()), c::Mask>::value, #a " <  " #b " => " #c "::Mask"); \
    COMPARE(typeid(a() * b()), typeid(c)); \
    COMPARE(typeid(a() / b()), typeid(c)); \
    COMPARE(typeid(a() + b()), typeid(c)); \
    COMPARE(typeid(a() - b()), typeid(c)); \
    COMPARE(typeid(a() | b()), typeid(c)); \
    COMPARE(typeid(a() ^ b()), typeid(c)); \
    COMPARE(typeid(a() == b()), typeid(c::Mask)); \
    COMPARE(typeid(a() != b()), typeid(c::Mask)); \
    COMPARE(typeid(a() <= b()), typeid(c::Mask)); \
    COMPARE(typeid(a() >= b()), typeid(c::Mask)); \
    COMPARE(typeid(a() <  b()), typeid(c::Mask));
#else
#define _TYPE_TEST(a, b, c) \
    static_assert(std::is_same<decltype(a() *  b()), c>::value, #a " *  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() /  b()), c>::value, #a " /  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() +  b()), c>::value, #a " +  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() -  b()), c>::value, #a " -  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() &  b()), c>::value, #a " &  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() |  b()), c>::value, #a " |  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() ^  b()), c>::value, #a " ^  " #b " => " #c); \
    static_assert(std::is_same<decltype(a() == b()), c::Mask>::value, #a " == " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() != b()), c::Mask>::value, #a " != " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() <= b()), c::Mask>::value, #a " <= " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() >= b()), c::Mask>::value, #a " >= " #b " => " #c "::Mask"); \
    static_assert(std::is_same<decltype(a() <  b()), c::Mask>::value, #a " <  " #b " => " #c "::Mask"); \
    COMPARE(typeid(a() * b()), typeid(c)); \
    COMPARE(typeid(a() / b()), typeid(c)); \
    COMPARE(typeid(a() + b()), typeid(c)); \
    COMPARE(typeid(a() - b()), typeid(c)); \
    COMPARE(typeid(a() & b()), typeid(c)); \
    COMPARE(typeid(a() | b()), typeid(c)); \
    COMPARE(typeid(a() ^ b()), typeid(c)); \
    COMPARE(typeid(a() == b()), typeid(c::Mask)); \
    COMPARE(typeid(a() != b()), typeid(c::Mask)); \
    COMPARE(typeid(a() <= b()), typeid(c::Mask)); \
    COMPARE(typeid(a() >= b()), typeid(c::Mask)); \
    COMPARE(typeid(a() <  b()), typeid(c::Mask));
#endif
#endif

#define TYPE_TEST(a, b, c) \
    _TYPE_TEST(a, b, c) \
    COMPARE(typeid(a() >  b()), typeid(c::Mask))

template<typename T>
struct TestImplicitCast {
    static bool test(const T &) { return  true; }
    static bool test(   ...   ) { return false; }
};

enum SomeEnum { EnumValue = 0 };
SomeEnum Enum() { return EnumValue; }

void testImplicitTypeConversions()
{
    VERIFY( TestImplicitCast<     int>::test(double()));
    VERIFY( TestImplicitCast<     int>::test( float()));
    VERIFY( TestImplicitCast<     int>::test(  Enum()));
    VERIFY( TestImplicitCast<     int>::test( short()));
    VERIFY( TestImplicitCast<     int>::test(ushort()));
    VERIFY( TestImplicitCast<     int>::test(  char()));
    VERIFY( TestImplicitCast<     int>::test(  uint()));
    VERIFY( TestImplicitCast<     int>::test(  long()));
    VERIFY( TestImplicitCast<     int>::test( ulong()));
    VERIFY( TestImplicitCast<     int>::test(  bool()));
    VERIFY( TestImplicitCast<double_v>::test(double()));
    VERIFY( TestImplicitCast<double_v>::test( float()));
    VERIFY( TestImplicitCast<double_v>::test(   int()));
    VERIFY( TestImplicitCast< float_v>::test( float()));
    VERIFY( TestImplicitCast<   int_v>::test(   int()));
    VERIFY( TestImplicitCast<  uint_v>::test(  uint()));
    VERIFY( TestImplicitCast< short_v>::test( short()));
    VERIFY( TestImplicitCast<ushort_v>::test(ushort()));
    VERIFY(!TestImplicitCast<double_v>::test(nullptr));
    VERIFY(!TestImplicitCast< float_v>::test(nullptr));
    VERIFY(!TestImplicitCast<   int_v>::test(nullptr));
    VERIFY(!TestImplicitCast<  uint_v>::test(nullptr));
    VERIFY(!TestImplicitCast< short_v>::test(nullptr));
    VERIFY(!TestImplicitCast<ushort_v>::test(nullptr));

    TYPE_TEST( double_v,    double_v, double_v);
    TYPE_TEST( double_v,      double, double_v);
    TYPE_TEST( double_v,       float, double_v);
    TYPE_TEST( double_v,       short, double_v);
    TYPE_TEST( double_v,      ushort, double_v);
    TYPE_TEST( double_v,         int, double_v);
    TYPE_TEST( double_v,        uint, double_v);
    TYPE_TEST( double_v,        long, double_v);
    TYPE_TEST( double_v,       ulong, double_v);
    TYPE_TEST( double_v,    longlong, double_v);
    TYPE_TEST( double_v,   ulonglong, double_v);
    TYPE_TEST( double_v,        Enum, double_v);
    TYPE_TEST( double_v,        bool, double_v);
    TYPE_TEST(   double,    double_v, double_v);
    TYPE_TEST(    float,    double_v, double_v);
    TYPE_TEST(    short,    double_v, double_v);
    TYPE_TEST(   ushort,    double_v, double_v);
    TYPE_TEST(      int,    double_v, double_v);
    TYPE_TEST(     uint,    double_v, double_v);
    TYPE_TEST(     long,    double_v, double_v);
    TYPE_TEST(    ulong,    double_v, double_v);
    TYPE_TEST( longlong,    double_v, double_v);
    TYPE_TEST(ulonglong,    double_v, double_v);
    TYPE_TEST(     Enum,    double_v, double_v);
    TYPE_TEST(     bool,    double_v, double_v);
    // double_v done

    TYPE_TEST(  float_v,     float_v,  float_v);
    TYPE_TEST(  float_v,       float,  float_v);
    TYPE_TEST(  float_v,       short,  float_v);
    TYPE_TEST(  float_v,      ushort,  float_v);
    TYPE_TEST(  float_v,         int,  float_v);
    TYPE_TEST(  float_v,        uint,  float_v);
    TYPE_TEST(  float_v,        long,  float_v);
    TYPE_TEST(  float_v,       ulong,  float_v);
    TYPE_TEST(  float_v,    longlong,  float_v);
    TYPE_TEST(  float_v,   ulonglong,  float_v);
    TYPE_TEST(  float_v,        Enum,  float_v);
    TYPE_TEST(  float_v,        bool,  float_v);
    TYPE_TEST(    float,     float_v,  float_v);
    TYPE_TEST(    short,     float_v,  float_v);
    TYPE_TEST(   ushort,     float_v,  float_v);
    TYPE_TEST(      int,     float_v,  float_v);
    TYPE_TEST(     uint,     float_v,  float_v);
    TYPE_TEST(     long,     float_v,  float_v);
    TYPE_TEST(    ulong,     float_v,  float_v);
    TYPE_TEST( longlong,     float_v,  float_v);
    TYPE_TEST(ulonglong,     float_v,  float_v);
    TYPE_TEST(     Enum,     float_v,  float_v);
    TYPE_TEST(     bool,     float_v,  float_v);
    // double_v + float_v done

    TYPE_TEST(  short_v,     short_v,  short_v);
    TYPE_TEST(  short_v,       short,  short_v);
    TYPE_TEST(  short_v,    ushort_v, ushort_v);
    TYPE_TEST(  short_v,      ushort, ushort_v);
    TYPE_TEST(  short_v,         int,  short_v);
    TYPE_TEST(  short_v,        uint, ushort_v);
    TYPE_TEST(  short_v,        long,  short_v);
    TYPE_TEST(  short_v,       ulong, ushort_v);
    TYPE_TEST(  short_v,    longlong,  short_v);
    TYPE_TEST(  short_v,   ulonglong, ushort_v);
    TYPE_TEST(  short_v,        Enum,  short_v);
    TYPE_TEST(  short_v,        bool,  short_v);
    TYPE_TEST(    short,     short_v,  short_v);
    TYPE_TEST( ushort_v,     short_v, ushort_v);
    TYPE_TEST(   ushort,     short_v, ushort_v);
    TYPE_TEST(      int,     short_v,  short_v);
    TYPE_TEST(     uint,     short_v, ushort_v);
    TYPE_TEST(     long,     short_v,  short_v);
    TYPE_TEST(    ulong,     short_v, ushort_v);
    TYPE_TEST( longlong,     short_v,  short_v);
    TYPE_TEST(ulonglong,     short_v, ushort_v);
    TYPE_TEST(     Enum,     short_v,  short_v);
    TYPE_TEST(     bool,     short_v,  short_v);
    // double_v + float_v + short_v done

    TYPE_TEST( ushort_v,       short, ushort_v);
    TYPE_TEST( ushort_v,    ushort_v, ushort_v);
    TYPE_TEST( ushort_v,      ushort, ushort_v);
    TYPE_TEST( ushort_v,         int, ushort_v);
    TYPE_TEST( ushort_v,        uint, ushort_v);
    TYPE_TEST( ushort_v,        long, ushort_v);
    TYPE_TEST( ushort_v,       ulong, ushort_v);
    TYPE_TEST( ushort_v,    longlong, ushort_v);
    TYPE_TEST( ushort_v,   ulonglong, ushort_v);
    TYPE_TEST( ushort_v,        Enum, ushort_v);
    TYPE_TEST( ushort_v,        bool, ushort_v);
    TYPE_TEST(    short,    ushort_v, ushort_v);
    TYPE_TEST(   ushort,    ushort_v, ushort_v);
    TYPE_TEST(      int,    ushort_v, ushort_v);
    TYPE_TEST(     uint,    ushort_v, ushort_v);
    TYPE_TEST(     long,    ushort_v, ushort_v);
    TYPE_TEST(    ulong,    ushort_v, ushort_v);
    TYPE_TEST( longlong,    ushort_v, ushort_v);
    TYPE_TEST(ulonglong,    ushort_v, ushort_v);
    TYPE_TEST(     Enum,    ushort_v, ushort_v);
    TYPE_TEST(     bool,    ushort_v, ushort_v);
    // double_v + float_v + short_v + ushort_v done

    TYPE_TEST(    int_v,      ushort,   uint_v);
    TYPE_TEST(    int_v,       short,    int_v);
    TYPE_TEST(    int_v,       int_v,    int_v);
    TYPE_TEST(    int_v,         int,    int_v);
    TYPE_TEST(    int_v,      uint_v,   uint_v);
    TYPE_TEST(    int_v,        uint,   uint_v);
    TYPE_TEST(    int_v,        long,    int_v);
    TYPE_TEST(    int_v,       ulong,   uint_v);
    TYPE_TEST(    int_v,    longlong,    int_v);
    TYPE_TEST(    int_v,   ulonglong,   uint_v);
    TYPE_TEST(    int_v,        Enum,    int_v);
    TYPE_TEST(    int_v,        bool,    int_v);
    TYPE_TEST(    int_v,       float,  float_v);
    TYPE_TEST(   ushort,       int_v,   uint_v);
    TYPE_TEST(    short,       int_v,    int_v);
    TYPE_TEST(      int,       int_v,    int_v);
    TYPE_TEST(   uint_v,       int_v,   uint_v);
    TYPE_TEST(     uint,       int_v,   uint_v);
    TYPE_TEST(     long,       int_v,    int_v);
    TYPE_TEST(    ulong,       int_v,   uint_v);
    TYPE_TEST( longlong,       int_v,    int_v);
    TYPE_TEST(ulonglong,       int_v,   uint_v);
    TYPE_TEST(     Enum,       int_v,    int_v);
    TYPE_TEST(     bool,       int_v,    int_v);
    TYPE_TEST(    float,       int_v,  float_v);

    TYPE_TEST(   uint_v,       short,   uint_v);
    TYPE_TEST(   uint_v,      ushort,   uint_v);
    TYPE_TEST(   uint_v,       int_v,   uint_v);
    TYPE_TEST(   uint_v,         int,   uint_v);
    TYPE_TEST(   uint_v,      uint_v,   uint_v);
    TYPE_TEST(   uint_v,        uint,   uint_v);
    TYPE_TEST(   uint_v,        long,   uint_v);
    TYPE_TEST(   uint_v,       ulong,   uint_v);
    TYPE_TEST(   uint_v,    longlong,   uint_v);
    TYPE_TEST(   uint_v,   ulonglong,   uint_v);
    TYPE_TEST(   uint_v,        Enum,   uint_v);
    TYPE_TEST(   uint_v,        bool,   uint_v);
    TYPE_TEST(   uint_v,       float,  float_v);
    TYPE_TEST(    short,      uint_v,   uint_v);
    TYPE_TEST(   ushort,      uint_v,   uint_v);
    TYPE_TEST(    int_v,      uint_v,   uint_v);
    TYPE_TEST(      int,      uint_v,   uint_v);
    TYPE_TEST(     uint,      uint_v,   uint_v);
    TYPE_TEST(     long,      uint_v,   uint_v);
    TYPE_TEST(    ulong,      uint_v,   uint_v);
    TYPE_TEST( longlong,      uint_v,   uint_v);
    TYPE_TEST(ulonglong,      uint_v,   uint_v);
    TYPE_TEST(     Enum,      uint_v,   uint_v);
    TYPE_TEST(     bool,      uint_v,   uint_v);
    TYPE_TEST(    float,      uint_v,  float_v);
}

void testmain()
{
    runTest(testImplicitTypeConversions);
}

// vim: foldmethod=marker
