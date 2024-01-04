
is_windows <- function() {
   .Platform$OS.type == "windows"
}

is_mac <- function() {
   Sys.info()[["sysname"]] == "Darwin"
}

is_unix <- function() {
   .Platform$OS.type == "unix"
}

is_solaris <- function() {
   Sys.info()[["sysname"]] == "SunOS"
}

is_sparc <- function() {
   info <- Sys.info()
   all(
      info[["sysname"]] == "SunOS",
      info[["machine"]] != "i86pc"
   )
}


