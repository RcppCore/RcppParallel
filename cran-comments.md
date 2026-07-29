## RcppParallel 6.2.0

This release follows closely on 6.1.1. We apologize for the quick turnaround;
it repairs a regression that leaves Windows users of RcppParallel unable to
build some downstream packages.

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
