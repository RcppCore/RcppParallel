
#' Create a skeleton for a new package depending on RcppParallel
#' 
#' \code{RcppParallel.package.skeleton} automates the creation of a new source
#' package that intends to use features of RcppParallel.
#' 
#' It is based on the \link[utils]{package.skeleton} function which it executes
#' first.
#' 
#' In addition to \link[Rcpp]{Rcpp.package.skeleton} :
#' 
#' The \samp{DESCRIPTION} file gains an Imports line requesting that the
#' package depends on RcppParallel and a LinkingTo line so that the package
#' finds RcppParallel header files.
#' 
#' The \samp{NAMESPACE} gains a \code{useDynLib} directive as well as an
#' \code{importFrom(RcppParallel, evalCpp} to ensure instantiation of
#' RcppParallel.
#' 
#' The \samp{src} directory is created if it does not exists and a
#' \samp{Makevars} file is added setting the environment variables
#' \samp{PKG_LIBS} to accomodate the necessary flags to link with the
#' RcppParallel library.
#' 
#' If the \code{example_code} argument is set to \code{TRUE}, example files
#' \samp{vector-sum.cpp} is created in the \samp{src} directory.
#' \code{Rcpp::compileAttributes()} is then called to generate
#' \code{src/RcppExports.cpp} and \code{R/RcppExports.R}. These files are given
#' as an example and should eventually by removed from the generated package.
#' 
#' @param name The name of your R package.
#' @param example_code If \code{TRUE}, example C++ code using RcppParallel is
#' added to the package.
#' @param ... Optional arguments passed to \link[Rcpp]{Rcpp.package.skeleton}.
#' @return Nothing, used for its side effects
#' @seealso \link[utils]{package.skeleton}
#' @references Read the \emph{Writing R Extensions} manual for more details.
#' 
#' Once you have created a \emph{source} package you need to install it: see
#' the \emph{R Installation and Administration} manual, \code{\link{INSTALL}}
#' and \code{\link{install.packages}}.
#' @keywords programming
#' @examples
#' 
#' \dontrun{
#' # simple package
#' RcppParallel.package.skeleton("foobar")
#' }
#' 
#' @export RcppParallel.package.skeleton
RcppParallel.package.skeleton <- function(name = "anRpackage",
                                          example_code = TRUE,
                                          ...)
{
   # call Rcpp.package.skeleton() -- provide 'list' explicitly
   # and clean up after
   env <- new.env(parent = emptyenv())
   env$dummy <- NULL
   Rcpp::Rcpp.package.skeleton(
      name = name,
      attributes = FALSE,
      module = FALSE,
      example_code = FALSE,
      environment = env,
      list = "dummy",
      ...
   )
   
   # move to generated package directory
   owd <- setwd(name)
   on.exit(setwd(owd), add = TRUE)
   
   # remove dummy stuff
   unlink("data", recursive=TRUE)
   unlink("man/dummy.Rd")
   unlink("Read-and-delete-me")
   lns <- readLines("NAMESPACE")
   writeLines(lns[!grepl("dummy", lns)], "NAMESPACE")
   unlink("src/init.c")
   
   message("\nAdding RcppParallel settings")
   
   # update DESCRIPTION file
   desc <- read.dcf("DESCRIPTION", all = TRUE, keep.white = TRUE)
   version <- sprintf("RcppParallel (>= %s)", utils::packageVersion("RcppParallel"))
   
   desc$Imports <- paste0(desc$Imports, ", ", version)
   message(" >> added Imports: ", desc$Imports)
   
   desc$LinkingTo <- paste0(desc$LinkingTo, ", RcppParallel")
   message(" >> added LinkingTo: ", desc$LinkingTo)
   
   desc$SystemRequirements <- "GNU make"
   message(" >> added SystemRequirements: GNU make")
   
   write.dcf(desc, file = "DESCRIPTION", keep.white = TRUE)
   
   # update NAMESPACE file
   message(" >> added importFrom(RcppParallel,RcppParallelLibs) directive to NAMESPACE")
   cat("importFrom(RcppParallel,RcppParallelLibs)",
      file = "NAMESPACE",
      sep = "\n",
      append = TRUE)
   
   # write Makevars files
   dir.create("src", showWarnings = FALSE)
   
   # src/Makevars
   message(" >> added src/Makevars")
   cat(
      c(
         '# We also need importFrom(RcppParallel,RcppParallelLibs) in NAMESPACE',
         'PKG_LIBS += $(shell ${R_HOME}/bin/Rscript -e "RcppParallel::RcppParallelLibs()")'
      ),
      file = "src/Makevars",
      sep = "\n"
   )
   
   # src/Makevars.win
   message(" >> added src/Makevars.win")
   cat(
      c(
         'PKG_CXXFLAGS += -DRCPP_PARALLEL_USE_TBB=1',
         'PKG_LIBS += $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "RcppParallel::RcppParallelLibs()")'
      ),
      file = "src/Makevars.win",
      sep = "\n"
   )
   
   # write an example script using RcppParallel
   if (example_code) {
      
      message(" >> added example file src/vector-sum.cpp")
      file.copy(
         system.file("skeleton/vector-sum.cpp", package = "RcppParallel"),
         "src/vector-sum.cpp"
      )
      
      message(" >> added example documentation man/vector-sum.Rd")
      file.copy(
         system.file("skeleton/vector-sum.Rd", package = "RcppParallel"),
         "man/vector-sum.Rd"
      )
      
      message(" >> compiled Rcpp attributes")
      Rcpp::compileAttributes()
   }
   
   TRUE
}
