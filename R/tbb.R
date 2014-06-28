

dllInfo <- NULL

.onLoad <- function(libname, pkgname) {
   
   # load tbb and make it's symbols available globally
   sysname <- Sys.info()['sysname']
   if (sysname == "Darwin")
      ext = ".dylib"
   else if (sysname == "Linux")
      ext = ".so.2"
   else if (sysname == "Windows")
      ext = ".dll"
   else
      ext = .Platform$dynlib.ext
   dll <- system.file(paste("libs/libtbb", ext, sep = ""), package = "tbb")
   dllInfo <<- dyn.load(dll, local = FALSE, now = TRUE)
   
   # load the tbb package library
   library.dynam("tbb", pkgname, libname)
}

.onUnload <- function(libpath) {
   
   # unload the tbb package library
   library.dynam.unload("tbb", libpath)
   
   # unload tbb
   dyn.unload(dllInfo[["path"]])
}

initialize <- function(number_of_threads = -1, thread_stack_size = 0) {

}

is_active <- function() {
   .Call("tbb_is_active", PACKAGE = "tbb")
}

default_num_threads <- function() {
   .Call("tbb_default_num_threads", PACKAGE = "tbb")
}

terminate <- function() {
   
}

