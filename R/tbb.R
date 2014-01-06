# 
# Tbb.system.file <- function(...){
#    tools::file_path_as_absolute( base::system.file( ..., package = "tbb" ) )
# }
# 
# TbbLdFlags <- function() {
#    libdir <- Tbb.system.file("lib")
#    flags <- paste("-L", libdir, " -ltbb", sep="")
#    invisible(flags)
# }
# 
# inlineCxxPlugin <- function() {
#    list(env = list(PKG_LIBS=TbbLdFlags()))
# }
# 
# .onLoad <- function(libname, pkgname) {
#    dyn.load(paste0(Tbb.system.file("lib/libtbb.dylib")))
# }
# 
# 
