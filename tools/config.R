# configure-database.R ----

#' Retrieve the Global Configuration Database
#'
#' Retrieve the global configuration database (as an \R environment).
#'
#' @family configure-db
#'
#' @export
configure_database <- local({
    database <- new.env(parent = emptyenv())
    function() database
})

#' Define Variables for the Configuration Database
#'
#' Define variables to be used as part of the default configuration database.
#' These will be used by [configure_file()] when no configuration database
#' is explicitly supplied.
#'
#' @param ... A set of named arguments, mapping configuration names to values.
#'
#' @family configure-db
#'
#' @export
configure_define <- function(...) {
    envir <- configure_database()
    list2env(list(...), envir = envir)
}

#' @export
define <- configure_define


# utils.R ----

#' Configure a File
#'
#' Configure a file, replacing any instances of `@`-delimited variables, e.g.
#' `@VAR@`, with the value of the variable called `VAR` in the associated
#' `config` environment.
#'
#' @param source The file to be configured.
#' @param target The file to be generated.
#' @param config The configuration database.
#' @param verbose Boolean; report files as they are configured?
#'
#' @family configure
#'
#' @export
configure_file <- function(
    source,
    target = sub("[.]in$", "", source),
    config = configure_database(),
    verbose = configure_verbose())
{
    contents <- readLines(source, warn = FALSE)
    enumerate(config, function(key, val) {
        needle <- paste("@", key, "@", sep = "")
        replacement <- val
        contents <<- gsub(needle, replacement, contents)
    })

    ensure_directory(dirname(target))
    writeLines(contents, con = target)

    info <- file.info(source)
    Sys.chmod(target, mode = info$mode)

    if (isTRUE(verbose)) {
        fmt <- "** configured file: '%s' => '%s'"
        message(sprintf(fmt, source, target))
    }
}

#' Configure Files in a Directory
#'
#' This companion function to [configure_file()] can be used to
#' configure all `.in` files within a directory.
#'
#' @param path The path to a directory in which files should be configured.
#' @param config The configuration database to be used.
#' @param verbose Boolean; report files as they are configured?
#'
#' @family configure
#'
#' @export
configure_directory <- function(
    path = ".",
    config = configure_database(),
    verbose = configure_verbose())
{
    files <- list.files(
        path = path,
        pattern = "[.]in$",
        full.names = TRUE)

    lapply(files, configure_file, config = config, verbose = verbose)
}

configure_auto <- function(type) {
    configure_common(type = type)
}

configure_common <- function(type) {

    if (!isTRUE(getOption("configure.common", default = TRUE)))
        return(invisible(FALSE))

    sources <- list.files(
        path = c("R", "src"),
        pattern = "[.]in$",
        full.names = TRUE
    )

    sources <- sub("[.]/", "", sources)

    if (type == "configure") {
        lapply(sources, configure_file)
    } else if (type == "cleanup") {
        targets <- sub("[.]in$", "", sources)
        lapply(targets, remove_file)
    }

    invisible(TRUE)
}

#' Read R Configuration for a Package
#'
#' Read the \R configuration, as through `R CMD config`.
#'
#' @param ... The \R configuration values to read (as a character vector).
#'   If empty, all values are read as through `R CMD config --all`).
#' @param package The path to the \R package's sources.
#' @param envir The environment in which the configuration information should
#'   be assigned. By default, the [configure_database()] is populated with the
#'   requested values.
#' @param verbose Boolean; notify the user as \R configuration is read?
#'
#' @export
read_r_config <- function(
    ...,
    package = Sys.getenv("R_PACKAGE_DIR", unset = "."),
    envir = configure_database(),
    verbose = configure_verbose())
{
    # move to requested directory
    owd <- setwd(package)
    on.exit(setwd(owd), add = TRUE)
    R <- file.path(R.home("bin"), "R")

    # suppress cygwin path warnings for windows
    if (Sys.info()[["sysname"]] == "Windows") {
        CYGWIN <- Sys.getenv("CYGWIN")
        Sys.setenv(CYGWIN = "nodosfilewarning")
        on.exit(Sys.setenv(CYGWIN = CYGWIN), add = TRUE)
    }

    values <- unlist(list(...), recursive = TRUE)
    if (length(values) == 0) {
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

    if (is.null(envir))
        return(config)

    list2env(config, envir = envir)
}

#' Concatenate the Contents of a Set of Files
#'
#' Given a set of files, concatenate their contents into
#' a single file.
#'
#' @param sources An \R list of files
#' @param target The file to use for generation.
#' @param headers Headers to be used for each file copied.
#' @param preamble Text to be included at the beginning of the document.
#' @param postamble Text to be included at the end of the document.
#' @param verbose Boolean; inform the user when the requested file is created?
#'
#' @export
concatenate_files <- function(
    sources,
    target,
    headers = sprintf("# %s ----", basename(sources)),
    preamble = NULL,
    postamble = NULL,
    verbose = configure_verbose())
{
    pieces <- vapply(seq_along(sources), function(i) {
        source <- sources[[i]]
        header <- headers[[i]]
        contents <- trim_whitespace(read_file(source))
        paste(header, contents, "", sep = "\n\n")
    }, character(1))

    all <- c(preamble, pieces, postamble)

    ensure_directory(dirname(target))
    writeLines(all, con = target)

    if (verbose) {
        fmt <- "** created file '%s'"
        message(sprintf(fmt, target))
    }

    TRUE
}

#' Add Configure Infrastructure to an R Package
#'
#' Add the infrastructure needed to configure an R package.
#'
#' @param package The path to the top-level directory of an \R package.
#' @export
use_configure <- function(package = ".") {

    # preserve working directory
    owd <- getwd()
    on.exit(setwd(owd), add = TRUE)

    # find resources
    package <- normalizePath(package, winslash = "/")
    resources <- system.file("resources", package = "configure")

    # copy into temporary directory
    dir <- tempfile("configure-")
    on.exit(unlink(dir, recursive = TRUE), add = TRUE)

    dir.create(dir)
    file.copy(resources, dir, recursive = TRUE)

    # rename resources directory
    setwd(dir)
    file.rename(basename(resources), basename(package))

    # now, copy these files back into the target directory
    file.copy(basename(package), dirname(package), recursive = TRUE)

    # ensure DESCRIPTION contains 'Biarch: TRUE' for Windows
    setwd(package)
    DESCRIPTION <- read_file("DESCRIPTION")
    if (!grepl("(?:^|\n)Biarch:", DESCRIPTION)) {
        DESCRIPTION <- paste(DESCRIPTION, "Biarch: TRUE", sep = "\n")
        DESCRIPTION <- gsub("\n{2,}", "\n", DESCRIPTION)
        cat(DESCRIPTION, file = "DESCRIPTION", sep = "\n")
    }
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
    verbose = configure_verbose())
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

source_file <- function(
    path,
    envir = parent.frame())
{
    contents <- read_file(path)
    invisible(eval(parse(text = contents), envir = envir))
}

trim_whitespace <- function(x) {
    gsub("^[[:space:]]*|[[:space:]]*$", "", x)
}

configure_verbose <- function() {
    getOption("configure.verbose", !interactive())
}


# run.R ----

local({

    # extract path to install script
    args <- commandArgs(TRUE)
    type <- args[[1]]

    # report start of execution
    package <- Sys.getenv("R_PACKAGE_NAME", unset = "<unknown>")
    fmt <- "* preparing to %s package '%s' ..."
    message(sprintf(fmt, type, package))

    # execute the requested script
    path <- sprintf("tools/config/%s.R", type)
    if (file.exists(path)) source_file(path)

    # perform automatic configuration
    configure_auto(type = type)

    # report end of execution
    fmt <- "* finished %s for package '%s'"
    message(sprintf(fmt, type, package))
})


