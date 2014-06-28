

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
   dll <- system.file(paste("lib/libtbb", ext, sep = ""), package = "tbb")
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

initialize <- function(number_of_threads = "auto", thread_stack_size = "auto") {
   
   # validate and resolve number_of_threads
   if (identical(number_of_threads, "auto"))
      number_of_threads <- -1L
   else if (!is.numeric(number_of_threads))
      stop("number_of_threads must be an integer")
   else
      number_of_threads <- as.integer(number_of_threads)
   
   # validate and resolve thread_stack_size
   if (identical(thread_stack_size, "auto"))
      thread_stack_size = 0L
   else if (!is.numeric(thread_stack_size))
      stop("thread_stack_size must be an integer")
   else
      thread_stack_size <- as.integer(thread_stack_size)
   
   invisible(.Call("tbb_initialize", number_of_threads, thread_stack_size, 
                   PACKAGE = "tbb"))
}

is_active <- function() {
   .Call("tbb_is_active", PACKAGE = "tbb")
}

default_num_threads <- function() {
   .Call("tbb_default_num_threads", PACKAGE = "tbb")
}

terminate <- function() {
   invisible(.Call("tbb_terminate", PACKAGE = "tbb"))
}

