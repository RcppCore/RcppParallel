# Copyright (c) 2005-2019 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifdef tbb_build_dir
  test_dir:=$(tbb_build_dir)
else
  test_dir:=.
endif

ifndef rtools
  export SHELL = cmd
  CMD:=cmd /C
  SLASH=\\
  RM=cmd /C del /Q /F
  RD=cmd /C rmdir
  MD=cmd /c mkdir
  NUL= nul
else
  ifneq ($(COMSPEC), )
    # Use comspec env var if present
    # Since it represents a full path, quote in case there are some spaces.
    CMD:="$(subst \,/,$(COMSPEC))" /C
  else
    # otherwise rely on cmd being in the path
    CMD:=cmd /C
  endif
  export SHELL = sh.exe
  SLASH=/
  RD=rmdir
  MD=mkdir
  RM=rm
  NUL= /dev/null
endif

# A convenience wrapper for calls to detect.js.
# $(1) is the full command line for the script, e.g. /minversion icl 12
detect_js = $(shell $(CMD) "cscript //NoLogo //E:jscript $(tbb_root)/build/detect.js $(1)")

# TODO give an error if archs doesn't match
ifndef arch
  export arch:=$(call detect_js, /arch $(compiler))
endif

ifndef runtime
  export runtime:=$(call detect_js, /runtime $(compiler))
endif

native_compiler := cl
export compiler ?= cl
debugger ?= devenv /debugexe

CWD=$(shell $(CMD) echo %CD%)

AR=lib
AR_OUTPUT_KEY=/out:
AR_FLAGS=/nologo /nodefaultlib

OBJ = obj
DLL = dll
LIBEXT = lib
ASMEXT = asm

def_prefix = $(if $(findstring intel64,$(arch)),win64,win32)

# Target Windows version. Do not increase beyond 0x0502 without prior discussion!
# Used as the value for macro definition option in windows.cl.inc etc.
# For tests, we need at least Windows XP SP2 for sake of enabling stack backtraces.
_WIN32_WINNT=0x0502

TBB.LST = $(tbb_root)/src/tbb/$(def_prefix)-tbb-export.lst
TBB.DEF = $(TBB.LST:.lst=.def)
TBB.DLL = tbb$(CPF_SUFFIX)$(DEBUG_SUFFIX).$(DLL)
TBB.LIB = tbb$(CPF_SUFFIX)$(DEBUG_SUFFIX).$(LIBEXT)
TBB.RES = tbb_resource.res
# On Windows, we use #pragma comment to set the proper TBB lib to link with.
# But for cross-configuration testing, need to link explicitly.
# Tests use this variable to detect dependency on TBB binary, so have to be non-empty. 
LINK_TBB.LIB = $(if $(crosstest),$(TBB.LIB),$(DEFINE_KEY)__TBB_IMPLICITLY_LINKED)
TBB.MANIFEST =
ifneq ($(filter vc8 vc9,$(runtime)),)
    TBB.MANIFEST = tbbmanifest.exe.manifest
endif

MALLOC.DEF = $(MALLOC_ROOT)/$(def_prefix)-tbbmalloc-export.def
MALLOC.DLL = tbbmalloc$(DEBUG_SUFFIX).$(DLL)
MALLOC.LIB = tbbmalloc$(DEBUG_SUFFIX).$(LIBEXT)
MALLOC.RES = tbbmalloc.res
MALLOC.MANIFEST =
ifneq ($(filter vc8 vc9,$(runtime)),)
MALLOC.MANIFEST = tbbmanifest.exe.manifest
endif
LINK_MALLOC.LIB = $(MALLOC.LIB)

MALLOCPROXY.DLL = tbbmalloc_proxy$(DEBUG_SUFFIX).$(DLL)
MALLOCPROXY.LIB = tbbmalloc_proxy$(DEBUG_SUFFIX).$(LIBEXT)
LINK_MALLOCPROXY.LIB = $(MALLOCPROXY.LIB)

PROXY.LIB = tbbproxy$(DEBUG_SUFFIX).$(LIBEXT)

RML.DEF = $(RML_SERVER_ROOT)/$(def_prefix)-rml-export.def
RML.DLL = irml$(DEBUG_SUFFIX).$(DLL)
RML.LIB = irml$(DEBUG_SUFFIX).$(LIBEXT)
RML.RES = irml.res
ifneq ($(filter vc8 vc9,$(runtime)),)
RML.MANIFEST = tbbmanifest.exe.manifest
endif

MAKE_VERSIONS = $(CMD) cscript //NoLogo //E:JScript         \
  "$(subst \,/,$(tbb_root)/build/version_info_windows.js)"  \
  "$(subst \,/,$(CONLY))"                                   \
  "$(arch)"                                                 \
  "$(subst \,/,$(VERSION_FLAGS))"                           \
  > version_string.ver

MAKE_TBBVARS = $(CMD) "$(subst /,\,$(tbb_root)/build/generate_tbbvars.bat)"

TEST_LAUNCHER = $(subst /,\,$(tbb_root))\build\test_launcher.bat $(largs)

OPENCL.LIB = OpenCL.$(LIBEXT)
