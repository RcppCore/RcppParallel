
dllInfo <- NULL


.onLoad <- function(libname, pkgname) {
   
   # load tbb on supported platforms   
   tbb <- tbbLibPath()
   if (!is.null(tbb)) {
      if (!file.exists(tbb)) {
         warning(paste("TBB library", tbb, "not found."))
      } else {
         dllInfo <<- dyn.load(tbb, local = FALSE, now = TRUE)
      }
   }
   
   # load the package library
   library.dynam("RcppParallel", pkgname, libname)
   
   # set default thread options
   setThreadOptions()
}

.onUnload <- function(libpath) {
   
   # unload the package library
   library.dynam.unload("RcppParallel", libpath)
   
   # unload tbb if we loaded it
   if (!is.null(dllInfo))
      dyn.unload(dllInfo[["path"]])
}
