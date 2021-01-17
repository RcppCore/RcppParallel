## RcppParallel Package

[![Travis-CI Build Status](https://travis-ci.org/RcppCore/RcppParallel.svg?branch=master)](https://travis-ci.org/RcppCore/RcppParallel)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/RcppCore/RcppParallel?branch=master&svg=true)](https://ci.appveyor.com/project/RcppCore/RcppParallel)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/RcppParallel)](https://cran.r-project.org/package=RcppParallel)

High level functions for doing parallel programming with Rcpp. For example, the `parallelFor` function can be used to convert the work of a standard serial "for" loop into a parallel one and the `parallelReduce` function can be used for accumulating aggregate or other values.

The high level interface enables safe and robust parallel programming without direct manipulation of operating system threads. On Windows, OS X, and Linux systems the underlying implementation is based on [Intel TBB](https://www.threadingbuildingblocks.org/) (Threading Building Blocks). On other platforms a less-performant fallback implementation based on the [TinyThread](http://tinythreadpp.bitsnbites.eu/) library is used.

For additional documentation on using RcppParallel see the package website at http://rcppcore.github.io/RcppParallel/.

### Intel TBB

`RcppParallel` now supports the new interface of Intel TBB and allows using external library (e.g., with [`oneTBB`](https://github.com/oneapi-src/oneTBB) or the system TBB library), using `TBB_LIB` and `TBB_INC` environment variables.

To build the development version of `RcppParallel` with [`oneTBB`](https://github.com/oneapi-src/oneTBB):

- Install [`oneTBB`](https://github.com/oneapi-src/oneTBB).

For example, installing [`oneTBB`](https://github.com/oneapi-src/oneTBB) on Linux 64-bit (`x86_64`) to `$HOME` directory (change if needed!):
```bash
TBB_VERSION="2021.1.1"

wget https://github.com/oneapi-src/oneTBB/releases/download/v2021.1.1/oneapi-tbb-$TBB_VERSION-lin.tgz
tar zxvf oneapi-tbb-$TBB_VERSION-lin.tgz -C $HOME

export TBB="$HOME/oneapi-tbb-$TBB_VERSION"
```

- Set the TBB environment variables (specifically: `TBB` for the installation prefix, `TBB_INC` for the directory that includes the header files, and `TBB_LIB` for the libraries directory).

For example, installing [`oneTBB`](https://github.com/oneapi-src/oneTBB) on Linux 64-bit (`x86_64`) to `$HOME` directory (change if needed!):
```bash
source $TBB/env/vars.sh intel64

export TBB_INC="$TBB/include"
export TBB_LIB="$TBB/lib/intel64/gcc4.8"
```

- Build the development version of `RcppParallel`:
```r
install.packages("remotes")
remotes::install_github("RcppCore/RcppParallel@develop", force = TRUE)
```

### License

The RcppParallel package is made available under the [GPLv2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html).

The TinyThread library is licensed under the [zlib/libpng](http://www.opensource.org/licenses/zlib-license.php) license as described [here](https://gitorious.org/tinythread/tinythreadpp/source/master:README.txt).

The Intel TBB Library is licensed under the Apache 2.0 (as described at https://www.threadingbuildingblocks.org/faq/10).
