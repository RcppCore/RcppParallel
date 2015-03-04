\name{setThreadOptions}
\alias{setThreadOptions}
\alias{defaultNumThreads}
\title{
Thread options for RcppParallel
}
\description{
Set thread options (number of threads to use for task scheduling and stack
size per-thread) for RcppParallel.
}
\usage{
setThreadOptions(numThreads = "auto", 
                 stackSize = "auto")
defaultNumThreads()
}
\arguments{
  \item{numThreads}{
      Number of threads to use for task scheduling (call 
      \code{defaultNumThreads} to determine the the default
      value used for "auto").
   }
  \item{stackSize}{
      Stack size (in bytes) to use for worker threads. The 
      default used for "auto" is 2MB on 32-bit systems and
      4MB on 64-bit systems (note that this parameter has
      no effect on Windows).
   }
}
\details{
   RcppParallel is automatically initialized with the default number
   of threads and thread stack size when it loads. You can call 
   \code{setThreadOptions} at any time to change the defaults.
}

\value{
   The \code{defaultNumThreads} returns the default number of threads
   that are used by RcppParallel if another value isn't specified using
   \code{setThreadOptions}.
}

\examples{
library(RcppParallel)

setThreadOptions(numThreads = 4)

defaultNumThreads()
}

