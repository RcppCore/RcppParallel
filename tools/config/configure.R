
# make sure we call correct version of R
rExe <- if (.Platform$OS.type == "windows") "R.exe" else "R"
define(R = file.path(R.home("bin"), rExe))

# check whether user has Makevars file that might cause trouble
makevars <- Sys.getenv("R_MAKEVARS_USER", unset = "~/.R/Makevars")
if (file.exists(makevars)) {
   contents <- readLines(makevars, warn = FALSE)
   pattern <- "^(PKG_CPPFLAGS|PKG_CXXFLAGS)\\s*="
   bad <- grep(pattern, contents, perl = TRUE, value = TRUE)
   if (length(bad)) {
      
      text <- c(
         "",
         sprintf("NOTE: '%s' contains variable declarations incompatible with RcppParallel:", makevars),
         "",
         paste0("\t", bad),
         "",
         "Makevars variables prefixed with 'PKG_' should be considered reserved for use by R packages.",
         ""
      )
      
      writeLines(text, con = stdout())
      
   }
}

# on Windows, check for Rtools; if it exists, and we have tbb, use it
if (.Platform$OS.type == "windows") {
   
   gccPath <- normalizePath(Sys.which("gcc"), winslash = "/")
   
   tbbLib <- Sys.getenv("TBB_LIB", unset = NA)
   if (is.na(tbbLib))
      tbbLib <- normalizePath(file.path(gccPath, "../../lib"), winslash = "/")
   
   tbbInc <- Sys.getenv("TBB_INC", unset = NA)
   if (is.na(tbbInc))
      tbbInc <- normalizePath(file.path(gccPath, "../../include"), winslash = "/")
   
   tbbFiles <- list.files(tbbLib, pattern = "^libtbb")
   if (length(tbbFiles)) {
      
      tbbPattern <- "^lib(tbb\\d*(?:_static)?)\\.a$"
      tbbName <- grep(tbbPattern, tbbFiles, perl = TRUE, value = TRUE)
      tbbName <- gsub(tbbPattern, "\\1", tbbName, perl = TRUE)
      
      tbbMallocPattern <- "^lib(tbbmalloc\\d*(?:_static)?)\\.a$"
      tbbMallocName <- grep(tbbMallocPattern, tbbFiles, perl = TRUE, value = TRUE)
      tbbMallocName <- gsub(tbbMallocPattern, "\\1", tbbMallocName, perl = TRUE)
      
      Sys.setenv(
         TBB_LIB = tbbLib,
         TBB_INC = tbbInc,
         TBB_NAME = tbbName,
         TBB_MALLOC_NAME = tbbMallocName
      )
      
   }
   
}

# try and figure out path to TBB
tbbRoot  <- Sys.getenv("TBB_ROOT", unset = NA)
tbbLib   <- Sys.getenv("TBB_LIB", unset = NA)
tbbInc   <- Sys.getenv("TBB_INC", unset = NA)

tbbName  <- Sys.getenv("TBB_NAME", unset = "tbb")
tbbMallocName <- Sys.getenv("TBB_MALLOC_NAME", unset = "tbbmalloc")

# check TBB_ROOT first if defined
if (!is.na(tbbRoot)) {
   
   if (is.na(tbbLib)) {
      tbbLib <- file.path(tbbRoot, "lib")
   }
   
   if (is.na(tbbInc)) {
      tbbInc <- file.path(tbbRoot, "include")
   }
   
}

# if TBB_LIB is defined, guess TBB_INC
if (!is.na(tbbLib) && is.na(tbbInc)) {
   tbbIncCandidate <- file.path(tbbLib, "../include")
   if (file.exists(tbbIncCandidate)) {
      tbbInc <- normalizePath(tbbIncCandidate)
   }
}

# if TBB_LIB and TBB_INC are still not defined, try auto-detecting
tryAutoDetect <-
   .Platform$OS.type == "unix" &&
   Sys.getenv("TBB_AUTODETECT", unset = "FALSE") == "TRUE" &&
   is.na(tbbLib) &&
   is.na(tbbInc)

if (tryAutoDetect) {
   
   sysInfo <- as.list(Sys.info())
   
   homebrewPrefix <- if (sysInfo$sysname == "Darwin") {
      "/opt/homebrew"
   } else {
      "/usr/local"
   }
   
   tbbLibSearch <- if (sysInfo$sysname == "Darwin") {
      file.path(homebrewPrefix, "opt/tbb/lib/libtbb.dylib")
   } else {
      Sys.glob(c(
         "/usr/*/libtbb.so",
         "/usr/*/*/libtbb.so",
         "/usr/*/*/*/libtbb.so"
      ))
   }
   
   tbbIncSearch <- if (sysInfo$sysname == "Darwin") {
      file.path(homebrewPrefix, "opt/tbb/include/tbb")
   } else {
      Sys.glob(c(
         "/usr/include/tbb.h",
         "/usr/include/*/tbb.h"
      ))
   }
   
   if (length(tbbLibSearch) &&
       length(tbbIncSearch) &&
       file.exists(tbbLibSearch[[1L]]) &&
       file.exists(tbbIncSearch[[1L]]))
   {
      tbbLib <- dirname(tbbLibSearch[[1L]])
      tbbInc <- dirname(tbbIncSearch[[1L]])
   }
   
}

# now, define TBB_LIB and TBB_INC as appropriate
define(
   TBB_LIB         = if (!is.na(tbbLib)) tbbLib else "",
   TBB_INC         = if (!is.na(tbbInc)) tbbInc else "",
   TBB_NAME        = tbbName,
   TBB_MALLOC_NAME = tbbMallocName
)

# set PKG_LIBS
pkgLibs <- if (.Platform$OS.type == "windows") {

   if (!is.na(tbbLib) && file.exists(file.path(tbbInc, "oneapi"))) {

      # downstream packages link with '-lRcppParallel' alone, so
      # RcppParallel.dll must provide the tbbmalloc API (scalable_malloc
      # and friends) even though RcppParallel itself never calls it; use
      # --whole-archive so those objects are linked in, and re-exported
      # via their '-export:' directives. tbbmalloc must precede tbb here:
      # both archives bundle an itt_notify object defining the same
      # symbols, and with tbbmalloc's copy already linked, tbb's is never
      # pulled in, avoiding duplicate definition errors
      c(
         "-Wl,-L\"$(TBB_LIB)\"",
         "-Wl,--whole-archive",
         "-l$(TBB_MALLOC_NAME)",
         "-Wl,--no-whole-archive",
         "-l$(TBB_NAME)"
      )

   } else if (!is.na(tbbLib)) {

      # with an older (non-oneTBB) toolchain like Rtools42, tbb and
      # tbbmalloc both define DllMain, so tbbmalloc cannot be linked
      # wholesale; its objects also carry no '-export:' directives, so
      # nothing would be re-exported anyhow -- just link as needed
      c(
         "-Wl,-L\"$(TBB_LIB)\"",
         "-l$(TBB_NAME)",
         "-l$(TBB_MALLOC_NAME)"
      )

   }

} else if (!is.na(tbbLib)) {

   c(
      "-Wl,-L\"$(TBB_LIB)\"",
      sprintf("-Wl,-rpath,%s", shQuote(tbbLib)),
      "-l$(TBB_NAME)",
      "-l$(TBB_MALLOC_NAME)"
   )

} else if (R.version$os == "emscripten") {
   
   c(
      "-Wl,-Ltbb/build/lib_release",
      "-l$(TBB_NAME)"
   )
   
} else {
   
   c(
      "-Wl,-Ltbb/build/lib_release",
      "-l$(TBB_NAME)",
      "-l$(TBB_MALLOC_NAME)"
   )
   
}


# on Windows, we may need to link to ssp; otherwise,
# we see errors like
#
#    C:\rtools43\x86_64-w64-mingw32.static.posix\bin/ld.exe: C:/rtools43/x86_64-w64-mingw32.static.posix/lib/libtbb12.a(allocator.cpp.obj):allocator.cpp:(.text+0x18b): undefined reference to `__stack_chk_fail'
#
if (.Platform$OS.type == "windows") {
   pkgLibs <- c(pkgLibs, "-lssp")
}

define(PKG_LIBS = paste(pkgLibs, collapse = " "))
   
# if we're going to build tbb from sources, check for cmake
# (not required on Windows, where the bundled TBB is never built;
# without an Rtools TBB, the tinythread fallback is used instead)
define(CMAKE = "")
if (is.na(tbbLib) && .Platform$OS.type != "windows") {
   
   cmake <- local({
      
      # check for envvar
      cmake <- Sys.getenv("CMAKE", unset = NA)
      if (!is.na(cmake))
         return(cmake)
      
      # check for path
      cmake <- Sys.which("cmake")
      if (nzchar(cmake))
         return(cmake)
      
      # check for macOS cmake
      cmake <- "/Applications/CMake.app/Contents/bin/cmake"
      if (file.exists(cmake))
         return(cmake)
      
      stop("cmake was not found")
      
   })
   
   # make sure we have an appropriate version of cmake installed
   # (use the resolved path; cmake may not be on the PATH)
   output <- system(paste(shQuote(cmake), "--version"), intern = TRUE)[[1L]]
   cmakeVersion <- numeric_version(sub("cmake version ", "", output))
   if (cmakeVersion < "3.5") {
      stop("error: RcppParallel requires cmake (>= 3.6); you have ", cmakeVersion)
   }
   
   define(CMAKE = cmake)
   
}


# now, set up PKG_CPPFLAGS
if (!is.na(tbbLib)) {
   define(PKG_CPPFLAGS = "-I../inst/include -I\"$(TBB_INC)\"")
} else {
   define(PKG_CPPFLAGS = "-I../inst/include")
}

# PKG_CXXFLAGS
if (.Platform$OS.type == "windows" && is.na(tbbLib)) {
   define(TBB_ENABLED = FALSE)
   define(PKG_CXXFLAGS = "-DRCPP_PARALLEL_USE_TBB=0")
} else {
   define(TBB_ENABLED = TRUE)
   define(PKG_CXXFLAGS = "-DRCPP_PARALLEL_USE_TBB=1")
}

# macOS needs some extra flags set
if (Sys.info()[["sysname"]] == "Darwin") {
   define(PKG_LIBS_EXTRA = "-Wl,-rpath,@loader_path/../lib")
} else if (Sys.info()[["sysname"]] == "Linux") {
   define(PKG_LIBS_EXTRA = "-Wl,-rpath,$(ORIGIN)/../lib")
} else {
   define(PKG_LIBS_EXTRA = "")
   
}
