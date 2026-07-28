
# Clean up files generated during configuration here.
# Use 'remove_file()' to remove files generated during configuration.

# NOTE: stale artifacts in src/tbb/build can otherwise be swept into the
# installed package; the bundled TBB is rebuilt from scratch on each
# install, so nothing is lost by removing these
unlink("src/tbb/build", recursive = TRUE)
unlink("src/tbb/build-tbb", recursive = TRUE)
unlink("inst/lib",  recursive = TRUE)
unlink("inst/libs", recursive = TRUE)
unlink("inst/include/index.html", recursive = TRUE)
unlink("inst/include/oneapi", recursive = TRUE)
unlink("inst/include/serial", recursive = TRUE)
unlink("inst/include/tbb", recursive = TRUE)

