
# NOTE: we intentionally do _not_ load tbbmalloc_proxy as its intended
# use is to replace the default allocator, something that is dangerous
# to do by default (and especially should only be done via e.g. LD_PRELOAD)
.dllInfo          <- NULL
.tbbDllInfo       <- NULL
.tbbMallocDllInfo <- NULL

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
   
   # load tbb, tbbmalloc
   .tbbDllInfo       <<- loadTbbLibrary("tbb")
   .tbbMallocDllInfo <<- loadTbbLibrary("tbbmalloc")
   
   # load RcppParallel library if available
   # (work around https://github.com/r-lib/devtools/issues/2343)
   if (!file.exists(file.path(libname, pkgname, "lib")))
      return()
   
   .dllInfo <<- library.dynam("RcppParallel", pkgname, libname)
   
}

.onUnload <- function(libpath) {
   
   # unload the package library
   if (!is.null(.dllInfo))
      library.dynam.unload("RcppParallel", libpath)
   
   # unload tbb_malloc if we loaded it
   if (!is.null(.tbbMallocDllInfo))
      dyn.unload(.tbbMallocDllInfo[["path"]])
   
   # unload tbb if we loaded it
   if (!is.null(.tbbDllInfo))
      dyn.unload(.tbbDllInfo[["path"]])

}
