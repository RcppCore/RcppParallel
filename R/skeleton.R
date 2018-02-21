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
   unlink("data/dummy.Rda")
   unlink("man/dummy.Rd")
   unlink("Read-and-delete-me")
   
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
         'CXX_STD = CXX11',
         'PKG_LIBS += $(shell ${R_HOME}/bin/Rscript -e "RcppParallel::RcppParallelLibs()")'
      ),
      file = "src/Makevars",
      sep = "\n"
   )
   
   # src/Makevars.win
   message(" >> added src/Makevars.win")
   cat(
      c(
         'CXX_STD = CXX11',
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
