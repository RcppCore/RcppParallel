# RcppParallel (development version)

* On macOS, `RcppParallel::LdFlags()` now also emits an `-rpath` entry for the
  directory containing the TBB libraries. The libraries record an
  `@rpath`-relative install name, so packages linking against them previously
  produced binaries with no runtime search path for TBB; those binaries could
  only be loaded when RcppParallel (and hence TBB) already happened to be
  loaded into the process, and failed with "Library not loaded:
  @rpath/libtbb.dylib" otherwise. (#209)

* Fixed an issue where compiling code including `tbb/parallel_for_each.h`
  could fail with toolchains that accept `-std=c++20` but provide a
  pre-C++20 standard library, with errors of the form "no member named
  'random_access_iterator' in namespace 'std'". This affected CRAN's macOS
  x86_64 machines, which pair Apple clang 14 with the macOS 11.3 SDK.

* Fixed an issue where building the bundled oneTBB could fail when `CXX`
  (or `CC`) was configured with a leading compiler launcher such as `ccache`
  (e.g. `CXX = "ccache g++"`). The launcher is now forwarded to cmake via
  `CMAKE_<LANG>_COMPILER_LAUNCHER` instead of being mistaken for the compiler
  itself.


# RcppParallel 6.1.1

* Fixed an issue where package installation could fail if `cmake` was not
  available on the `PATH`, even when it was discoverable at another known
  location (e.g. `/Applications/CMake.app/Contents/bin/cmake` on macOS).
  This caused installation failures on CRAN's macOS machines, where `cmake`
  is not on the `PATH` by default.

* Removed vestigial compiler / flag detection code from the configure
  script. This code has been unused since the switch to a cmake-driven
  build of the bundled oneTBB, and probed `R CMD config` variables that
  are defunct in R (>= 4.6.0).


# RcppParallel 6.1.0

* RcppParallel now provides `isProcessForkedChild()` (R) and
  `RcppParallel::isProcessForkedChild()` (C++), which return `TRUE` when the
  current process is a `fork()` of the process in which RcppParallel was
  loaded.
  Packages dispatching parallel work from within `parallel::mclapply()` (or
  similar) should consult this and fall back to a serial path, as TBB does
  not support use after fork. (#243, #244)

* The TBB backend is now enabled by default on musl-based Linux
  distributions, such as Alpine Linux. Previously, TBB was only enabled by
  default with glibc-based toolchains on Linux. (#231, #263)

* The mingw cpuid guard applied to TBB's `_machine.h` header during
  installation is now logged, and a warning is emitted if the header does
  not have the expected form and the guard cannot be applied. (#265)

* On Linux, the bundled TBB libraries are once again installed with versioned
  names (e.g. `libtbb.so.2`) plus an unversioned `libtbb.so` symlink, matching
  the layout shipped by RcppParallel 5.1.11 and earlier. The oneTBB cmake build
  produces only unversioned libraries on Linux, so binaries compiled against
  those releases (which recorded a load-time dependency on `libtbb.so.2`) would
  otherwise fail to load after an upgrade with "libtbb.so.2: cannot open shared
  object file". (#260)

* Fixed linking of downstream packages using the TBB scalable allocator
  on Windows, e.g. via RcppArmadillo's `ARMA_USE_TBB_ALLOC`. RcppParallel
  now links the whole Rtools `tbbmalloc` archive into `RcppParallel.dll`
  and re-exports its API, so that `scalable_malloc`, `scalable_free`, and
  friends can be resolved by packages linking with `-lRcppParallel`. (#262)

* Fixed installation on Windows toolchains providing an older (non-oneTBB)
  copy of TBB, e.g. Rtools42: the tbb stub library is now built by
  re-exporting the static TBB library, rather than wrapping the oneTBB
  runtime (which is unavailable there). In addition, stale stub build
  artifacts from a different toolchain are no longer reused. (#258)

* Fixed installation on Windows systems whose Rtools does not provide TBB
  (R < 4.2.0): configure no longer requires cmake there, and the tbb stub
  library is no longer built when the TBB backend is disabled. (#257)

* RcppParallel now reports which TBB headers and libraries are installed
  with the package, and from where, during package installation. In
  addition, setting the `VERBOSE` environment variable to a value other
  than `0` enables diagnostics describing how TBB libraries are resolved
  and loaded when the package is loaded. (#256, #259)

* On Windows, RcppParallel once again loads its compatibility stub library
  (`tbb.dll`) when the package is loaded. Packages linking with `-ltbb`
  (e.g. via StanHeaders) record a load-time dependency on `tbb.dll`, which
  can only be resolved if RcppParallel has already loaded it; with
  RcppParallel 6.0.0, such packages would fail to load with "LoadLibrary
  failure: The specified module could not be found". (#249, #250)

* The TBB headers installed with RcppParallel (whether from Rtools or from
  the bundled copy of oneTBB) now guard against GCC's `<cpuid.h>` being
  included before `<intrin.h>` on Windows (mingw). Previously, translation
  units including `<cpuid.h>` before any TBB header would fail to compile,
  as the `__cpuid` macro from `<cpuid.h>` conflicts with the `__cpuid()`
  function declared by mingw's `<intrin.h>`. (#248, #253)

* When building the bundled copy of oneTBB, RcppParallel no longer searches
  for hwloc, and so no longer tries to build the optional 'tbbbind' library.
  This fixes build failures on machines where a static hwloc library is
  discoverable via pkg-config, as on the CRAN macOS machines. (#247)

* On macOS, the bundled copy of oneTBB is now built with
  `__TBB_RESUMABLE_TASKS_USE_THREADS`, avoiding use of the deprecated
  ucontext APIs (`getcontext`, `swapcontext`, `makecontext`). (#247)


# RcppParallel 6.0.0

* RcppParallel no longer includes tbb headers as part of the RcppParallel/TBB.h
  header, and instead only exposes its TBB-specific APIs for parallel work.
  
* RcppParallel now bundles oneTBB 2022.0.0. Note that the TBB ABI has changed;
  packages which depend on RcppParallel may need to be rebuilt.
  
* On Windows, RcppParallel now uses the copy of TBB provided by Rtools.
  If TBB is not available, RcppParallel will use only the fallback 'tinythread'
  implementation. In practice, this implies that RcppParallel will now only
  provide a TBB backend with R (>= 4.2.0).

* Fixed builds under wasm/webR. (#237; @andrjohns)

* Fixed compilation with clang-19 on Windows aarch64. (#235, #236; @andrjohns)

* Fixed TBB library lookup on Windows, and removed the obsolete
  `TBB_USE_GCC_BUILTINS` flag for Windows ARM64. TBB is statically linked
  on Windows, so the package no longer tries to load TBB libraries there
  at load time. (#241; @andrjohns)

# RcppParallel 5.1.11-2

* Resolved compilation warnings with C++20 and Apple clang 21.

# RcppParallel 5.1.11

* Compatibility fixes for LLVM 21.

# RcppParallel 5.1.10

* Fixed an issue where packages linking to RcppParallel could inadverently
  depend on internals of the TBB library available during compilation, even
  if the package did not explicitly use TBB itself.

# RcppParallel 5.1.9

* RcppParallel no longer passes `-rpath` when building / linking on Windows.
  This fixes build issues when building RcppParallel when using the LLVM
  linker on Windows. (@kalibera)
  
# RcppParallel 5.1.8

* RcppParallel now explicitly links to the bundled copy of TBB on macOS. (#206; @jeroen)

# RcppParallel 5.1.7

* Remove deprecated `std::iterator`. (#192; @Enchufa2)

# RcppParallel 5.1.6

* Patch for TBB to allow compilation with gcc-13.

* Fixed a memory leak that could occur when using TinyThread on POSIX systems.
  (#185; @dipertix and and @kevinushey)

# RcppParallel 5.1.5

* Patches to ensure compatibility with the R 4.2.0 UCRT toolchain on Windows,
  adapted from patches contributed by Tomas Kalibera.

* Fixed an issue where setting `TBB_ROOT` (or `TBB_INC` / `TBB_LIB`) would
  copy rather than symlink the associated libraries. (#161)

# RcppParallel 5.1.4

* Fixed an issue causing client packages of RcppParallel to fail to compile
  on Solaris.

# RcppParallel 5.1.3

* Fixed an issue that prevented compilation of RcppParallel with R (< 4.0.0)
  of R on Windows.

* The `RCPP_PARALLEL_USE_TBBMALLOC_PROXY` environment variable can now be used
  to control whether RcppParallel loads the `tbbmalloc_proxy` library on load.
  See https://www.threadingbuildingblocks.org/docs/help/tbb_userguide/Automically_Replacing_malloc.html
  for more information.

# RcppParallel 5.1.2

* `RcppParallel` gains the `tbbLibraryPath()` function, to be used when attempting
  to query the location of the TBB libraries that `RcppParallel` has been
  configured to use. This may be useful for R packages which wish to explicitly
  use, or link to, these libraries.

# RcppParallel 5.1.1

* Updated bundled version of TBB (Intel TBB 2019 Update 8).

* RcppParallel can now be configured to use an external copy of TBB, via the
  `TBB_LIB` and `TBB_INC` environment variables. These should be set to the
  directories containing the TBB libraries and headers, respectively.
  
* Added support for the latest versions of Intel oneAPI TBB / oneTBB.

* Updated TBB functionality for the new interface.

* Falling back to building TBB from local source code.

* Backward TBB compatibility based on `__TBB_tbb_stddef_H`.

* Resolved conflicts between system and local TBB headers.

* Fixed URLs, used HTTPS, and minor cleanups.

* Updated package DESCRIPTION and bumped version.

* `setThreadOptions(...)` can again be called multiple times per session.
  The requested number of threads will be used for invocations to `parallelFor()`
  and `parallelReduce()` that don't explicitly request a specific number of threads.
  
* The `parallelFor()` and `parallelReduce()` functions gain the `numThreads`
  argument, allowing one to limit the number of threads used for a
  particular computation.

# RcppParallel 5.0.3

* Fixed compilation on macOS M1 machines.

# RcppParallel 5.0.2

* `setThreadOptions(...)` can now only be called once per session, to avoid
  segfaults when compiling RcppParallel / TBB with gcc 10.1. Subsequent
  calls to `setThreadOptions(...)` are ignored.

# RcppParallel 5.0.1

* Fixed compilation issue on OpenSUSE Tumbleweed with -flto=auto

* Fixed compilation when CPPFLAGS = -I/usr/local/include and a version
  of libtbb is installed there

# RcppParallel 5.0.0

* RcppParallel backend can now be customized with RCPP_PARALLEL_BACKEND
  environment variable (supported values are 'tbb' and 'tinythread')
  
* Fixed issue when compiling RcppParallel on macOS Catalina

* Fixed issue when compiling RcppParallel with Rtools40

# RcppParallel 4.4.4

* Fixed an issue when compiling RcppParallel with clang-9 on Fedora

# RcppParallel 4.4.3

* Suppress gcc-9 warnings related -Wclass-memaccess

* Added TBB headers for serial TBB operations (#90, @mikejiang)

* Fixed row iterator constructor (#87, @wtianyi)

* Fixed compilation on FreeBSD

# RcppParallel 4.4.2

* Suppress gcc-8 warnings related to -Wclass-memaccess

* Use PKG_CXXFLAGS rather than PKG_CPPFLAGS

* Remove unused dependency on the BH package

# RcppParallel 4.4.1

* Ensure user-specified R configuration passed to TBB

* Work around warnings emitted by gcc 8

# RcppParallel 4.4.0

* Respect user-defined compiler settings (e.g. from ~/.R/Makevars).

* Remove TBB's attempts to suppress compiler diagnostics.

* Allow setting the number of threads to use via RCPP_PARALLEL_NUM_THREADS
  environment variable.

* Update to TBB 2018 Update 1.

* Add native registration of compiled functions.

# RcppParallel 4.3.20

* Add support for Rtools 3.3 w/ GCC 4.9

# RcppParallel 4.3.14

* Add support for TBB on Solaris

* Fix failure to compile on OS X Snow Leopard R toolchain

* Add const and non-const operator[] for RMatrix class

# RcppParallel 4.3.8

* Add tbbmalloc library

* Correctly pass clang to TBB configure when R is using clang

# RcppParallel 4.3.6

* Support for TBB on Windows

# RcppParallel 4.3.3

* Update to TBB 4.3 (fixes clang compilation error in platform.h)

* Forward CXX to TBB Makefile

# RcppParallel 4.2.5

* Initial release
