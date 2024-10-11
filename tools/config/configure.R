
# defualt compiler unset
define(COMPILER = "")

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

# define special flags for Windows
db <- configure_database()
info <- as.list(Sys.info())
if (info[["sysname"]] == "Windows") {
   
   # for older versions of R, we need to resolve the
   # 'true' path to the C / C++ compiler; we do so
   # via the cygpath utility here
   fmt <- if (getRversion() < "4.2.0") {
      cygpath <- nzchar(Sys.which("cygpath"))
      if (cygpath) "$(shell cygpath -m \"%s\")" else "%s"
   } else {
      "%s"
   }

   define(
      WINDOWS_CC    = sprintf(fmt, db$CC),
      WINDOWS_CXX11 = sprintf(fmt, db$CXX11)
   )

}

# on Solaris, check if we're using gcc or g++
if (Sys.info()[["sysname"]] == "SunOS") {
   cxx <- r_cmd_config("CXX")
   version <- system(paste(cxx, "--version"), intern = TRUE)
   for (compiler in c("gcc", "g++")) {
      if (any(grepl(compiler, version, fixed = TRUE))) {
         define(COMPILER = "gcc")
      }
   }
}

# try and figure out path to TBB
tbbRoot <- Sys.getenv("TBB_ROOT", unset = NA)
tbbLib  <- Sys.getenv("TBB_LIB", unset = NA)
tbbInc  <- Sys.getenv("TBB_INC", unset = NA)

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
   TBB_LIB = if (!is.na(tbbLib)) tbbLib else "",
   TBB_INC = if (!is.na(tbbInc)) tbbInc else ""
)
