
# Inline plugin used by sourceCpp.
inlineCxxPlugin <- function() {
   
   list(
      env = list(
         PKG_CXXFLAGS = tbbCxxFlags(),
         PKG_LIBS = tbbLdFlags()
      ),
      includes  = "#include <RcppParallel.h>",
      LinkingTo = "RcppParallel",
      body      = identity,
      Depends   = "RcppParallel"
   )
}
