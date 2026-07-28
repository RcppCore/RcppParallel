# Unit tests for tbbLdFlags(), the linker flags handed to downstream packages
# via RcppParallel::LdFlags().
#
# On macOS, the TBB libraries RcppParallel ships record an '@rpath'-relative
# install name (e.g. '@rpath/libtbb.dylib'), so a '-L' search path alone only
# satisfies the linker: the resulting binary carries no runtime search path for
# TBB, and dyld can resolve it only when RcppParallel has already pulled TBB
# into the process. Every '-L' we emit must therefore be paired with a matching
# '-rpath'. (#209)
#
# This is only a check on the shape of the flags, so that something still runs
# where no toolchain is available (e.g. CRAN). tests/test-downstream-load.R
# covers the behaviour itself: it builds a package against these flags and
# loads it in a process that never loads RcppParallel.

RcppParallel:::test_init()

flags <- tbbLdFlags()

assert(is.character(flags))
assert(length(flags) == 1L)
assert(!is.na(flags))

if (is_mac()) {

   parts <- strsplit(flags, "\\s+")[[1L]]

   libPaths <- sub("^-L", "", grep("^-L", parts, value = TRUE))
   rpaths <- sub("^-Wl,-rpath,", "", grep("^-Wl,-rpath,", parts, value = TRUE))

   # we always link TBB explicitly on macOS, so there is a search path to check
   assert(length(libPaths) > 0L)
   assert(all(nzchar(libPaths)))

   # and each one must also be searched at load time
   assert(all(libPaths %in% rpaths))

}
