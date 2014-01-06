

#include <R_ext/Rdynload.h>
#include <stdio.h>

#include <dlfcn.h>


extern "C" void R_init_tbb(DllInfo *dll) {
   
   
   void * handle = dlopen("/Library/Frameworks/R.framework/Versions/3.0/Resources/library/tbb/libs/libtbb.dylib",
         RTLD_GLOBAL);
   dlsym(handle, "__ZN3tbb8internal15runtime_warningEPKcz");
   
   //R_RegisterCCallable("tbb", 
   //                    "__ZN3tbb8internal15runtime_warningEPKcz", 
   //                    (DL_FUNC)dlsym(handle, "__ZN3tbb8internal15runtime_warningEPKcz"));
   
   
}