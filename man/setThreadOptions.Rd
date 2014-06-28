\name{setThreadOptions}
\alias{setThreadOptions}
\alias{defaultNumThreads}
\title{
Thread options for TBB
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
setThreadOptions(numThreads = "auto", 
                 stackSize = "auto")
defaultNumThreads()
}
\arguments{
  \item{numThreads}{
   
}
  \item{stackSize}{

}
}
\details{
   The TBB library is automatically initialized with the default number
   of threads and thread stack size when it loads. You can call 
   \code{setThreadOptions} at any time to change the defaults.
}

\value{
   The \code{defaultNumThreads} returns the default number of threads
   that are used by TBB if another value isn't specified using
   \code{setThreadOptions}.
}

\examples{
\dontrun{
setThreadOptions(numThreads = 4)

defaultNumThreads()
}
}

