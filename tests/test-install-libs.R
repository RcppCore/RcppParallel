# Unit tests for the install-time helpers defined in src/install.libs.R.
#
# These helpers run during 'R CMD INSTALL' (before the package is loadable),
# so they live in src/install.libs.R rather than in R/ and cannot be reached
# via library(RcppParallel). Instead, we locate that source file, evaluate the
# helper definitions that precede its '# Main' section (evaluating the whole
# file would trigger an actual install), and exercise them directly.

RcppParallel:::test_init()

# locate src/install.libs.R by walking up from the working directory; this is
# reachable when tests are run from the package sources. If it cannot be found
# (e.g. only the installed package is available), skip rather than fail.
findInstallLibs <- function() {
   dir <- normalizePath(getwd(), mustWork = FALSE)
   for (i in 1:8) {
      candidate <- file.path(dir, "src", "install.libs.R")
      if (file.exists(candidate))
         return(candidate)
      parent <- dirname(dir)
      if (identical(parent, dir))
         break
      dir <- parent
   }
   NA_character_
}

path <- findInstallLibs()
if (is.na(path)) {
   writeLines("skipping: could not locate src/install.libs.R")
   quit(save = "no", status = 0L)
}

# evaluate only the helper definitions, stopping before the '# Main' section
lines <- readLines(path)
marker <- grep("^# Main", lines)
if (length(marker))
   lines <- lines[seq_len(marker[[1L]] - 1L)]

env <- new.env(parent = globalenv())
eval(parse(text = paste(lines, collapse = "\n")), envir = env)
splitCompilerVar <- get("splitCompilerVar", envir = env)
extractCompilerLauncher <- get("extractCompilerLauncher", envir = env)
patchTbbMachineHeader <- get("patchTbbMachineHeader", envir = env)

# minimal assertion harness
failures <- 0L
check <- function(cond, label) {
   ok <- isTRUE(cond)
   if (!ok)
      failures <<- failures + 1L
   writeLines(sprintf("%s - %s", if (ok) "PASS" else "FAIL", label))
}

# run 'expr' with the given environment variables set, restoring the previous
# environment afterwards so tests can't leak into one another (or into CC/CXX)
withEnv <- function(vars, expr) {
   keys <- names(vars)
   previous <- Sys.getenv(keys, unset = NA, names = TRUE)
   on.exit({
      set <- previous[!is.na(previous)]
      if (length(set))
         do.call(Sys.setenv, as.list(set))
      unset <- keys[is.na(previous)]
      if (length(unset))
         Sys.unsetenv(unset)
   }, add = TRUE)
   do.call(Sys.setenv, as.list(vars))
   force(expr)
}

# the regression this branch fixes: '$(CCACHE) g++' with an empty CCACHE
# expands to ' g++' (leading space). scan() yields a single token, and the
# old early-return left the leading space in place, forwarding an invalid
# '-DCMAKE_CXX_COMPILER= g++' to CMake. The compiler must be normalized.
withEnv(c(TEST_CXX = " g++", TEST_CXXFLAGS = ""), {
   result <- splitCompilerVar("TEST_CXX", "TEST_CXXFLAGS")
   check(isTRUE(result), "leading-whitespace compiler returns TRUE")
   check(identical(Sys.getenv("TEST_CXX"), "g++"),
      "leading-whitespace compiler is normalized (no leading space)")
   check(identical(Sys.getenv("TEST_CXXFLAGS"), ""),
      "leading-whitespace compiler leaves flags untouched")
})

# a plain single-token compiler is already clean, but should still be
# re-set (and report TRUE) so the normalization path is exercised uniformly
withEnv(c(TEST_CXX = "g++", TEST_CXXFLAGS = ""), {
   result <- splitCompilerVar("TEST_CXX", "TEST_CXXFLAGS")
   check(isTRUE(result), "single-token compiler returns TRUE")
   check(identical(Sys.getenv("TEST_CXX"), "g++"),
      "single-token compiler is preserved")
})

# trailing tokens are split off as flags and prepended to any existing flags
withEnv(c(TEST_CXX = "g++ -std=c++17 -O2", TEST_CXXFLAGS = "-Wall"), {
   result <- splitCompilerVar("TEST_CXX", "TEST_CXXFLAGS")
   check(isTRUE(result), "compiler with flags returns TRUE")
   check(identical(Sys.getenv("TEST_CXX"), "g++"),
      "compiler with flags splits off the compiler token")
   check(identical(Sys.getenv("TEST_CXXFLAGS"), "-std=c++17 -O2 -Wall"),
      "compiler with flags prepends split flags to existing flags")
})

# a whitespace-only value tokenizes to nothing: report FALSE and change nothing
withEnv(c(TEST_CXX = "   ", TEST_CXXFLAGS = "-Wall"), {
   result <- splitCompilerVar("TEST_CXX", "TEST_CXXFLAGS")
   check(identical(result, FALSE), "whitespace-only compiler returns FALSE")
   check(identical(Sys.getenv("TEST_CXXFLAGS"), "-Wall"),
      "whitespace-only compiler leaves flags untouched")
})

# an unset compiler variable is a no-op that reports FALSE
Sys.unsetenv("TEST_CXX_UNSET")
check(identical(splitCompilerVar("TEST_CXX_UNSET", "TEST_CXXFLAGS"), FALSE),
   "unset compiler variable returns FALSE")

# a leading compiler launcher (ccache) must be split off from the compiler so
# CMake can receive it via CMAKE_<LANG>_COMPILER_LAUNCHER. Left in place, CMake
# would treat 'ccache' as the compiler and run 'ccache ... -Wa,-v' during its
# assembler probe, which ccache rejects with "invalid option -- 'W'".
withEnv(c(TEST_CXX = "ccache g++"), {
   launcher <- extractCompilerLauncher("TEST_CXX")
   check(identical(launcher, "ccache"), "ccache launcher is extracted")
   check(identical(Sys.getenv("TEST_CXX"), "g++"),
      "ccache launcher is stripped from the compiler")
})

# the launcher may be a full path and carry trailing compiler flags; only the
# launcher token is removed, leaving the compiler and its flags intact
withEnv(c(TEST_CXX = "/usr/bin/ccache g++ -std=c++17"), {
   launcher <- extractCompilerLauncher("TEST_CXX")
   check(identical(launcher, "/usr/bin/ccache"),
      "ccache launcher path is extracted")
   check(identical(Sys.getenv("TEST_CXX"), "g++ -std=c++17"),
      "compiler and flags survive launcher extraction")
})

# sccache is recognized as a launcher too
withEnv(c(TEST_CXX = "sccache clang++"), {
   launcher <- extractCompilerLauncher("TEST_CXX")
   check(identical(launcher, "sccache"), "sccache launcher is extracted")
   check(identical(Sys.getenv("TEST_CXX"), "clang++"),
      "sccache launcher is stripped from the compiler")
})

# a plain compiler has no launcher: return NA and leave the variable untouched
withEnv(c(TEST_CXX = "g++ -O2"), {
   launcher <- extractCompilerLauncher("TEST_CXX")
   check(identical(launcher, NA_character_),
      "plain compiler yields no launcher")
   check(identical(Sys.getenv("TEST_CXX"), "g++ -O2"),
      "plain compiler is left unmodified")
})

# an unset compiler variable is a no-op that reports NA
Sys.unsetenv("TEST_CXX_UNSET")
check(identical(extractCompilerLauncher("TEST_CXX_UNSET"), NA_character_),
   "unset compiler variable yields no launcher")

# the mingw cpuid guard should be applied exactly once to a header with the
# expected form, and applying it again should leave the header untouched
header <- tempfile(fileext = ".h")
writeLines(c("#pragma once", "#include <intrin.h>", "int value;"), header)
patchTbbMachineHeader(header)
patched <- readLines(header)
check(any(grepl("push_macro", patched, fixed = TRUE)),
   "cpuid guard is applied to a well-formed header")
patchTbbMachineHeader(header)
check(identical(readLines(header), patched),
   "cpuid guard application is idempotent")

# a header without exactly one matching include line must not be modified,
# and the skipped patch must be surfaced as a warning (a silent no-op here
# would quietly reintroduce the mingw __cpuid build failure)
malformed <- tempfile(fileext = ".h")
original <- c("#pragma once", "  #include <intrin.h>")
writeLines(original, malformed)
warned <- FALSE
withCallingHandlers(
   patchTbbMachineHeader(malformed),
   warning = function(w) {
      warned <<- TRUE
      invokeRestart("muffleWarning")
   }
)
check(warned, "unexpected header form emits a warning")
check(identical(readLines(malformed), original),
   "unexpected header form is left unmodified")
unlink(c(header, malformed))

if (failures > 0L)
   stop(sprintf("%d install.libs.R helper test(s) failed", failures))

writeLines("all install.libs.R helper tests passed")
