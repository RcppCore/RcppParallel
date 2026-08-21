tbb_cxx_compiler <- function() {

   compiler <- Sys.getenv("CXX", unset = NA_character_)
   if (!is.na(compiler) && nzchar(compiler))
      return(compiler)

   R <- file.path(R.home("bin"), "R")
   output <- tryCatch(
      system2(R, c("CMD", "config", "CXX"), stdout = TRUE, stderr = FALSE),
      error = function(cnd) character()
   )

   if (length(output)) output[[1L]] else ""

}

tbb_needs_no_aligned_allocation <- function(
   sysname = Sys.info()[["sysname"]],
   release = Sys.info()[["release"]],
   compiler = tbb_cxx_compiler())
{

   if (!identical(sysname, "Darwin"))
      return(FALSE)

   # Darwin 16 is macOS 10.12; Darwin 17 is macOS 10.13.
   darwinMajor <- suppressWarnings(as.integer(strsplit(release, ".", fixed = TRUE)[[1L]][[1L]]))
   if (is.na(darwinMajor) || darwinMajor >= 17L)
      return(FALSE)

   compiler <- strsplit(compiler, "[[:space:]]+", perl = TRUE)[[1L]][[1L]]
   identical(basename(compiler), "clang++")

}
