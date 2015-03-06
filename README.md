## RcppParallel Package

High level functions for doing parallel programming with Rcpp. For example, the `parallelFor` function can be used to convert the work of a standard serial "for" loop into a parallel one and the `parallelReduce` function can be used for accumulating aggregate or other values.

The high level interface enables safe and robust parallel programming without direct manipulation of operating system threads. On Windows, OS X, and Linux systems the underlying implementation is based on [Intel TBB](https://www.threadingbuildingblocks.org/) (Threading Building Blocks). On other platforms a less-performant fallback implementation based on the [TinyThread](http://tinythreadpp.bitsnbites.eu/) library is used.

For additional documentation on using RcppParallel see the package website at http://rcppcore.github.io/RcppParallel/.

### License

The RcppParallel package is made available under the [GPLv2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html).

The TinyThread library is licensed under the [zlib/libpng](http://www.opensource.org/licenses/zlib-license.php) license as described [here](https://gitorious.org/tinythread/tinythreadpp/source/master:README.txt).

The Intel TBB Library is licensed under the GPLv2 (as described at https://www.threadingbuildingblocks.org/Licensing):

TBB and other open-source software available from this site is licensed under GPLv2 with the (libstdc++) runtime exception. Specifically, the TBB open-source license is the same license used by the GNU libstdc++ library in gcc 4.2.1 (and earlier). For a complete description of the license, please visit the official GNU website for [GPLv2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html) and for the [runtime exception](https://www.threadingbuildingblocks.org/licensing#runtime-exception). 

**Runtime Exception**

```
As a special exception, you may use this file as part of a free software
library without restriction.  Specifically, if other files instantiate
templates or use macros or inline functions from this file, or you compile
this file and link it with other files to produce an executable, this
file does not by itself cause the resulting executable to be covered by
the GNU General Public License.  This exception does not however
invalidate any other reasons why the executable file might be covered by
the GNU General Public License.
```

