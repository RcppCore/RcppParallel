\name{RcppParallelLibs}
\alias{RcppParallelLibs}
\alias{RcppParallelLibs}
\title{
Linker flags for RcppParallel
}
\description{
Output the linker flags required to link to RcppParallel. On
Windows this includes the underlying TBB library, on other 
platforms no linker flags are required.
}
\usage{
RcppParallelLibs()
}
\details{
This function is typically called from \code{Makevars.win} as follows:

\code{PKG_LIBS += $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "RcppParallel::RcppParallelLibs()")}

}

\value{
  Returns \code{NULL} invisibly. The function is not called for it's
  return value rather for the side effect of outputting the linker
  flags.
}

