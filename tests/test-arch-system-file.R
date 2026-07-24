# Unit tests for archSystemFile(), the arch-aware wrapper around system.file()
# introduced when systemFile() was renamed (see #251, #252). It injects the
# architecture-specific subdirectory (.Platform$r_arch) used on Windows, e.g.
# archSystemFile("lib") -> 'lib/x64', while behaving like system.file()
# elsewhere. Note that this subdirectory only ever holds compiled libraries
# ('lib', 'libs'); headers and other resources are never installed under it.

RcppParallel:::test_init()

arch <- .Platform$r_arch

# compare two file paths for equality. system.file() returns "" when a path is
# not found, so preserve that sentinel; otherwise normalize both sides, since
# strings that differ only in separators, case, or symlinks can still denote
# the same file (and normalizePath("") would resolve to the working directory).
samePath <- function(a, b) {
   norm <- function(p) {
      if (nzchar(p)) normalizePath(p, winslash = "/", mustWork = FALSE) else p
   }
   identical(norm(a), norm(b))
}

# with no arch subdirectory (the usual case off Windows), archSystemFile()
# should be equivalent to a plain system.file() call
if (!nzchar(arch)) {
   assert(samePath(
      archSystemFile("libs"),
      system.file("libs", package = "RcppParallel")
   ))
}

# the composed relative path must match what system.file() is handed: dir,
# then the arch subdir when set, then the optional name -- joined with '/'
expected <- function(dir, name = NULL) {
   parts <- c(dir, if (nzchar(arch)) arch, name)
   system.file(paste(parts, collapse = "/"), package = "RcppParallel")
}

assert(samePath(archSystemFile("lib"), expected("lib")))
assert(samePath(archSystemFile("lib", "libtbb.so"), expected("lib", "libtbb.so")))

# the package's own compiled code is installed under 'libs' (or 'libs/<arch>'
# on Windows) -- exactly the arch-aware lookup archSystemFile() exists for --
# so it must resolve to an existing directory on every platform
libs <- archSystemFile("libs")
assert(nzchar(libs))
assert(dir.exists(libs))
