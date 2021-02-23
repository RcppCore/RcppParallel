
# Avoid usages of memset() that might cause compiler warnings.
# This is necessary for CRAN submissions of RcppParallel.

files <- list.files(
   path = "src/tbb",
   pattern = "[.](?:h|cpp)$",
   all.files = TRUE,
   full.names = TRUE,
   recursive = TRUE
)

pattern <- "(memset\\s*\\(\\s*)(\\w+)(\\s*[,)])"

for (file in files) {
   
   before <- readLines(file)
   after <- gsub(pattern, "\\1static_cast<void*>(\\2)\\3", before, perl = TRUE)
   
   if (!identical(before, after))
      writeLines(after, con = file)
}
