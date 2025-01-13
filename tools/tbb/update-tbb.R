
# update as appropriate for new TBB releases, then re-run script
url <- "https://github.com/uxlfoundation/oneTBB/archive/refs/tags/v2022.0.0.tar.gz"

owd <- setwd("src")
unlink("tbb", recursive = TRUE)
download.file(url, destfile = basename(url), mode = "wb")

before <- list.files()
untar(basename(url))
after <- list.files()

folder <- setdiff(after, before)
print(folder)
file.rename(folder, "tbb")

setwd("tbb")
remove <- c(".gitattributes", ".github", "doc", "examples", "python", "test")
unlink(remove, recursive = TRUE)
bazel <- list.files(pattern = "[Bb]azel")
unlink(bazel)
setwd("..")

unlink(basename(url))
