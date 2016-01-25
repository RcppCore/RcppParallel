pathProg <- function(name) {
   prog <- Sys.which(name)
   if (!nzchar(prog))
      stop("No program named '", name, "' on PATH!", call. = FALSE)
   prog
}

git <- pathProg("git")

if (!dir.exists("inst/include/boost"))
   dir.create("inst/include/boost")

BOOST_DISPATCH_URL <- "https://github.com/NumScale/boost.dispatch"
BOOST_SIMD_URL <- "https://github.com/NumScale/boost.simd"

if (!dir.exists("boost.dispatch"))
   system2(git, c("clone", BOOST_DISPATCH_URL, "boost.dispatch"))
files <- list.files("boost.dispatch/include/boost", full.names = TRUE)
for (file in files)
   file.copy(file, "inst/include/boost", recursive = TRUE)

if (!dir.exists("boost.simd"))
   system2(git, c("clone", BOOST_SIMD_URL, "boost.simd"))
files <- list.files("boost.simd/include/boost", full.names = TRUE)
for (file in files)
   file.copy(file, "inst/include/boost", recursive = TRUE)