configure <- function() {
   
   if (getRversion() < "3.4.0") {
      config <- list(
         CC            = "$(CC)",
         CXX11         = "$(CXX1X)",
         CXX11STD      = "$(CXX1XSTD)",
         CXX11PICFLAGS = "$(CXX1XPICFLAGS)"
      )
   } else {
      config <- list(
         CC            = "$(CC)",
         CXX11         = "$(CXX11)",
         CXX11STD      = "$(CXX11STD)",
         CXX11PICFLAGS = "$(CXX11PICFLAGS)"
      )
   }
   
   config$STDVER <- "c++11"
   if (Sys.info()[["sysname"]] == "Windows") {
      configure_file("src/Makevars.in", "src/Makevars.win", config = config)
   } else {
      configure_file("src/Makevars.in", "src/Makevars", config = config)
   }
   
   config
}
