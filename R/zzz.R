
# !diagnostics suppress=.dllInfo,.tbbDllInfo,.tbbMallocDllInfo,.tbbMallocProxyDllInfo

# NOTE: we intentionally do _not_ load tbbmalloc_proxy by default, as its
# intended use is to replace the default allocator, something that may be
# dangerous to do by default. in addition, TBB's documentation recommends
# only loading explicitly via e.g. LD_PRELOAD
.dllInfo               <- NULL
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
   
   # load tbb, tbbmalloc
   .tbbDllInfo       <<- loadTbbLibrary("tbb")
   .tbbMallocDllInfo <<- loadTbbLibrary("tbbmalloc")
   
   # load tbbmalloc_proxy, but only if requested
   useTbbMallocProxy <- Sys.getenv("RCPP_PARALLEL_USE_TBBMALLOC_PROXY", unset = "FALSE")
   if (useTbbMallocProxy %in% c("TRUE", "True", "true", "1"))
      .tbbMallocProxyDllInfo <<- loadTbbLibrary("tbbmalloc_proxy")
   
   # load RcppParallel library if available
   .dllInfo <<- library.dynam("RcppParallel", pkgname, libname, local = FALSE)
   
}

.onUnload <- function(libpath) {
   
   # unload the package library
   if (!is.null(.dllInfo))
      library.dynam.unload("RcppParallel", libpath)
   
   # NOTE: we do not explicitly unload tbbmalloc_proxy as switching
   # the allocator at runtime can cause issues
   
   # unload tbbmalloc if we loaded it
   if (!is.null(.tbbMallocDllInfo))
      dyn.unload(.tbbMallocDllInfo[["path"]])
   
   # unload tbb if we loaded it
   if (!is.null(.tbbDllInfo))
      dyn.unload(.tbbDllInfo[["path"]])
   
}
