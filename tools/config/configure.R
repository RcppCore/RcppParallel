
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

# define the set of flags appropriate to the current
# configuration of R
switch(
   cxx,
   
   CXX11 = define(
      CC            = "$(CC)",
      CXX11         = "$(CXX11)",
      CXX11FLAGS    = "$(CXX11FLAGS)",
      CXX11STD      = "$(CXX11STD)",
      CXX11PICFLAGS = "$(CXX11PICFLAGS)"
   ),
   
   CXX1X = define(
      CC            = "$(CC)",
      CXX11         = "$(CXX1X)",
      CXX11FLAGS    = "$(CXX1XFLAGS)",
      CXX11STD      = "$(CXX1XSTD)",
      CXX11PICFLAGS = "$(CXX1XPICFLAGS)"
   ),
   
   CXX = define(
      CC            = "$(CC)",
      CXX11         = "$(CXX)",
      CXX11FLAGS    = "$(CXXFLAGS)",
      CXX11STD      = "-std=c++0x",
      CXX11PICFLAGS = "-fPIC"
   ),
   
   stop("Failed to infer C / C++ compilation flags")
)

# use c++0x for compatibility with older compilers
define(STDVER = "c++0x")

