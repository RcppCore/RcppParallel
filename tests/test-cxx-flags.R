# Unit tests for the compiler and platform-specific flags returned by
# RcppParallel::CxxFlags().

RcppParallel:::test_init()

# Darwin 16 is macOS 10.12, the last release affected by this libc++ issue.
assert(tbb_needs_no_aligned_allocation("Darwin", "16.7.0", "clang++"))
assert(!tbb_needs_no_aligned_allocation("Darwin", "17.0.0", "clang++"))
assert(!tbb_needs_no_aligned_allocation("Darwin", "16.7.0", "g++"))
assert(!tbb_needs_no_aligned_allocation("Linux", "16.7.0", "clang++"))

flags <- tbbCxxFlags()
assert(is.character(flags))
assert(length(flags) == 1L)
assert(!is.na(flags))

if (nzchar(TBB_CXXFLAGS))
   assert(grepl("-fno-aligned-allocation", flags, fixed = TRUE))
