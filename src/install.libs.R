
.install.libs <- function() {

   # copy default library
   files <- Sys.glob(paste0("*", SHLIB_EXT))
   dest <- file.path(R_PACKAGE_DIR, paste0("libs", R_ARCH))
   dir.create(dest, recursive = TRUE, showWarnings = FALSE)
   file.copy(files, dest, overwrite = TRUE)
   if (file.exists("symbols.rds"))
      file.copy("symbols.rds", dest, overwrite = TRUE)
   
   # copy tbb
   # TODO: use 'dest' library directory once rstan is updated
   tbbDest <- file.path(R_PACKAGE_DIR, "lib", R_ARCH)
   dir.create(tbbDest, recursive = TRUE, showWarnings = FALSE)
   
   # check for bundled vs. system tbb
   tbbRoot <- Sys.getenv("TBB_ROOT", unset = NA)
   
   tbbLib <- Sys.getenv("TBB_LIB", unset = NA)
   if (is.na(tbbLib) && !is.na(tbbRoot))
      tbbLib <- file.path(tbbRoot, "lib")
   
   # note: on Linux, TBB gets compiled with extensions like
   # '.so.2', so be ready to handle those
   shlibPattern <- switch(
      Sys.info()[["sysname"]],
      Windows = "^tbb.*\\.dll$",
      Darwin  = "^libtbb.*\\.dylib$",
      "^libtbb.*\\.so.*$"
   )
   
   if (is.na(tbbLib)) {
      
      # using bundled TBB
      tbbLibs <- list.files(
         path       = "tbb/build/lib_release",
         pattern    = shlibPattern,
         full.names = TRUE
      )
      
      # don't copy symlinks
      tbbLibs <- tbbLibs[!nzchar(Sys.readlink(tbbLibs))]
      
      # perform the copy
      file.copy(tbbLibs, tbbDest)
      
   } else {
      
      # using system tbb
      tbbLibs <- list.files(
         path       = tbbLib,
         pattern    = shlibPattern,
         full.names = TRUE
      )
      
      # don't copy symlinks
      tbbLibs <- tbbLibs[!nzchar(Sys.readlink(tbbLibs))]
      
      # copy / link the libraries
      useSymlinks <- Sys.getenv("TBB_USE_SYMLINKS", unset = "TRUE")
      if (useSymlinks) 
         file.symlink(tbbLibs, tbbDest)
      else
         file.copy(tbbLibs, tbbDest)
      
   }
   
}

.install.libs()
