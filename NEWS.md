
## RcppParallel 5.1.4

- Fixed an issue causing client packages of RcppParallel to fail to compile
  on Solaris.

## RcppParallel 5.1.3

* Fixed an issue that prevented compilation of RcppParallel with R (< 4.0.0)
  of R on Windows.

* The `RCPP_PARALLEL_USE_TBBMALLOC_PROXY` environment variable can now be used
  to control whether RcppParallel loads the `tbbmalloc_proxy` library on load.
  See https://www.threadingbuildingblocks.org/docs/help/tbb_userguide/Automically_Replacing_malloc.html
  for more information.

## RcppParallel 5.1.2

* `RcppParallel` gains the `tbbLibraryPath()` function, to be used when attempting
  to query the location of the TBB libraries that `RcppParallel` has been
  configured to use. This may be useful for R packages which wish to explicitly
  use, or link to, these libraries.

## RcppParallel 5.1.1

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

## RcppParallel 5.0.3

* Fixed compilation on macOS M1 machines.

## RcppParallel 5.0.2

* `setThreadOptions(...)` can now only be called once per session, to avoid
  segfaults when compiling RcppParallel / TBB with gcc 10.1. Subsequent
  calls to `setThreadOptions(...)` are ignored.

## RcppParallel 5.0.1

* Fixed compilation issue on OpenSUSE Tumbleweed with -flto=auto

* Fixed compilation when CPPFLAGS = -I/usr/local/include and a version
  of libtbb is installed there

## RcppParallel 5.0.0

* RcppParallel backend can now be customized with RCPP_PARALLEL_BACKEND
  environment variable (supported values are 'tbb' and 'tinythread')
  
* Fixed issue when compiling RcppParallel on macOS Catalina

* Fixed issue when compiling RcppParallel with Rtools40

## RcppParallel 4.4.4

* Fixed an issue when compiling RcppParallel with clang-9 on Fedora

## RcppParallel 4.4.3

* Suppress gcc-9 warnings related -Wclass-memaccess

* Added TBB headers for serial TBB operations (#90, @mikejiang)

* Fixed row iterator constructor (#87, @wtianyi)

* Fixed compilation on FreeBSD

## RcppParallel 4.4.2

* Suppress gcc-8 warnings related to -Wclass-memaccess

* Use PKG_CXXFLAGS rather than PKG_CPPFLAGS

* Remove unused dependency on the BH package

## RcppParallel 4.4.1

* Ensure user-specified R configuration passed to TBB

* Work around warnings emitted by gcc 8

## RcppParallel 4.4.0

* Respect user-defined compiler settings (e.g. from ~/.R/Makevars).

* Remove TBB's attempts to suppress compiler diagnostics.

* Allow setting the number of threads to use via RCPP_PARALLEL_NUM_THREADS
  environment variable.

* Update to TBB 2018 Update 1.

* Add native registration of compiled functions.

## RcppParallel 4.3.20

* Add support for Rtools 3.3 w/ GCC 4.9

## RcppParallel 4.3.14

* Add support for TBB on Solaris

* Fix failure to compile on OS X Snow Leopard R toolchain

* Add const and non-const operator[] for RMatrix class

## RcppParallel 4.3.8

* Add tbbmalloc library

* Correctly pass clang to TBB configure when R is using clang

## RcppParallel 4.3.6

* Support for TBB on Windows

## RcppParallel 4.3.3

* Update to TBB 4.3 (fixes clang compilation error in platform.h)

* Forward CXX to TBB Makefile

## RcppParallel 4.2.5

* Initial release
