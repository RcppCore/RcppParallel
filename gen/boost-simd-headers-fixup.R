# Tar warns about portability problems with paths >= 100 characters,
# which unfortunately we bump into with Boost.SIMD. Fix this up by
# renaming some offending files.
transformations <- list(
   "is_not_equal_with_equal_nans.hpp" = "is_ne_nans.hpp",
   "is_equal_with_equal_nans.hpp" = "is_eq_nans.hpp"
)

files <- c(
   list.files("inst/include/nt2", recursive = TRUE, full.names = TRUE),
   list.files("inst/include/boost", recursive = TRUE, full.names = TRUE)
)

# First pass to rename contents of files
for (file in files) {
   contents <- readLines(file)
   changed <- contents
   for (i in seq_along(transformations)) {
      from <- names(transformations)[[i]]
      to <- transformations[[i]]
      changed <- tryCatch(
         gsub(from, to, changed, fixed = TRUE),
         error = function(e) from
      )
   }
   
   if (all(contents == changed))
      next
   
   writeLines(changed, file)
}

# Second pass to rename files
for (file in files) {
   new <- file
   for (i in seq_along(transformations)) {
      from <- names(transformations)[[i]]
      to <- transformations[[i]]
      new <- gsub(from, to, new, fixed = TRUE)
   }
   
   if (new == file)
      next
   
   file.rename(file, new)
}
