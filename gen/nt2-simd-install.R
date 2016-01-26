NT2_URL <- "https://github.com/jfalcou/nt2"

pathProg <- function(name) {
   prog <- Sys.which(name)
   if (!nzchar(prog))
      stop("No program named '", name, "' on the PATH!", call. = FALSE)
   prog
}

cmakeDef <- function(name, value) {
   sprintf("-D%s=%s", name, value)
}

cmake <- pathProg("cmake")
make <- pathProg("make")
git <- pathProg("git")

owd <- getwd()
# Check out the 'nt2' sources
if (!dir.exists("nt2"))
   system2(git, c("clone", NT2_URL))

setwd("nt2")

# Prepare installation directory
if (dir.exists("install"))
   unlink("install", recursive = TRUE)
dir.create("install")
installDir <- file.path(getwd(), "install")

# Enter 'nt2' directory, and check out relevant commit
if (dir.exists("build"))
   unlink("build", recursive = TRUE)
dir.create("build")
setwd("build")

# Call cmake to prepare the build
system2(cmake, c(
   "..",
   cmakeDef("CMAKE_INSTALL_PREFIX", installDir)
))

# Call 'make', 'make install' to build everything
system2(make)
system2(make, "install")

# Go back to parent directory
setwd(owd)

# Copy all of the relevant headers over
includePath <- file.path(installDir, "include")
from <- list.files(includePath, full.names = TRUE)
to   <- file.path("inst/include")
file.copy(from, to, recursive = TRUE)

# Fix up the boost SIMD headers
source("gen/boost-simd-headers-fixup.R")

