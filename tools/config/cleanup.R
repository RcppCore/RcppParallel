# utils.R ----

#' Configure a File
#'
#' Configure a file, replacing any instances of `@`-delimited variables, e.g.
#' `@VAR@`, with the value of the variable called `VAR` in the associated
#' `config` environment.
#'
#' @param source The file to be configured.
#' @param target The file to be generated.
#' @param config The configuration environment.
#' @param verbose Boolean; report files as they are configured?
#'
#' @export
configure_file <- function(
    source,
    target = sub("[.]in$", "", source),
    config = NULL,
    verbose = getOption("configure.verbose", TRUE))
{
    contents <- readLines(source, warn = FALSE)
    enumerate(config, function(key, val) {
        needle <- paste("@", key, "@", sep = "")
        replacement <- val
        contents <<- gsub(needle, replacement, contents)
    })

    ensure_directory(dirname(target))
    writeLines(contents, con = target)

    if (isTRUE(verbose)) {
        fmt <- "** configured file: '%s' => '%s'"
        message(sprintf(fmt, source, target))
    }
}

#' Read R Configuration for a Package
#'
#' Read the \R configuration, as through `R CMD config --all`.
#'
#' @param package The path to an \R package's sources.
#' @param values The \R configuration values to read (as a character vector).
#'   If `NULL` (the default), all values are read (as through `R CMD config --all`).
#' @param verbose Boolean; notify the user as \R configuration is read?
#'
#' @export
read_config <- function(
    package = ".",
    values  = NULL,
    verbose = getOption("configure.verbose", TRUE))
{
    # move to requested directory
    owd <- setwd(package)
    on.exit(setwd(owd), add = TRUE)
    R <- file.path(R.home("bin"), "R")

    if (is.null(values)) {
        if (verbose)
            message("** executing 'R CMD config --all'")
        output <- system2(R, c("CMD", "config", "--all"), stdout = TRUE)
        equalsIndex <- regexpr("=", output, fixed = TRUE)
        keys <- trim_whitespace(substring(output, 1, equalsIndex - 1))
        config <- as.list(trim_whitespace(substring(output, equalsIndex + 1)))
        names(config) <- keys

    } else {
        if (verbose)
            message("** executing 'R CMD config'")
        config <- lapply(values, function(value) {
            system2(R, c("CMD", "config", value), stdout = TRUE)
        })
        names(config) <- values
    }

    list2env(config, parent = globalenv())
}

#' Concatenate the Contents of a Set of Files
#'
#' Given a set of files, concatenate their contents into
#' a single file.
#'
#' @param sources An \R list of files
#' @param target The file to use for generation.
#' @param headers Headers to be used for each file copied.
#'
#' @export
concatenate_files <- function(
    sources,
    target,
    headers = sprintf("# %s ----", basename(sources)))
{
    pieces <- vapply(seq_along(sources), function(i) {
        source <- sources[[i]]
        header <- headers[[i]]
        contents <- trim_whitespace(read_file(source))
        paste(header, contents, "", sep = "\n\n")
    }, character(1))

    ensure_directory(dirname(target))
    writeLines(pieces, con = target)
}

ensure_directory <- function(dir) {
    info <- file.info(dir)

    # no file exists at this location; try to make it
    if (is.na(info$isdir)) {
        dir.create(info$isdir, recursive = TRUE, showWarnings = FALSE)
        if (!file.exists(dir))
            stop("failed to create directory '", dir, "'")
        return(TRUE)
    }

    # a directory already exists
    if (isTRUE(info$isdir))
        return(TRUE)

    # a file exists, but it's not a directory
    stop("file already exists at path '", dir, "'")
}

enumerate <- function(x, f, ...) {
    nms <- if (is.environment(x)) ls(envir = x) else names(x)
    lapply(nms, function(nm) {
        f(nm, x[[nm]], ...)
    })
}

read_file <- function(path) {
    paste(readLines(path, warn = FALSE), collapse = "\n")
}

remove_file <- function(
    path,
    verbose = getOption("configure.verbose", TRUE))
{
    info <- file.info(path)
    if (!is.na(info$isdir)) {
        unlink(path, recursive = isTRUE(info$isdir))
        if (verbose) {
            fmt <- "** removed file '%s'"
            message(sprintf(fmt, path))
        }
    }

    TRUE
}

trim_whitespace <- function(x) {
    gsub("^[[:space:]]*|[[:space:]]*$", "", x)
}


# run-cleanup.R ----

# figure out the current package's name
DESCRIPTION <- read.dcf("DESCRIPTION", all = TRUE)
fmt <- "* configuring package '%s' ..."
message(sprintf(fmt, DESCRIPTION$Package))

# overlay user configuration
envir <- new.env(parent = globalenv())
files <- list.files("tools/config/cleanup", pattern = "[.][rR]$", full.names = TRUE)
for (file in files) {
    fmt <- "** sourcing '%s'"
    message(sprintf(fmt, file))
    source(file, local = envir)
}

# apply cleanup script (if any)
if (exists("cleanup", envir = envir, inherits = FALSE)) {
    cleanup <- get("cleanup", envir = envir, inherits = FALSE)
    message("** executing user-defined cleanup script")
    cleanup()
}

fmt <- "* successfully cleaned package '%s'"
message(sprintf(fmt, DESCRIPTION$Package))


