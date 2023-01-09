
## RcppParallel

<!-- badges: start -->
[![R-CMD-check](https://github.com/RcppCore/RcppParallel/workflows/R-CMD-check/badge.svg)](https://github.com/RcppCore/RcppParallel/actions)
[![CRAN](http://www.r-pkg.org/badges/version/RcppParallel)](https://cran.r-project.org/package=RcppParallel)
<!-- badges: end -->

High level functions for parallel programming with Rcpp. The `parallelFor()` function can be used to convert the work of a standard serial "for" loop into a parallel one, and the `parallelReduce()` function can be used for accumulating aggregate or other values.

The high level interface enables safe and robust parallel programming without direct manipulation of operating system threads. On Windows, macOS, and Linux systems, the underlying implementation is based on [Intel TBB](https://github.com/oneapi-src/oneTBB) (Threading Building Blocks). On other platforms, a less-performant fallback implementation based on the [TinyThread](https://tinythreadpp.bitsnbites.eu/) library is used.

For additional documentation on using RcppParallel see the package website at http://rcppcore.github.io/RcppParallel/.


### Intel TBB

`RcppParallel` supports the new interface of Intel TBB, and can be configured to use an external copy of TBB (e.g., with [`oneTBB`](https://github.com/oneapi-src/oneTBB) or the system TBB library), using the `TBB_LIB` and `TBB_INC` environment variables.

To build the development version of `RcppParallel` with [`oneTBB`](https://github.com/oneapi-src/oneTBB):

- Install [`oneTBB`](https://github.com/oneapi-src/oneTBB).

For example, installing [`oneTBB`](https://github.com/oneapi-src/oneTBB) on Linux 64-bit (`x86_64`) to `$HOME` directory (change if needed!):

```bash
TBB_RELEASE="https://api.github.com/repos/oneapi-src/oneTBB/releases/latest"
TBB_TAG=$(curl --silent $TBB_RELEASE | grep -Po '"tag_name": "\K.*?(?=")')
TBB_VERSION=${TBB_TAG#?}

wget https://github.com/oneapi-src/oneTBB/releases/download/v$TBB_VERSION/oneapi-tbb-$TBB_VERSION-lin.tgz
tar zxvf oneapi-tbb-$TBB_VERSION-lin.tgz -C $HOME

export TBB="$HOME/oneapi-tbb-$TBB_VERSION"
```
Note that you may replace `TBB_VERSION=${TBB_TAG#?}` with a custom version number if needed ( check available releases [here](https://github.com/oneapi-src/oneTBB/releases) ).

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
remotes::install_github("RcppCore/RcppParallel")
```


### License

The RcppParallel package is made available under the [GPLv2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html) license.

The [TinyThread library](https://tinythreadpp.bitsnbites.eu/) is licensed under the [zlib/libpng](https://opensource.org/licenses/zlib-license.php) license.

The Intel TBB Library is licensed under the Apache 2.0 license, as described at https://github.com/oneapi-src/oneTBB/blob/master/LICENSE.txt.
