# Unit tests for the compiler flags handed to downstream packages through
# RcppParallel::CxxFlags().

RcppParallel:::test_init()

flags <- tbbCxxFlags()

assert(is.character(flags))
assert(length(flags) == 1L)
assert(!is.na(flags))
assert(grepl("-DRCPP_PARALLEL_USE_TBB=1", flags, fixed = TRUE))

hasNoAlignedAllocation <- grepl(
   "-fno-aligned-allocation",
   flags,
   fixed = TRUE
)
assert(identical(hasNoAlignedAllocation, nzchar(TBB_CXXFLAGS)))
