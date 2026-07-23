
# like system.file(), but injects the architecture-specific subdirectory
# used on Windows when set; e.g. archSystemFile("lib") resolves 'lib/x64'
archSystemFile <- function(dir, name = NULL) {
   arch <- .Platform$r_arch
   parts <- c(dir, if (nzchar(arch)) arch, name)
   system.file(paste(parts, collapse = "/"), package = "RcppParallel")
}

# generate paths consumable by the compilers and linkers
# in particular, on Windows and Solaris, this means the path _cannot_ be quoted !!
asBuildPath <- function(path) {

   # normalize paths using forward slashes
   path <- normalizePath(path, winslash = "/", mustWork = FALSE)

   # prefer short path names if the path has spaces
   if (is_windows() && grepl(" ", path, fixed = TRUE))
      path <- utils::shortPathName(path)

   # if we still have spaces, and we're not Windows or Solaris, try quoting
   if (grepl(" ", path, fixed = TRUE) && !is_solaris())
      path <- shQuote(path)

   # ensure we use forward slashes, even on Windows
   path <- chartr("\\", "/", path)

   # return path
   path

}

