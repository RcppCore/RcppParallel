if (getRversion() < "3.4.0") {
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

define(STDVER = "c++11")
