# Build and load a translation unit exercising the parts of the TBB API that
# downstream packages depend on, using only the flags RcppParallel advertises.
#
# StanHeaders -- and so rstan -- needs both of the pieces used here:
# tbb::this_task_arena::isolate, to keep its thread-local AD tape from being
# modified by a task from another arena, and tbb::task_scheduler_observer, to
# install that tape on each worker. Rtools42's TBB 2017 provides neither in a
# usable form, which is what broke rstan on R 4.2 (isolate is gated behind
# TBB_PREVIEW_TASK_ISOLATION, and isolate_within_arena isn't in the library at
# all), so this stands in for a full rstan build.

code <- '
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/task_arena.h>
#include <tbb/task_scheduler_observer.h>

#include <atomic>
#include <cstddef>

// R.h remaps names like \'length\' onto Rf_ equivalents by default, which
// collides with the standard library; keep it last, and unremapped
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

namespace {

// mirrors StanHeaders\' ad_tape_observer, which is what pulls the
// task_scheduler_observer entry points into the link
struct observer : public tbb::task_scheduler_observer {
   observer() : tbb::task_scheduler_observer() { observe(true); }
   void on_scheduler_entry(bool) override {}
   void on_scheduler_exit(bool) override {}
};

} // end anonymous namespace

extern "C" SEXP tbb_downstream_check(void) {

   observer obs;
   std::atomic<int> total(0);

   // mirrors StanHeaders\' use of task isolation in reduce_sum / map_rect
   tbb::this_task_arena::isolate([&] {
      tbb::parallel_for(
         tbb::blocked_range<std::size_t>(0, 1024),
         [&](const tbb::blocked_range<std::size_t>& range) {
            total += static_cast<int>(range.end() - range.begin());
         }
      );
   });

   return Rf_ScalarInteger(total.load());

}
'

# report how RcppParallel is configured, so a failure here can be read
# against the provenance logged during installation
writeLines(c(
   sprintf("TBB_ENABLED : %s", RcppParallel:::TBB_ENABLED),
   sprintf("TBB_LIB     : '%s'", RcppParallel:::TBB_LIB),
   sprintf("TBB_INC     : '%s'", RcppParallel:::TBB_INC),
   sprintf("CxxFlags()  : %s", RcppParallel:::tbbCxxFlags()),
   sprintf("LdFlags()   : %s", RcppParallel:::tbbLdFlags())
))

if (!RcppParallel:::TBB_ENABLED)
   stop("RcppParallel was installed without a tbb backend")

# mirror rstan's src/Makevars.win, which takes all of its TBB configuration
# from RcppParallel: its compiler flags via CxxFlags(), its linker flags via
# RcppParallelLibs(), and the include path itself via 'LinkingTo'
makevars <- c(
   "CXX_STD = CXX17",
   sprintf("PKG_CPPFLAGS = -I\"%s\"", system.file("include", package = "RcppParallel")),
   "PKG_CPPFLAGS += $(shell \"${R_HOME}/bin/Rscript\" -e \"RcppParallel::CxxFlags()\" | tail -n 1)",
   "PKG_LIBS += $(shell \"${R_HOME}/bin${R_ARCH_BIN}/Rscript\" -e \"RcppParallel::RcppParallelLibs()\" | tail -n 1)"
)

dir <- tempfile("tbb-downstream-")
dir.create(dir, recursive = TRUE)
owd <- setwd(dir)
on.exit(setwd(owd), add = TRUE)

writeLines(code, "check.cpp")

# deliberately not named 'Makevars': R CMD SHLIB reads a Makevars in the
# working directory as well as R_MAKEVARS_USER, and would apply both. going
# through R_MAKEVARS_USER also keeps any personal ~/.R/Makevars out of the way
writeLines(makevars, "makevars-downstream")
Sys.setenv(R_MAKEVARS_USER = file.path(dir, "makevars-downstream"))
status <- system(paste(shQuote(file.path(R.home("bin"), "R")), "CMD SHLIB check.cpp"))
if (status != 0L)
   stop("downstream translation unit failed to build")

# loading also proves any load-time dependency on the tbb stub resolves
dll <- dyn.load(paste0("check", .Platform$dynlib.ext))
on.exit(dyn.unload(dll[["path"]]), add = TRUE)

result <- .Call("tbb_downstream_check")
if (!identical(result, 1024L))
   stop("downstream check returned ", result, "; expected 1024")

writeLines("** downstream TBB check passed")
