\name{parallelVectorSum}
\alias{parallelVectorSum}
\title{Parallel Vector Sum}
\description{
Parallel Vector Sum
}
\usage{
parallelVectorSum(x)
}
\arguments{
  \item{x}{Vector}
}

\value{
Sum of Vector
}

\examples{
library(RcppParallelTest)
parallelVectorSum(c(1:100))
}


