
URL <- "https://github.com/intel/tbb/archive/v2020.1.tar.gz"
archive <- basename(URL)

# download and unpack tbb
owd <- setwd(tempdir())
download.file(URL, archive)
before <- list.files()
untar(archive)
after <- list.files()
tbb <- normalizePath(setdiff(after, before), winslash = "/", mustWork = TRUE)
setwd(owd)

# copy to src/tbb
system2("cp", c("-R", shQuote(tbb), "src/tbb"))
unlink("src/tbb", recursive = TRUE)
file.copy(tbb, "src", recursive = TRUE)

# copy header files
unlink("inst/include/tbb", recursive = TRUE)
tbbInclude <- paste(tbb, "include/", sep = "/")
args <- c("-R", shQuote(tbbInclude), "inst/include")
system2("cp", args)
