## RcppParallel 6.0.0

This is a major release, which updates the bundled version of oneTBB to
2022.0.0. Because the TBB ABI has changed, packages compiled against an
older version of RcppParallel may need to be rebuilt. RcppParallel provides
compatibility headers and symbols to help ease this transition.

On Windows, RcppParallel now uses the copy of TBB provided by Rtools
(R >= 4.2.0), rather than bundling its own copy.

## R CMD check results

0 errors | 0 warnings | 0 notes

## revdepcheck results

We checked 301 reverse dependencies (273 from CRAN + 28 from Bioconductor),
comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 0 new problems
 * We failed to check 16 packages

Most of the packages we failed to check did so for reasons unrelated to this
release (they could not be installed in the check environment, e.g. missing
Bioconductor dependencies).

However, the following packages failed specifically because of the updated
TBB ABI. They link, directly or transitively, against 'Rfast' or
'stringfish', which were themselves compiled against the previous version of
TBB and so reference symbols (such as 'tbb::task') that oneTBB 2022.0 no
longer provides:

 * via 'Rfast':       CompositionalRF, DER, kernreg, Rfast2
 * via 'stringfish':  qs2, rxode2

These will resolve once 'Rfast' and 'stringfish' are reinstalled / rebuilt
against RcppParallel 6.0.0, which we expect to happen when CRAN rebuilds the
reverse dependency chain. No source changes are required in those packages.

(One further package, 'multinma', failed to check due to the compiler being
killed for exceeding memory during compilation, which is unrelated to this
release.)
