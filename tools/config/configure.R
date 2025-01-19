
# use new tbb for newer versions of R
tbbSrc <- Sys.getenv("TBB_SRC", unset = NA)
if (is.na(tbbSrc)) {
   tbbSrc <- if (getRversion() >= "4.5.0") "tbb" else "tbb-2019"
}

# set up some default flags
define(TBB_ENABLED = TRUE)
define(TBB_STATIC = FALSE)
define(TBB_SRC = tbbSrc)


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

# Figure out the appropriate CXX prefix for the current
# version of R + configuration.
cxx <- "/usr/bin/c++"
candidates <- c("CXX11", "CXX1X", "CXX")
for (candidate in candidates) {
   value <- r_cmd_config(candidate)
   if (!is.null(value)) {
      if (any(grepl("icpc", value))) {
         define(COMPILER = "icc")
      }
      cxx <- candidate
      break
   }
}

# work around issue with '-Werror=format-security' being specified without
# a prior '-Wformat', which makes gcc angry
cxxflags <- read_r_config(sprintf("%sFLAGS", cxx), envir = NULL)[[1]]
broken <-
   grepl(" -Werror=format-security ", cxxflags) &&
   !grepl(" -Wformat ", cxxflags)

if (broken)
   cxxflags <- gsub("-Werror=format-security", "-Wformat -Werror=format-security", cxxflags)

# add C++ standard if not set
if (!grepl("-std=", cxxflags, fixed = TRUE)) {
   stdflag <- if (getRversion() < "4.0") {
      "-std=c++0x"
   } else {
      "$(CXX11STD)"
   }
   cxxflags <- paste(stdflag, cxxflags)
}

# avoid including /usr/local/include, as this can cause
# RcppParallel to find and use a version of libtbb installed
# there as opposed to the bundled version
cppflags <- read_r_config("CPPFLAGS", envir = NULL)[[1]]
cppflags <- sub("(?: )?-I/usr/local/include", "", cppflags)
cppflags <- sub("(?: )?-I/opt/homebrew/include", "", cppflags)
cppflags <- sub("(?: )?-I/opt/local/libexec/onetbb/include", "", cppflags)

# define the set of flags appropriate to the current
# configuration of R
switch(
   cxx,
   
   CXX11 = define(
      CC            = "$(CC)",
      CPPFLAGS      = cppflags,
      CXX11         = "$(CXX11)",
      CXX11FLAGS    = cxxflags,
      CXX11STD      = "$(CXX11STD)",
      CXX11PICFLAGS = "$(CXX11PICFLAGS)"
   ),
   
   CXX1X = define(
      CC            = "$(CC)",
      CPPFLAGS      = cppflags,
      CXX11         = "$(CXX1X)",
      CXX11FLAGS    = cxxflags,
      CXX11STD      = "$(CXX1XSTD)",
      CXX11PICFLAGS = "$(CXX1XPICFLAGS)"
   ),
   
   CXX = define(
      CC            = "$(CC)",
      CPPFLAGS      = cppflags,
      CXX11         = "$(CXX)",
      CXX11FLAGS    = cxxflags,
      CXX11STD      = "-std=c++0x",
      CXX11PICFLAGS = "-fPIC"
   ),
   
   stop("Failed to infer C / C++ compilation flags")
)

# on Windows, check for Rtools; if it exists, and we have tbb, use it
if (getRversion() >= "4.5.0" && .Platform$OS.type == "windows") {
   
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
      
      define(TBB_STATIC = TRUE)
      
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
pkgLibs <- if (!is.na(tbbLib)) {
   
   c(
      "-Wl,-L\"$(TBB_LIB)\"",
      sprintf("-Wl,-rpath,%s", shQuote(tbbLib)),
      "-l$(TBB_NAME)",
      "-l$(TBB_MALLOC_NAME)"
   )
   
} else if (.Platform$OS.type == "windows") {
   
   NULL
   
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
define(CMAKE = "")
if (tbbSrc == "tbb" && is.na(tbbLib)) {
   
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
   output <- system("cmake --version", intern = TRUE)[[1L]]
   cmakeVersion <- numeric_version(sub("cmake version ", "", output))
   if (cmakeVersion < "3.5") {
      stop("error: RcppParallel requires cmake (>= 3.6); you have ", cmakeVersion)
   }
   
   define(CMAKE = cmake)
   
}

# set TBB_RPATH
if (!is.na(tbbLib)) {
   define(TBB_RPATH = sprintf("-Wl,-rpath,%s", shQuote(tbbLib)))
} else {
   define(TBB_RPATH = "")
}


# now, set up PKG_CPPFLAGS
if (!is.na(tbbLib)) {
   define(PKG_CPPFLAGS = "-I../inst/include -I\"$(TBB_INC)\"")
} else {
   define(PKG_CPPFLAGS = "-I../inst/include")
}

# macOS needs some extra flags set
if (Sys.info()[["sysname"]] == "Darwin") {
   define(PKG_LIBS_EXTRA = "-Wl,-rpath,@loader_path/../lib")
} else {
   define(PKG_LIBS_EXTRA = "")
}
