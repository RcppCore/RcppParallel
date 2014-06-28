/*
    Copyright 2005-2014 Intel Corporation.  All Rights Reserved.

    This file is part of Threading Building Blocks.

    Threading Building Blocks is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    Threading Building Blocks is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Threading Building Blocks; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    As a special exception, you may use this file as part of a free software
    library without restriction.  Specifically, if other files instantiate
    templates or use macros or inline functions from this file, or you compile
    this file and link it with other files to produce an executable, this
    file does not by itself cause the resulting executable to be covered by
    the GNU General Public License.  This exception does not however
    invalidate any other reasons why the executable file might be covered by
    the GNU General Public License.
*/


#if (_WIN32 || _WIN64)
// As the test is intentionally build with /EHs-, suppress multiple VS2005's 
// warnings like C4530: C++ exception handler used, but unwind semantics are not enabled
#if defined(_MSC_VER) && !__INTEL_COMPILER
/* ICC 10.1 and 11.0 generates code that uses std::_Raise_handler,
   but it's only defined in libcpmt(d), which the test doesn't linked with.
 */
#undef  _HAS_EXCEPTIONS
#define _HAS_EXCEPTIONS _CPPUNWIND
#endif
// to use strdup and putenv w/o warnings
#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif // _WIN32 || _WIN64

#define HARNESS_NO_PARSE_COMMAND_LINE 1
// LD_PRELOAD mechanism is broken in offload
#if __TBB_MIC_OFFLOAD
#define HARNESS_SKIP_TEST 1
#endif
#include "harness.h"

#if __linux__
#define MALLOC_REPLACEMENT_AVAILABLE 1
#elif _WIN32 && !__MINGW32__ && !__MINGW64__ && !__TBB_WIN8UI_SUPPORT
#define MALLOC_REPLACEMENT_AVAILABLE 2
#include "tbb/tbbmalloc_proxy.h"
#endif

#if MALLOC_REPLACEMENT_AVAILABLE

#include "harness_report.h"
#include "harness_assert.h"
#include "harness_defs.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <new>

#if __linux__
#include <dlfcn.h>
#include <unistd.h> // for sysconf
#include <stdint.h> // for uintptr_t

extern "C" {
void *__libc_malloc(size_t size);
void *__libc_realloc(void *ptr, size_t size);
void *__libc_calloc(size_t num, size_t size);
void __libc_free(void *ptr);
void *__libc_memalign(size_t alignment, size_t size);
void *__libc_pvalloc(size_t size);
void *__libc_valloc(size_t size);
#if __ANDROID__
#define malloc_usable_size(p) dlmalloc_usable_size(p)
size_t dlmalloc_usable_size(const void *ptr);
#endif
}

#elif _WIN32
#include <stddef.h>
#if __MINGW32__
#include <unistd.h>
#else
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#endif

#endif /* OS selection */

#if _WIN32
// On Windows, the trick with string "dependence on msvcpXX.dll" is necessary to create 
// dependence on msvcpXX.dll, for sake of a regression test.
// On Linux, C++ RTL headers are undesirable because of breaking strict ANSI mode.
#if defined(_MSC_VER) && _MSC_VER >= 1300 && _MSC_VER <= 1310 && !defined(__INTEL_COMPILER)
/* Fixing compilation error reported by VS2003 for exception class
   when _HAS_EXCEPTIONS is 0: 
   bad_cast that inherited from exception is not in std namespace.
*/
using namespace std;
#endif
#include <string>
#endif


template<typename T>
static inline T alignDown(T arg, uintptr_t alignment) {
    return T( (uintptr_t)arg  & ~(alignment-1));
}
template<typename T>
static inline bool isAligned(T arg, uintptr_t alignment) {
    return 0==((uintptr_t)arg &  (alignment-1));
}

/* start of code replicated from src/tbbmalloc */

class BackRefIdx { // composite index to backreference array
private:
    uint16_t master;      // index in BackRefMaster
    uint16_t largeObj:1;  // is this object "large"?
    uint16_t offset  :15; // offset from beginning of BackRefBlock
public:
    BackRefIdx() : master((uint16_t)-1) {}
    bool isInvalid() { return master == (uint16_t)-1; }
    bool isLargeObject() const { return largeObj; }
    uint16_t getMaster() const { return master; }
    uint16_t getOffset() const { return offset; }

    // only newBackRef can modify BackRefIdx
    static BackRefIdx newBackRef(bool largeObj);
};

class ExtMemoryPool;

class BlockI {
    intptr_t     blockState[2];
};

struct LargeMemoryBlock : public BlockI {
    LargeMemoryBlock *next,          // ptrs in list of cached blocks
                     *prev,
                     *gPrev,         // in pool's global list 
                     *gNext;
    uintptr_t         age;           // age of block while in cache
    size_t            objectSize;    // the size requested by a client
    size_t            unalignedSize; // the size requested from getMemory
    bool              fromMapMemory;
    BackRefIdx        backRefIdx;    // cached here, used copy is in LargeObjectHdr
    void registerInPool(ExtMemoryPool *extMemPool);
    void unregisterFromPool(ExtMemoryPool *extMemPool);
};

struct LargeObjectHdr {
    LargeMemoryBlock *memoryBlock;
    /* Have to duplicate it here from CachedObjectHdr, 
       as backreference must be checked without further pointer dereference.
       Points to LargeObjectHdr. */
    BackRefIdx       backRefIdx;
};

/*
 * Objects of size minLargeObjectSize and larger are considered large objects.
 */
const uintptr_t blockSize = 16*1024;
#if __powerpc64__ || __ppc64__ || __bgp__
const int estimatedCacheLineSize = 128;
#else
const int estimatedCacheLineSize =  64;
#endif
const uint32_t fittingAlignment = estimatedCacheLineSize;
#define SET_FITTING_SIZE(N) ( (blockSize-2*estimatedCacheLineSize)/N ) & ~(fittingAlignment-1)
const uint32_t fittingSize5 = SET_FITTING_SIZE(2); // 8128/8064
#undef SET_FITTING_SIZE
const uint32_t minLargeObjectSize = fittingSize5 + 1;

/* end of code replicated from src/tbbmalloc */

/* Correct only for large blocks, i.e. not smaller then minLargeObjectSize */
static bool scalableMallocLargeBlock(void *object, size_t size)
{
    ASSERT(size >= minLargeObjectSize, NULL);
#if MALLOC_REPLACEMENT_AVAILABLE == 1
    ASSERT(malloc_usable_size(object) >= size, NULL);
#elif MALLOC_REPLACEMENT_AVAILABLE == 2
    // Check that _msize works correctly
    ASSERT(_msize(object) >= size, NULL);
    ASSERT(_aligned_msize(object,16,0) >= size, NULL);
#endif

    LargeMemoryBlock *lmb = ((LargeObjectHdr*)object-1)->memoryBlock;
    return uintptr_t(lmb)<uintptr_t(((LargeObjectHdr*)object-1)) && lmb->objectSize==size;
}

struct BigStruct {
    char f[minLargeObjectSize];
};

void CheckStdFuncOverload(void *(*malloc_p)(size_t), void *(*calloc_p)(size_t, size_t),
                          void *(*realloc_p)(void *, size_t), void (*free_p)(void *))
{
    void *ptr = malloc_p(minLargeObjectSize);
    ASSERT(ptr!=NULL && scalableMallocLargeBlock(ptr, minLargeObjectSize), NULL);
    free(ptr);

    ptr = calloc_p(minLargeObjectSize, 2);
    ASSERT(ptr!=NULL && scalableMallocLargeBlock(ptr, minLargeObjectSize*2), NULL);
    void *ptr1 = realloc_p(ptr, minLargeObjectSize*10);
    ASSERT(ptr1!=NULL && scalableMallocLargeBlock(ptr1, minLargeObjectSize*10), NULL);
    free_p(ptr1);

}

#if MALLOC_REPLACEMENT_AVAILABLE == 1

void CheckUnixAlignFuncOverload(void *(*memalign_p)(size_t, size_t),
                                void *(*valloc_p)(size_t), void (*free_p)(void*))
{
    void *ptr = memalign_p(128, 4*minLargeObjectSize);
    ASSERT(ptr!=NULL && scalableMallocLargeBlock(ptr, 4*minLargeObjectSize), NULL);
    free_p(ptr);

    ptr = valloc_p(minLargeObjectSize);
    ASSERT(ptr!=NULL && isAligned(ptr, sysconf(_SC_PAGESIZE)) &&
           scalableMallocLargeBlock(ptr, minLargeObjectSize), NULL);
    free_p(ptr);
}

#if __TBB_PVALLOC_PRESENT
void CheckPvalloc(void *(*pvalloc_p)(size_t), void (*free_p)(void*))
{
    long memoryPageSize = sysconf(_SC_PAGESIZE);
    int sz = 1024*minLargeObjectSize;
    void *ptr = pvalloc_p(sz);
    ASSERT(ptr!=NULL &&                // align size up to the page size
           scalableMallocLargeBlock(ptr, ((sz-1) | (memoryPageSize-1)) + 1), NULL);
    free_p(ptr);
}
#else
#define CheckPvalloc(alloc_p, free_p) ((void)0)
#endif

#endif // MALLOC_REPLACEMENT_AVAILABLE

#if __ANDROID__
// Workaround for an issue with strdup somehow bypassing our malloc replacement on Android.
char *strdup(const char *str) {
    REPORT( "Known issue: malloc replacement does not work for strdup on Android.\n" );
    size_t len = strlen(str)+1;
    void *new_str = malloc(len);
    return new_str ? reinterpret_cast<char *>(memcpy(new_str, str, len)) : 0;
}
#endif

int TestMain() {
    void *ptr, *ptr1;

#if MALLOC_REPLACEMENT_AVAILABLE == 1
    ASSERT(dlsym(RTLD_DEFAULT, "scalable_malloc"),
           "Lost dependence on malloc_proxy or LD_PRELOAD was not set?");
#endif

/* On Windows, memory block size returned by _msize() is sometimes used
   to calculate the size for an extended block. Substituting _msize,
   scalable_msize initially returned 0 for regions not allocated by the scalable
   allocator, which led to incorrect memory reallocation and subsequent crashes.
   It was found that adding a new environment variable triggers the error.
*/
    ASSERT(getenv("PATH"), "We assume that PATH is set everywhere.");
    char *pathCopy = strdup(getenv("PATH"));
#if __ANDROID__
    ASSERT(strcmp(pathCopy,getenv("PATH")) == 0, "strdup workaround does not work as expected.");
#endif
    const char *newEnvName = "__TBBMALLOC_OVERLOAD_REGRESSION_TEST_FOR_REALLOC_AND_MSIZE";
    char *newEnv = (char*)malloc(3 + strlen(newEnvName));

    ASSERT(!getenv(newEnvName), "Environment variable should not be used before.");
    strcpy(newEnv, newEnvName);
    strcat(newEnv, "=1");
    int r = putenv(newEnv);
    ASSERT(!r, NULL);
    char *path = getenv("PATH");
    ASSERT(path && 0==strcmp(path, pathCopy), "Environment was changed erroneously.");
    free(pathCopy);
    free(newEnv);

    CheckStdFuncOverload(malloc, calloc, realloc, free);
#if MALLOC_REPLACEMENT_AVAILABLE == 1

#if __TBB_POSIX_MEMALIGN_PRESENT
    int ret = posix_memalign(&ptr, 1024, 3*minLargeObjectSize);
    ASSERT(0==ret && ptr!=NULL && scalableMallocLargeBlock(ptr, 3*minLargeObjectSize), NULL);
    free(ptr);
#endif

    CheckUnixAlignFuncOverload(memalign, valloc, free);
    CheckPvalloc(pvalloc, free);

    struct mallinfo info = mallinfo();
    // right now mallinfo initialized by zero
    ASSERT(!info.arena && !info.ordblks && !info.smblks && !info.hblks
           && !info.hblkhd && !info.usmblks && !info.fsmblks
           && !info.uordblks && !info.fordblks && !info.keepcost, NULL);

#if __linux__ && !__ANDROID__
    // Those non-standart functions are exported by GLIBC, and might be used
    // in conjunction with standart malloc/free. Test that we ovrload them as well.
    // Bionic doesn't have them.
    CheckStdFuncOverload(__libc_malloc, __libc_calloc, __libc_realloc, __libc_free);
    CheckUnixAlignFuncOverload(__libc_memalign, __libc_valloc, __libc_free);
    CheckPvalloc(__libc_pvalloc, __libc_free);
#endif // __linux__

#elif MALLOC_REPLACEMENT_AVAILABLE == 2

    ptr = _aligned_malloc(minLargeObjectSize,16);
    ASSERT(ptr!=NULL && scalableMallocLargeBlock(ptr, minLargeObjectSize), NULL);

    // Testing of workaround for vs "is power of 2 pow N" bug that accepts zeros
    ptr1 = _aligned_malloc(minLargeObjectSize,0);
    ASSERT(ptr1!=NULL, NULL);
    _aligned_free(ptr1);

    ptr1 = _aligned_realloc(ptr, minLargeObjectSize*10,16);
    ASSERT(ptr1!=NULL && scalableMallocLargeBlock(ptr1, minLargeObjectSize*10), NULL);
    _aligned_free(ptr1);

#endif

    BigStruct *f = new BigStruct;
    ASSERT(f!=NULL && scalableMallocLargeBlock(f, sizeof(BigStruct)), NULL);
    delete f;

    f = new BigStruct[10];
    ASSERT(f!=NULL && scalableMallocLargeBlock(f, 10*sizeof(BigStruct)), NULL);
    delete []f;

    f = new(std::nothrow) BigStruct;
    ASSERT(f!=NULL && scalableMallocLargeBlock(f, sizeof(BigStruct)), NULL);
    delete f;

    f = new(std::nothrow) BigStruct[2];
    ASSERT(f!=NULL && scalableMallocLargeBlock(f, 2*sizeof(BigStruct)), NULL);
    delete []f;

#if _WIN32
    std::string stdstring = "dependence on msvcpXX.dll";
    ASSERT(strcmp(stdstring.c_str(), "dependence on msvcpXX.dll") == 0, NULL);
#endif

    return Harness::Done;
}

#else  /* !MALLOC_REPLACEMENT_AVAILABLE */
#include <stdio.h>

int TestMain() {
    return Harness::Skipped;
}
#endif /* !MALLOC_REPLACEMENT_AVAILABLE */
