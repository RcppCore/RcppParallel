## RcppParallel 6.2.0

This release follows closely on 6.1.1, and we apologize for the quick
turnaround. It fixes the installation failure currently reported for 6.1.1 on
r-release-macos-x86_64, along with a regression that leaves Windows users
unable to build some downstream packages from source.

### Installation failure on r-release-macos-x86_64

RcppParallel 6.1.1 fails to install on that machine, with:

    no member named 'random_access_iterator' in namespace 'std'

The bundled oneTBB guarded a concepts-based iterator dispatch in
`parallel_for_each.h` on a macro that only tests the language standard. With a
toolchain that accepts `-std=c++20` but provides a pre-C++20 standard library
-- Apple clang 14 with the macOS 11.3 SDK, as on that check machine -- it
therefore reached for `std::random_access_iterator`, which is not available.
oneTBB already defines `__TBB_CPP20_CONCEPTS_PRESENT` as 0 for clang, and
guards the rest of that header on it; this release uses it for the dispatch
block as well, so the pre-C++20 fallback is selected as intended.

### Downstream builds on Windows

Since 6.0.0, RcppParallel has linked the static TBB provided by Rtools on
Windows. That makes the TBB version, and its ABI, a property of the user's
toolchain rather than of RcppParallel: Rtools42 ships Intel TBB 2017, whose
headers downstream packages cannot build against (StanHeaders requires
`tbb::this_task_arena::isolate`, which that release gates behind a preview
macro and does not export), so rstan can no longer be built from source on
R 4.2 for Windows. It also left downstream packages with no TBB library to
link against.

RcppParallel now builds the bundled oneTBB as a shared library on Windows and
ships it with the package, as it already does on every other platform. As a
consequence, `RcppParallel::RcppParallelLibs()` now emits `-ltbb` and
`-ltbbmalloc` there in addition to `-lRcppParallel`. Packages that take their
linker flags from that function require no source changes; packages that
hard-coded `-lRcppParallel` to pick up TBB symbols will need to use it.

Building the bundled oneTBB requires cmake, which is now required on Windows
as well. This matches the `SystemRequirements: CMake (>= 3.5)` that DESCRIPTION
has always declared, and Rtools has shipped cmake since Rtools42, so it should
not affect Windows users in practice.

## R CMD check results

0 errors | 0 warnings | 1 note

The note is the incoming-feasibility check reporting the number of days since
the last update, for the reason described above.

## revdepcheck results

<!-- TODO: fill in from a fresh revdepcheck run against 6.2.0 -->
