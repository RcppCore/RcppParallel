
# Clean up files generated during configuration here.
# Use 'remove_file()' to remove files generated during configuration.

# unlink("src/tbb/build", recursive = TRUE)
# unlink("src/tbb/build-tbb", recursive = TRUE)
unlink("inst/lib",  recursive = TRUE)
unlink("inst/libs", recursive = TRUE)
unlink("inst/include/index.html", recursive = TRUE)
unlink("inst/include/oneapi", recursive = TRUE)
unlink("inst/include/serial", recursive = TRUE)
unlink("inst/include/tbb", recursive = TRUE)

