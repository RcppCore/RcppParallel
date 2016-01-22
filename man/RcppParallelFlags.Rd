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

\code{PKG_LIBS += $(shell "${R_HOME}/bin/Rscript/" -e "RcppParallel::LdFlags()")}

}

\value{
  Returns \code{NULL} invisibly. The function is not called for it's
  return value rather for the side effect of outputting the flags.
}

