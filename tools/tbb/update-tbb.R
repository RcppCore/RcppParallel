
# update as appropriate for new TBB releases, then re-run script
url <- "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.1.1.tar.gz"

owd <- setwd("src")
unlink("tbb", recursive = TRUE)
download.file(url, destfile = basename(url), mode = "wb")

before <- list.files()
untar(basename(url))
after <- list.files()

folder <- setdiff(after, before)
print(folder)
file.rename(folder, "tbb")

unlink(basename(url))
