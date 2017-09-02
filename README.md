## RcppParallel Package

[![Travis-CI Build Status](https://travis-ci.org/RcppCore/RcppParallel.svg?branch=master)](https://travis-ci.org/RcppCore/RcppParallel)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/RcppCore/RcppParallel?branch=master&svg=true)](https://ci.appveyor.com/project/RcppCore/RcppParallel)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/RcppParallel)](https://cran.r-project.org/package=RcppParallel)

High level functions for doing parallel programming with Rcpp. For example, the `parallelFor` function can be used to convert the work of a standard serial "for" loop into a parallel one and the `parallelReduce` function can be used for accumulating aggregate or other values.

The high level interface enables safe and robust parallel programming without direct manipulation of operating system threads. On Windows, OS X, and Linux systems the underlying implementation is based on [Intel TBB](https://www.threadingbuildingblocks.org/) (Threading Building Blocks). On other platforms a less-performant fallback implementation based on the [TinyThread](http://tinythreadpp.bitsnbites.eu/) library is used.

For additional documentation on using RcppParallel see the package website at http://rcppcore.github.io/RcppParallel/.

### License

The RcppParallel package is made available under the [GPLv2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html).

The TinyThread library is licensed under the [zlib/libpng](http://www.opensource.org/licenses/zlib-license.php) license as described [here](https://gitorious.org/tinythread/tinythreadpp/source/master:README.txt).

The Intel TBB Library is licensed under the Apache 2.0 (as described at https://www.threadingbuildingblocks.org/faq/10).
