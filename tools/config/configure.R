if (Sys.info()[["sysname"]] == "Windows" && getRversion() < "3.1.0") {
   define(
      CC            = "$(CC)",
      CXX11         = "$(CXX)",
      CXX11STD      = "-std=c++0x",
      CXX11PICFLAGS = "-fPIC"
   )
} else if (getRversion() < "3.4.0") {
   define(
      CC            = "$(CC)",
      CXX11         = "$(CXX1X)",
      CXX11STD      = "$(CXX1XSTD)",
      CXX11PICFLAGS = "$(CXX1XPICFLAGS)"
   )
} else {
   define(
      CC            = "$(CC)",
      CXX11         = "$(CXX11)",
      CXX11STD      = "$(CXX11STD)",
      CXX11PICFLAGS = "$(CXX11PICFLAGS)"
   )
}

# use c++0x for compatibility with older compilers
define(STDVER = "c++0x")

