
# Check that a package linking against RcppParallel's TBB can be loaded on its
# own, in a process that has not already loaded RcppParallel.
#
# The TBB libraries we ship on macOS record an '@rpath'-relative install name,
# so LdFlags() must emit an '-rpath' alongside its '-L'. With only the '-L' the
# link still succeeds -- so the package builds, and loads fine via its
# NAMESPACE, whose importFrom(RcppParallel, ...) pulls TBB into the process
# first -- but the shared object itself carries no runtime search path, and
# dyld fails with "Library not loaded: @rpath/libtbb.dylib" for anything that
# loads it directly. Hence the load below runs in a fresh R process which never
# touches RcppParallel; loading it from here would prove nothing.
#
# See also tests/test-ld-flags.R, the cheap flag-level check that still runs
# where no toolchain is available.
#
# https://github.com/RcppCore/RcppParallel/issues/209

RcppParallel:::test_init()

# building the test package requires a toolchain, so keep this test
# off of CRAN's machines
ci <- nzchar(Sys.getenv("CI")) || identical(Sys.getenv("NOT_CRAN"), "true")
if (!ci) {
   writeLines("Not running on CI; skipping downstream load test.")
   quit(save = "no")
}

if (!TBB_ENABLED) {
   writeLines("TBB is not enabled; skipping downstream load test.")
   quit(save = "no")
}

# Windows has no rpath: the loader resolves DLLs through the process search
# path, and downstream packages link '-lRcppParallel' rather than TBB itself
if (is_windows()) {
   writeLines("Windows resolves DLLs via the search path; skipping.")
   quit(save = "no")
}

# A standalone load can only work where TBB is linked into the client
# explicitly: macOS (#206), and any platform configured against a system TBB.
# Elsewhere the TBB symbols are deliberately left undefined at link time and
# resolved from the libraries RcppParallel loads, so a standalone load is
# expected to fail. Note this mirrors the branches in tbbLdFlags() rather than
# inspecting its output: gating on the '-rpath' we are checking for would skip
# precisely the configuration that regressed.
tbbLib <- Sys.getenv("TBB_LINK_LIB", Sys.getenv("TBB_LIB", unset = TBB_LIB))
if (!is_mac() && !nzchar(tbbLib)) {
   writeLines("TBB is not linked into downstream packages here; skipping.")
   quit(save = "no")
}

# generate the test package
pkgRoot <- file.path(tempdir(), "downstreamtest")
dir.create(file.path(pkgRoot, "src"), recursive = TRUE, showWarnings = FALSE)

writeLines(con = file.path(pkgRoot, "DESCRIPTION"), c(
   "Package: downstreamtest",
   "Type: Package",
   "Title: Test Loading a Package Linked Against RcppParallel's TBB",
   "Version: 0.1.0",
   "Author: RcppParallel Authors",
   "Maintainer: RcppParallel Authors <noreply@example.com>",
   "Description: Confirms that such packages can be loaded standalone.",
   "License: GPL-2",
   "Imports: RcppParallel"
))

writeLines(con = file.path(pkgRoot, "NAMESPACE"), c(
   "useDynLib(downstreamtest)",
   "importFrom(RcppParallel, RcppParallelLibs)"
))

writeLines(con = file.path(pkgRoot, "src", "Makevars"), c(
   'PKG_CXXFLAGS = $(shell "${R_HOME}/bin/Rscript" -e "RcppParallel::CxxFlags()")',
   'PKG_LIBS = $(shell "${R_HOME}/bin/Rscript" -e "RcppParallel::RcppParallelLibs()")'
))

# call into TBB proper, so that the shared object records a real load-time
# dependency on the TBB library rather than merely being linked against it
writeLines(con = file.path(pkgRoot, "src", "concurrency.cpp"), c(
   "#include <tbb/task_arena.h>",
   "",
   "#include <R.h>",
   "#include <Rinternals.h>",
   "",
   'extern "C" SEXP downstream_max_concurrency(void)',
   "{",
   "   return Rf_ScalarInteger(tbb::this_task_arena::max_concurrency());",
   "}"
))

# install it, making sure child processes resolve this RcppParallel
libDir <- file.path(tempdir(), "library")
dir.create(libDir, recursive = TRUE, showWarnings = FALSE)
Sys.setenv(R_LIBS = paste(.libPaths(), collapse = .Platform$path.sep))

rExe <- file.path(R.home("bin"), "R")
args <- c("CMD", "INSTALL", "--no-multiarch", paste0("--library=", shQuote(libDir)), shQuote(pkgRoot))

output <- suppressWarnings(system2(rExe, args, stdout = TRUE, stderr = TRUE))
writeLines(output)

status <- attr(output, "status")
if (is.numeric(status) && status != 0L)
   stop("error installing test package (status code ", status, ")")

# locate the shared object that was just built
pattern <- paste0("^downstreamtest\\", .Platform$dynlib.ext, "$")
shlib <- list.files(
   file.path(libDir, "downstreamtest", "libs"),
   pattern    = pattern,
   recursive  = TRUE,
   full.names = TRUE
)

assert(length(shlib) == 1L)

# load it from a process which has never loaded RcppParallel; deparse() is used
# to embed the path as a properly-quoted R string literal
script <- file.path(tempdir(), "downstream-load.R")
writeLines(con = script, c(
   'if ("RcppParallel" %in% loadedNamespaces())',
   '   stop("RcppParallel is loaded; this check would prove nothing")',
   "",
   sprintf("dll <- dyn.load(%s)", deparse(shlib)),
   'value <- .Call(getNativeSymbolInfo("downstream_max_concurrency", dll))',
   'cat("max concurrency:", value, "\\n")',
   "",
   'if (!is.integer(value) || is.na(value) || value < 1L)',
   '   stop("unexpected concurrency: ", value)'
))

rscript <- file.path(R.home("bin"), "Rscript")
output <- suppressWarnings(system2(rscript, c("--vanilla", shQuote(script)), stdout = TRUE, stderr = TRUE))
writeLines(output)

status <- attr(output, "status")
assert(is.null(status) || status == 0L)
