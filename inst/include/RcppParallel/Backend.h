
#ifndef __RCPP_PARALLEL_BACKEND__
#define __RCPP_PARALLEL_BACKEND__

#include <cstdlib>
#include <cstring>

extern "C" {
void REprintf(const char*, ...);
}

namespace RcppParallel {
namespace internal {

enum backend_type {
   BACKEND_TBB,
   BACKEND_TINYTHREAD
};

#if RCPP_PARALLEL_USE_TBB

inline backend_type defaultBackend()
{
   return BACKEND_TBB;
}

#else

inline backend_type defaultBackend()
{
   return BACKEND_TINYTHREAD;
}

#endif

inline const char* backendToString(backend_type backend)
{
   switch (backend)
   {
   case BACKEND_TBB:
      return "tbb";
   case BACKEND_TINYTHREAD:
      return "tinythread";
   }

   // shouldn't be reached but need to silence compiler warnings
   return "tbb";
}

inline backend_type backend()
{
   const char* requestedBackend = std::getenv("RCPP_PARALLEL_BACKEND");
   if (requestedBackend == NULL)
   {
      return defaultBackend();
   }
   else if (std::strcmp(requestedBackend, "tbb") == 0)
   {
#if RCPP_PARALLEL_USE_TBB
      return BACKEND_TBB;
#else
      const char* msg =
         "tbb backend is not available; using tinythread instead";
      
      REprintf("%s\n", msg);
      return BACKEND_TINYTHREAD;
#endif
   }
   else if (strcmp(requestedBackend, "tinythread") == 0)
   {
      return BACKEND_TINYTHREAD;
   }
   else
   {
      const char* fmt = "unknown parallel backend '%s'; using '%s' instead\n";
      REprintf(fmt, requestedBackend, backendToString(defaultBackend()));
      return defaultBackend();
   }
}

} // namespace internal
} // namespace RcppParallel

#endif /* __RCPP_PARALLEL_BACKEND__ */
