# Unit tests for archSystemFile(), the arch-aware wrapper around system.file()
# introduced when systemFile() was renamed (see #251, #252). It injects the
# architecture-specific subdirectory (.Platform$r_arch) used on Windows, e.g.
# archSystemFile("lib") -> 'lib/x64', while behaving like system.file()
# elsewhere.

RcppParallel:::test_init()

arch <- .Platform$r_arch

# with no arch subdirectory (the usual case off Windows), archSystemFile()
# should be equivalent to a plain system.file() call
if (!nzchar(arch)) {
   assert(identical(
      archSystemFile("include"),
      system.file("include", package = "RcppParallel")
   ))
   assert(identical(
      archSystemFile("include", "RcppParallel.h"),
      system.file("include/RcppParallel.h", package = "RcppParallel")
   ))
}

# the composed relative path must match what system.file() is handed: dir,
# then the arch subdir when set, then the optional name -- joined with '/'
expected <- function(dir, name = NULL) {
   parts <- c(dir, if (nzchar(arch)) arch, name)
   system.file(paste(parts, collapse = "/"), package = "RcppParallel")
}

assert(identical(archSystemFile("lib"), expected("lib")))
assert(identical(archSystemFile("lib", "libtbb.so"), expected("lib", "libtbb.so")))

# a real, shipped resource resolves to an existing path
header <- archSystemFile("include", "RcppParallel.h")
assert(nzchar(header))
assert(file.exists(header))
