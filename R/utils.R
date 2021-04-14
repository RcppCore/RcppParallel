
# Helper function to ape the behavior of the R build system
# when providing paths to libraries
asBuildPath <- function(path) {
   
   # nothing to do for non-Windows
   if (!is_windows())
      return(path)
   
   # normalize paths using forward slashes
   path <- normalizePath(path, winslash = "/", mustWork = FALSE)
   
   # prefer short path names if the path has spaces
   if (grepl(" ", path, fixed = TRUE))
      path <- utils::shortPathName(path)
   
   # return path
   return(path)
   
}
