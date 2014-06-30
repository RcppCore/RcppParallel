## Intel TBB Package for R/Rcpp

The [Intel TBB](https://www.threadingbuildingblocks.org/) (Threading Building Blocks) is a widely used, award-winning C++ template library for creating reliable, portable, and scalable parallel applications. Intel TBB includes synchronization primitives, parallel algorithms and tasking, and concurrent containers, including:

**Generic Parallel Algorithms**

* parallel_for
* parallel_while
* parallel_reduce
* pipeline
* parallel_sort
* parallel_scan

**Concurrent Containers**

* concurrent_hash_map
* concurrent_queue
* concurrent_vector

The TBB package makes it easy to use Intel TBB with R and Rcpp.

### Examples

Here are links to two examples that illustrate using TBB with R and Rcpp:

[Parallel Matrix Transform](inst/examples/parallel-matrix-transform.cpp) --- Demonstrates using `tbb::parallel_for` to transform a matrix (take the square root of each element) in parallel. In this simple example the parallel version performs about 2.5x faster than the serial version on a 4-core machine.

[Parallel Vector Sum](inst/examples/parallel-vector-sum.cpp) --- Demonstrates using `tbb::parallel_reduce` to take the sum of a vector in parallel. In this example the parallel version performs 4x faster than the serial version on a 4-core machine.

### Usage

You can install the TBB package from GitHub as follows (note that the package is currently only available for Linux and Mac OS X systems):

```s
devtools::install_package("jjallaire/TBB")
```

#### sourceCpp

You can use the TBB library from within a standalone C++ source file as follows:

```cpp
// [[Rcpp::depends(TBB)]]
#include <tbb/tbb.h>
```

#### Packages

If you want to use TBB from within an R package you add the following to your DESCRIPTION file:

```yaml
Imports: TBB
LinkingTo: TBB
```

And the following to your NAMESPACE file:

```s
import(TBB)
```

### Learning More

The examples described above are a good place to start getting the feel for how TBB can be used with Rcpp. Here are some additional resources for learning more in depth:

http://en.wikipedia.org/wiki/Threading_Building_Blocks --- Wikipedia article on TBB

https://www.threadingbuildingblocks.org --- Website for TBB open-source distribution

https://software.intel.com/en-us/node/506045 --- Intel TBB User Guide

http://homepages.math.uic.edu/~jan/mcs572/intro2tbb.pdf --- Introduction to TBB tutorial

http://blog.ruslans.com/2013/08/introduction-to-high-level.html --- Introduction to TBB with game of life example

### License

The TBB package is made available under the [GPLv2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html).

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





