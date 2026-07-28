# Unit tests for tbbRoot() and tbbLibraryPath(), which resolve the TBB library
# that the *installed* package uses.
#
# Regression tests for #270: on Windows these consulted TBB_LIB, the library
# directory recorded when configure ran. For a package built from source that
# happens to be a real path, but for a pre-built binary it names the Rtools
# tree of the build machine -- so tbbRoot() reported a directory that need not
# exist on the user's machine (a 'D:/rtools45/...' path, in the report), and
# tbbLibraryPath() then found nothing and returned NULL.
#
# The invariant these tests pin down is that both functions describe the
# installation actually in use: whatever they return must exist.

RcppParallel:::test_init()

# tbbRoot() must never report a directory that isn't there. system.file()
# returns "" when it cannot resolve a path, so that sentinel is allowed; any
# non-empty answer has to be a real directory.
root <- tbbRoot()
assert(is.character(root))
assert(length(root) == 1L)
if (nzchar(root))
   assert(dir.exists(root))

# on Windows the answer is always the package's own library directory, since
# TBB is statically linked into RcppParallel.dll and the tbb.dll stub is the
# only TBB library installed. in particular it must not depend on TBB_LIB.
if (is_windows()) {

   assert(identical(root, archSystemFile("lib")))

   saved <- Sys.getenv("TBB_LIB", unset = NA)
   Sys.setenv(TBB_LIB = "Z:/nonexistent/rtools/lib")
   assert(identical(tbbRoot(), archSystemFile("lib")))
   if (is.na(saved)) Sys.unsetenv("TBB_LIB") else Sys.setenv(TBB_LIB = saved)

}

# tbbLibraryPath(NULL) reports the directory, and agrees with tbbRoot() when
# TBB_LIB is not set in the environment
if (is.na(Sys.getenv("TBB_LIB", unset = NA)))
   assert(identical(tbbLibraryPath(), root))

# a named library either resolves to a file that exists, or isn't found at all.
# it must never name a file that isn't there -- that was the shape of #270.
for (name in c("tbb", "tbbmalloc", "tbbmalloc_proxy")) {

   path <- tbbLibraryPath(name)
   if (is.null(path))
      next

   assert(is.character(path))
   assert(length(path) == 1L)
   assert(file.exists(path))

}

# the user-visible symptom from #270: tbbLibraryPath("tbb") returned nothing
# from a perfectly good installation. assert this only on Windows, where the
# installed layout is known exactly -- install.libs.R always builds the
# tbb.dll stub when TBB is enabled, and fails the install if it cannot. off
# Windows the library may legitimately be unresolvable, e.g. a system TBB
# whose distro package ships no unversioned 'libtbb.so' development symlink.
if (is_windows() && TBB_ENABLED) {
   tbb <- tbbLibraryPath("tbb")
   assert(!is.null(tbb))
   assert(file.exists(tbb))
}

writeLines("all tbbLibraryPath() tests passed")
