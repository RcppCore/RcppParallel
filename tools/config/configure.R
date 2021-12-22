
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
cxx <- NULL
candidates <- c("CXX11", "CXX1X", "CXX")
for (candidate in candidates) {
   value <- r_cmd_config(candidate)
   if (!is.null(value)) {
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

# avoid including /usr/local/include, as this can cause
# RcppParallel to find and use a version of libtbb installed
# there as opposed to the bundled version
cppflags <- read_r_config("CPPFLAGS", envir = NULL)[[1]]
cppflags <- sub("(?: )?-I/usr/local/include", "", cppflags)

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

# use c++0x for compatibility with older compilers
if (getRversion() < "4.0") {
   define(STDVER = "stdver=c++0x")
} else {
   define(STDVER = "")
}

# on Solaris, check if we're using gcc or g++
define(COMPILER = "")
if (Sys.info()[["sysname"]] == "SunOS") {
   cxx <- r_cmd_config("CXX")
   version <- system(paste(cxx, "--version"), intern = TRUE)
   for (compiler in c("gcc", "g++")) {
      if (any(grepl(compiler, version, fixed = TRUE))) {
         define(COMPILER = "gcc")
      }
   }
}

