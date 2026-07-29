# Report how the installed RcppParallel resolved TBB, so that a downstream
# build failure can be read against the configuration that produced it.
#
# This lives in a file rather than inline in the workflow: 'Rscript -e' only
# receives the first line of a multi-line argument on Windows, so the rest of
# the expression is silently dropped and R fails to parse what it did get.

writeLines(c(
   sprintf("TBB_ENABLED : %s", RcppParallel:::TBB_ENABLED),
   sprintf("TBB_LIB     : '%s'", RcppParallel:::TBB_LIB),
   sprintf("TBB_INC     : '%s'", RcppParallel:::TBB_INC),
   sprintf("CxxFlags()  : %s", RcppParallel:::tbbCxxFlags()),
   sprintf("LdFlags()   : %s", RcppParallel:::tbbLdFlags())
))
