
# Check that packages using TBB's scalable allocator can be compiled, linked,
# and loaded against this installation of RcppParallel.
#
# On Windows, downstream packages link only '-lRcppParallel', and so this
# requires RcppParallel.dll to re-export the tbbmalloc API on their behalf.
# On other platforms, the symbols are left undefined at link time, and
# resolved from the tbbmalloc library loaded when RcppParallel is loaded.
#
# https://github.com/RcppCore/RcppParallel/pull/262

RcppParallel:::test_init()

# building the test package requires a toolchain, so keep this test
# off of CRAN's machines
ci <- nzchar(Sys.getenv("CI")) || identical(Sys.getenv("NOT_CRAN"), "true")
if (!ci) {
   writeLines("Not running on CI; skipping scalable allocator test.")
   quit(save = "no")
}

# the scalable allocator is only available with the TBB backend
if (!TBB_ENABLED) {
   writeLines("TBB is not enabled; skipping scalable allocator test.")
   quit(save = "no")
}

# generate the test package
pkgRoot <- file.path(tempdir(), "scalabletest")
dir.create(file.path(pkgRoot, "src"), recursive = TRUE, showWarnings = FALSE)

writeLines(con = file.path(pkgRoot, "DESCRIPTION"), c(
   "Package: scalabletest",
   "Type: Package",
   "Title: Test Linking to the TBB Scalable Allocator",
   "Version: 0.1.0",
   "Author: RcppParallel Authors",
   "Maintainer: RcppParallel Authors <noreply@example.com>",
   "Description: Confirms that packages can use the TBB scalable allocator.",
   "License: GPL-2",
   "Imports: RcppParallel"
))

writeLines(con = file.path(pkgRoot, "NAMESPACE"), c(
   "useDynLib(scalabletest)",
   "importFrom(RcppParallel, RcppParallelLibs)"
))

writeLines(con = file.path(pkgRoot, "src", "Makevars"), c(
   'PKG_CXXFLAGS = $(shell "${R_HOME}/bin/Rscript" -e "RcppParallel::CxxFlags()")',
   'PKG_LIBS = $(shell "${R_HOME}/bin/Rscript" -e "RcppParallel::RcppParallelLibs()")'
))

writeLines(con = file.path(pkgRoot, "src", "Makevars.win"), c(
   'PKG_CXXFLAGS = $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "RcppParallel::CxxFlags()")',
   'PKG_LIBS = $(shell "${R_HOME}/bin${R_ARCH_BIN}/Rscript.exe" -e "RcppParallel::RcppParallelLibs()")'
))

writeLines(con = file.path(pkgRoot, "src", "scalable.cpp"), c(
   "#include <tbb/scalable_allocator.h>",
   "",
   "#include <R.h>",
   "#include <Rinternals.h>",
   "",
   'extern "C" SEXP scalable_roundtrip(SEXP sizeSEXP)',
   "{",
   "   int size = Rf_asInteger(sizeSEXP);",
   "",
   "   double* data = (double*) scalable_malloc(size * sizeof(double));",
   "   if (data == NULL)",
   "      return Rf_ScalarLogical(FALSE);",
   "",
   "   for (int i = 0; i < size; i++)",
   "      data[i] = i;",
   "",
   "   double total = 0.0;",
   "   for (int i = 0; i < size; i++)",
   "      total += data[i];",
   "",
   "   scalable_free(data);",
   "",
   "   double expected = (double) size * (size - 1) / 2;",
   "   return Rf_ScalarLogical(total == expected);",
   "}"
))

# install it, making sure child processes resolve this RcppParallel
libDir <- file.path(tempdir(), "library")
dir.create(libDir, recursive = TRUE, showWarnings = FALSE)
Sys.setenv(R_LIBS = paste(.libPaths(), collapse = .Platform$path.sep))

rExe <- file.path(R.home("bin"), if (.Platform$OS.type == "windows") "R.exe" else "R")
args <- c("CMD", "INSTALL", "--no-multiarch", paste0("--library=", shQuote(libDir)), shQuote(pkgRoot))

output <- suppressWarnings(system2(rExe, args, stdout = TRUE, stderr = TRUE))
writeLines(output)

status <- attr(output, "status")
if (is.numeric(status) && status != 0L)
   stop("error installing test package (status code ", status, ")")

# load it, and check that the scalable allocator can be used
invisible(loadNamespace("scalabletest", lib.loc = libDir))
ok <- .Call("scalable_roundtrip", 1000L, PACKAGE = "scalabletest")
writeLines(paste("scalable allocator round trip:", if (isTRUE(ok)) "OK" else "FAILED"))
assert(isTRUE(ok))
