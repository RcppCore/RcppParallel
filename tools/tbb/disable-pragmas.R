# Disable TBB pragmas that silence diagnostic warnings.
# This is necessary for CRAN submissions of RcppParallel.

files <- list.files(
   path = "src/tbb",
   pattern = "[.](?:h|cpp)$",
   all.files = TRUE,
   full.names = TRUE,
   recursive = TRUE
)

for (file in files) {
   
   before <- readLines(file)
   
   after <- before
   after <- gsub("^(\\s*)#pragma warning", "\\1// #pragma warning", after, perl = TRUE)
   after <- gsub("^(\\s*)#pragma GCC", "\\1// #pragma GCC", after, perl = TRUE)
   after <- gsub("^(\\s*)#pragma clang", "\\1// #pragma clang", after, perl = TRUE)
   
   if (!identical(before, after))
      writeLines(after, con = file)
}
