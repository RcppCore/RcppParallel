if (Sys.info()[["sysname"]] == "Windows" && getRversion() < "3.1.0") {
   define(
      CC            = "$(CC)",
      CXX11         = "$(CXX)",
      CXX11FLAGS    = "$(CXXFLAGS)",
      CXX11STD      = "-std=c++0x",
      CXX11PICFLAGS = "-fPIC",
      CXX_STD       = "CXX98"
   )
} else if (getRversion() < "3.4.0") {
   define(
      CC            = "$(CC)",
      CXX11         = "$(CXX1X)",
      CXX11FLAGS    = "$(CXX1XFLAGS)",
      CXX11STD      = "$(CXX1XSTD)",
      CXX11PICFLAGS = "$(CXX1XPICFLAGS)",
      CXX_STD       = "CXX11"
   )
} else {
   define(
      CC            = "$(CC)",
      CXX11         = "$(CXX11)",
      CXX11FLAGS    = "$(CXX11FLAGS)",
      CXX11STD      = "$(CXX11STD)",
      CXX11PICFLAGS = "$(CXX11PICFLAGS)",
      CXX_STD       = "CXX11"
   )
}

# use c++0x for compatibility with older compilers
define(STDVER = "c++0x")

