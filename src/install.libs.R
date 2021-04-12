
.install.libs <- function() {

   # copy default library
   files <- Sys.glob(paste0("*", SHLIB_EXT))
   dest <- file.path(R_PACKAGE_DIR, paste0("libs", R_ARCH))
   dir.create(dest, recursive = TRUE, showWarnings = FALSE)
   file.copy(files, dest, overwrite = TRUE)
   if (file.exists("symbols.rds"))
      file.copy("symbols.rds", dest, overwrite = TRUE)
   
   # copy tbb
   tbbDest <- file.path(dest, "tbb")
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
      Windows = "[.]dll$",
      Darwin  = "[.]dylib$",
      "[.]so(?:[.][[:digit:]]+)?$"
   )
   
   if (is.na(tbbLib)) {
      
      # using bundled TBB
      tbbLibs <- list.files(
         path       = "tbb/build/lib_release",
         pattern    = shlibPattern,
         full.names = TRUE
      )
      
      # only copy real files; don't copy symlinks
      links <- Sys.readlink(tbbLibs)
      file.copy(tbbLibs[!nzchar(links)], tbbDest)
      
   } else {
      
      # using system tbb
      tbbLibs <- list.files(
         path       = tbbLib,
         pattern    = shlibPattern,
         full.names = TRUE
      )
      
      # symlink tbb libraries
      file.symlink(tbbLibs, tbbDest)
      
   }
   
}

.install.libs()
