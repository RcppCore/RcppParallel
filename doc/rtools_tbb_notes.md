# Differences MinGW / Rtools

## cmd

### MinGW

cmd is an sh wrapper which invokes the 32bit version of Windows' shell:

	$ where cmd
	C:\MinGW\msys\1.0\bin\cmd
	c:\Windows\System32\cmd.exe
	$ cat /c/MinGW/msys/1.0/bin/cmd
	#!/bin/sh
	# Copyright (C) 2002, Earnie Boyd
	#   mailto:earnie@users.sf.net
	# This file is part of Minimal SYStem.
	#   http://www.mingw.org/msys.shtml
	# File: cmd

	"$COMSPEC" "$@"
	$ echo $COMSPEC
	C:\windows\SysWOW64\cmd.exe
	
### Rtools

No wrapper; cmd is the default Windows shell (64bit on a 64bit OS):

	$ where cmd
	C:\Windows\System32\cmd.exe
	

## paths

### MinGW

- 3 styles supported: `/drive/path`, `drive:/path`, `drive:\path` (properly escaped).
- The *actual* path (returned when querying) is `/drive/path`.


		$ cd f:/tmp/testpath
		$ pwd
		/f/tmp/testpath
		$ cd f:\\tmp\\testpath
		$ pwd
		/f/tmp/testpath
		$ cd /f/tmp/testpath
		$ pwd
		/f/tmp/testpath	
	
### Rtools

- 3 styles supported: `/cygdrive/drive/path`, `drive:/path`, `drive:\path` (properly escaped).
- The *actual* path (returned when querying) is `/cygdrive/drive/path`.
- `/drive/path` is **not** supported.

		$ cd f:/tmp/testpath
		$ pwd
		/cygdrive/f/tmp/testpath
		$ cd f:\\tmp\\testpath
		$ pwd
		/cygdrive/f/tmp/testpath
		$ cd /f/tmp/testpath
		cd: can't cd to /f/tmp/testpath
		$ cd /cygdrive/f/tmp/testpath
		$ pwd
		/cygdrive/f/tmp/testpath
		

## parameters

### MinGW

Shell will sometimes automatically replace parameters starting with forward slashes using the rules described [here](http://www.mingw.org/wiki/Posix_path_conversion). 
Since forward slashes are often used to mark option parameters in Windows command line applications (/o is the Windows equivalent of -o and --option for Unix), this can cause very subtle and hard to debug issues. The fix is to double the forward slashes, or to quote (when possible)

	$ ls /d
	$RECYCLE.BIN  System Volume Information  pagefile.sys

	$ cmd /c "echo hi"
	hi

	$ cmd /C "echo hi"
	Microsoft Windows [Version 6.3.9600]
	(c) 2013 Microsoft Corporation. All rights reserved.

	f:\tmp\testpath>exit

	$ cmd /C "echo hi /runtime"
	'untime"' is not recognized as an internal or external command,
	operable program or batch file.
	
	$ cmd //C "echo hi /runtime"
	hi /runtime


### Rtools

No parameter replacements. What you type is what you get.

	$ ls /d
	ls: cannot access /d: No such file or directory
	$ cmd /c "echo hi"
	hi
	$ cmd /C "echo hi"
	hi
	$ cmd /C "echo hi /runtime"
	hi /runtime


## uname

Only present in MinGW

## g++

### MinGW

default full paths supported

	$ g++ /f/tmp/testpath/test.cpp
	$ echo $?
	0

### Rtools

default full paths are not supported

	$ ls /cygdrive/f/tmp/testpath/test.cpp
	/cygdrive/f/tmp/testpath/test.cpp
	$ cat /cygdrive/f/tmp/testpath/test.cpp
	int main() {return 0;}	
	$ g++ /cygdrive/f/tmp/testpath/test.cpp
	g++.exe: error: /cygdrive/f/tmp/testpath/test.cpp: No such file or directory
	g++.exe: fatal error: no input files
	compilation terminated.

This means that great care must be taken to ensure paths are never queried and instead always manually constructed. Examples of queried paths that end up being g++ incompatible in the context of a Makefile:

- don't use `$(shell pwd)`
- don't use `$(CURDIR)`
- only use **relative paths** in `VPATH`
		

		$ cat Makefile
		.PHONY: all
		all: test.o foo.o
			@echo DIR=$(CURDIR)

		%.o: %.cpp
			@echo $<

		$  make VPATH=f:/tmp/testpath/subdir
		test.cpp
		/cygdrive/f/tmp/testpath/subdir/foo.cpp
		DIR=/cygdrive/f/tmp/testpath
		
		$ make VPATH=subdir
		test.cpp
		subdir/foo.cpp
		DIR=/cygdrive/f/tmp/testpath
		
# Bugs and tips

## Modal dialog asking to insert disk in drive

This bug is in MinGW only (not Rtools). This is due to hard-coded paths pointing to I: drive in g++

	$ strings c:/MinGW/bin/g++.exe | grep i: | grep mingw
	i:/p/giaw/mingw/share/locale
	i:/p/giaw/mingw/share/locale
	
If no I: drive exists, or the path does not exist, then g++ silently ignores it. *However*, if I: happens to point to a removable drive, then you get a modal dialog.

Fix: go in "Disk Management" and rename the drive.

## Full paths

g++ is not the only tool affected by full paths in the context of Rtools. Since Rtools doesn't perform any auto-conversion and `/` is used as a option marker for many Windows command line applications, 
some of them end up being confused. For example:

	$ cat test.js
	WScript.Echo( "Hi" );
	$ cscript /nologo test.js
	Hi
	$ pwd
	/cygdrive/f/tmp/testpath
	$ cscript /nologo /cygdrive/f/tmp/testpath/test.js
	Input Error: Unknown option "/cygdrive/f/tmp/testpath/test.js" specified.
	$ cscript /nologo f:/tmp/testpath/test.js
	Hi
	$

Recommendation is to always use relative paths.

## Changing the shell in make

The `.SHELLFLAGS` variable doesn't work in the context of Rtools (silently ignored), making it impossible to change default shell to cmd: the default for SHELLFLAGS is `-c`, which is suitable for `sh` and not `cmd`:


	$ cmd /c dir /b notfound
	File Not Found
	$ cmd -c dir /b notfound
	Microsoft Windows [Version 6.3.9600]
	(c) 2013 Microsoft Corporation. All rights reserved.

	F:\tmp\testpath>exit

	$ cat Makefile
	SHELL=cmd
	.SHELLFLAGS=/c
	TEST=$(shell dir /b notfound)

	.PHONY: all
	all:
        @echo hi

	$ make
	Microsoft Windows [Version 6.3.9600]
	(c) 2013 Microsoft Corporation. All rights reserved.

	F:\tmp\testpath>exit
	

The Rtools-only `--win32` command line option for make didn't properly work for me (but I was dealing with complex Makefiles).

## Hangs in make

There does not appear to be a built-in tracing or time-out mechanism in make regarding sub-processes. One effective way to figure out what's hanging is "Task Manager", "Details", then add column "Command Line".
In my case, most hangs were due to some variation of `cmd -c something` or `cmd c: something` (both variations end up leaving cmd.exe running) instead of `cmd /c something`. The first one is due to SHELLFLAGS not working, the second to auto param replacement.

## Rule not found errors

i.e. "no rule to make target" errors.  
In some cases, the `VPATH` parser gets confused, and then **all** paths specified are *silently* ignored. This can even happen for simple (no spaces, etc.), valid (exist) paths.

	$ cat Makefile
	.PHONY: all
	all: test.o foo.o
		@echo hi

	%.o: %.cpp
		@echo $<
	$ pwd
	/cygdrive/f/tmp/testpath
	$ make "VPATH=f:/tmp/testpath/subdir"
	test.cpp
	/cygdrive/f/tmp/testpath/subdir/foo.cpp
	hi
	$ make "VPATH=f:/tmp/testpath subdir"
	test.cpp
	subdir/foo.cpp
	hi
	$ make "VPATH=subdir f:/tmp/testpath"
	test.cpp
	subdir/foo.cpp
	hi
	$ make "VPATH=f:/tmp/testpath f:/tmp/testpath/subdir"
	test.cpp
	make: *** No rule to make target `foo.o', needed by `all'.  Stop.


### Incorrect rule firing

These can be caused by the previous issue: VPATH not working, therefore target file not found, therefore other rule firing.

This can also be caused by MinGW and RTools using a different version of make. A quick way to test it is to manually/explicitly create the rule, and see if it is firing. 



