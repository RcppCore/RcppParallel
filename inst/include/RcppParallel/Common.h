#ifndef __RCPP_PARALLEL_COMMON__
#define __RCPP_PARALLEL_COMMON__

#include <cerrno>
#include <cstddef>
#include <cstdlib>

namespace RcppParallel {

template <typename T, typename U>
inline int resolveValue(const char* envvar,
                        T requestedValue,
                        U defaultValue)
{
   // if the requested value is non-zero and not the default, we can use it
   if (requestedValue != defaultValue && requestedValue > 0)
      return requestedValue;
   
   // otherwise, try reading the default from associated envvar
   // if the environment variable is unset, use the default
   const char* var = getenv(envvar);
   if (var == NULL)
      return defaultValue;
   
   // try to convert the string to a number
   // if an error occurs during conversion, just use default
   errno = 0;
   char* end;
   long value = strtol(var, &end, 10);
   
   // check for conversion failure
   if (end == var || *end != '\0' || errno == ERANGE)
      return defaultValue;
   
   // okay, return the parsed environment variable value   
   return value;
}

// Work executed within a background thread. We implement dynamic
// dispatch using vtables so we can have a stable type to cast
// to from the void* passed to the worker thread (required because
// the tinythreads interface allows to pass only a void* to the
// thread main rather than a generic type / template)

struct Worker 
{  
   // construct and destruct (delete virtually)
   Worker() {}
   virtual ~Worker() {}
   
   // dispatch work over a range of values
   virtual void operator()(std::size_t begin, std::size_t end) = 0;   
   
   // disable copying and assignment
private:
   Worker(const Worker&);
   void operator=(const Worker&);
};

// Tag type used for disambiguating splitting constructors

struct Split {};

} // namespace RcppParallel


#endif // __RCPP_PARALLEL_COMMON__
