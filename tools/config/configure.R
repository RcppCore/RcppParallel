
# Figure out the appropriate CXX prefix for the current
# version of R + configuration.
cxx <- NULL
candidates <- c("CXX11", "CXX1X", "CXX")
for (candidate in candidates) {
   config <- read_r_config(candidate, envir = NULL)
   value <- config[[candidate]]
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

# define the set of flags appropriate to the current
# configuration of R
switch(
   cxx,
   
   CXX11 = define(
      CC            = "$(CC)",
      CXX11         = "$(CXX11)",
      CXX11FLAGS    = cxxflags,
      CXX11STD      = "$(CXX11STD)",
      CXX11PICFLAGS = "$(CXX11PICFLAGS)"
   ),
   
   CXX1X = define(
      CC            = "$(CC)",
      CXX11         = "$(CXX1X)",
      CXX11FLAGS    = cxxflags,
      CXX11STD      = "$(CXX1XSTD)",
      CXX11PICFLAGS = "$(CXX1XPICFLAGS)"
   ),
   
   CXX = define(
      CC            = "$(CC)",
      CXX11         = "$(CXX)",
      CXX11FLAGS    = cxxflags,
      CXX11STD      = "-std=c++0x",
      CXX11PICFLAGS = "-fPIC"
   ),
   
   stop("Failed to infer C / C++ compilation flags")
)

# define special flags for Windows
db <- configure_database()
if (Sys.info()[["sysname"]] == "Windows") {
   
   cygpath <- nzchar(Sys.which("cygpath"))
   fmt <- if (cygpath) "$(shell cygpath -m \"%s\")" else "%s"
   define(
      WINDOWS_CC    = sprintf(fmt, db$CC),
      WINDOWS_CXX11 = sprintf(fmt, db$CXX11)
   )

}

# use c++0x for compatibility with older compilers
define(STDVER = "c++0x")

