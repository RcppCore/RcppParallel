
# silence pragma messages
files <- list.files(recursive = TRUE, full.names = TRUE)
lapply(files, function(file) {
   
   contents <- readLines(file, warn = FALSE)
   idx <- grep("^\\s*#pragma message", contents)
   if (length(idx) == 0)
      next
   
   contents[idx] <- paste("//", contents[idx])
   writeLines(contents, con = file)
   
})