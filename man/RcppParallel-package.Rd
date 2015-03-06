\docType{package}
\name{RcppParallel-package}
\alias{RcppParallel}
\alias{RcppParallel-package}
\title{Parallel programming tools for Rcpp}
\description{
  High level functions for doing parallel programming with Rcpp.
  For example, the \code{parallelFor} function can be used to convert the work of 
  a standard serial "for" loop into a parallel one and the \code{parallelReduce} 
  function can be used for accumulating aggregate or other values.

  The high level interface enables safe and robust parallel programming without
  direct manipulation of operating system threads. On Windows, OS X, and Linux
  systems the underlying implementation is based on \href{https://www.threadingbuildingblocks.org/}{Intel TBB} (Threading Building
  Blocks). On other platforms a less-performant fallback implementation based on the
  \href{http://tinythreadpp.bitsnbites.eu/}{TinyThread} library is used.
  
  For additional documentation see the package website at: \href{http://rcppcore.github.io/RcppParallel}{http://rcppcore.github.io/RcppParallel}.
}

\author{
  JJ Allaire, Romain Francois, Gregory Vandenbrouck, Marcus Geelnard, Intel Inc.
}


\keyword{package}
\keyword{parallel}

