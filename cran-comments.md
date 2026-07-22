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

The packages we failed to check did so because they link, directly or
transitively, against other packages (e.g. 'Rfast', 'stringfish') that were
themselves compiled against the previous TBB ABI. These fail to load with
errors such as "undefined symbol: _ZTIN3tbb4taskE" until those upstream
packages are rebuilt against oneTBB 2022.0. We expect these to resolve once
CRAN rebuilds the reverse dependency chain against RcppParallel 6.0.0.
