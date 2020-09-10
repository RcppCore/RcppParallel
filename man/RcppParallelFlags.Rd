\name{RcppParallelFlags}
\alias{RcppParallelLibs}
\alias{LdFlags}
\alias{CxxFlags}
\title{
Compilation flags for RcppParallel
}
\description{
Output the compiler or linker flags required to build against RcppParallel.
}
\usage{
CxxFlags()
LdFlags()
RcppParallelLibs()
}

\details{
These functions are typically called from \code{Makevars} as follows:

\code{PKG_LIBS += $(shell "${R_HOME}/bin/Rscript" -e "RcppParallel::LdFlags()")}

On Windows, the flags ensure that the package links with the built-in TBB library.
On Linux and macOS, the output is empty, because TBB is loaded dynamically.
To ensure portability, load \pkg{RcppParallel} before loading your package, e.g. by including \code{importFrom(RcppParallel, RcppParallelLibs)} in your \code{NAMESPACE} file.
See \url{https://github.com/RcppCore/RcppParallel/issues/129} for details.
}

\value{
  Returns \code{NULL} invisibly. The function is not called for it's
  return value rather for the side effect of outputting the flags.
}

