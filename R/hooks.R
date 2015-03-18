
dllInfo <- NULL
mallocDllInfo <- NULL

.onLoad <- function(libname, pkgname) {
   
   # load tbb and tbbmalloc on supported platforms   
   tbb <- tbbLibPath()
   if (!is.null(tbb)) {
      if (!file.exists(tbb)) {
         warning(paste("TBB library", tbb, "not found."))
      } else {
         dllInfo <<- dyn.load(tbb, local = FALSE, now = TRUE)
      }
   }
   tbbMalloc <- tbbLibPath("malloc")
   if (!is.null(tbbMalloc)) {
      if (!file.exists(tbbMalloc)) {
         warning(paste("TBB malloc library", tbbMalloc, "not found."))
      } else {
         mallocDllInfo <<- dyn.load(tbbMalloc, local = FALSE, now = TRUE)
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
   # unload tbbmalloc if we loaded it
   if (!is.null(mallocDllInfo))
      dyn.unload(mallocDllInfo[["path"]])
}
