
.tbbDllInfo            <- NULL
.tbbMallocDllInfo      <- NULL
.tbbMallocProxyDllInfo <- NULL

loadTbbLibrary <- function(name) {
   
   path <- tbbLibraryPath(name)
   if (is.null(path))
      return(NULL)
   
   if (!file.exists(path)) {
      warning("TBB library ", shQuote(name), " not found.")
      return(NULL)
   }
   
   dyn.load(path, local = FALSE, now = TRUE)
   
}

.onLoad <- function(libname, pkgname) {
   
   # load tbb, tbbmalloc, tbbmalloc_proxy
   .tbbDllInfo            <<- loadTbbLibrary("tbb")
   .tbbMallocDllInfo      <<- loadTbbLibrary("tbbmalloc")
   .tbbMallocProxyDllInfo <<- loadTbbLibrary("tbbmalloc_proxy")
   
   library.dynam("RcppParallel", pkgname, libname)
   
}

.onUnload <- function(libpath) {
   
   # unload the package library
   library.dynam.unload("RcppParallel", libpath)
   
   # unload tbb if we loaded it
   dlls <- list(.tbbDllInfo, .tbbMallocDllInfo, .tbbMallocProxyDllInfo)
   for (dll in dlls)
      if (!is.null(dll))
         dyn.unload(dll[["path"]])

}
