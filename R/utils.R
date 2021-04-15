
# generate paths consumable by the compilers and linkers
# in particular, on Windows, this means the path _cannot_ be quoted !!
asBuildPath <- function(path) {
   
   if (!is_windows())
      return(shQuote(path))
   
   # normalize paths using forward slashes
   path <- normalizePath(path, winslash = "/", mustWork = FALSE)
   
   # prefer short path names if the path has spaces
   if (grepl(" ", path, fixed = TRUE))
      path <- utils::shortPathName(path)
   
   # return path
   return(path)
   
}
