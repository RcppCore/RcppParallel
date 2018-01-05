AC_INIT([RcppParallel], 2018.1.0)

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  AC_MSG_ERROR([could not determine R_HOME])
fi

R_VERSION=`"${R_HOME}/bin/R" --vanilla --slave -e "cat(as.character(getRversion()))"`
AS_VERSION_COMPARE("${R_VERSION}", "3.4.0",
                   [USE_CXX11="no"],
                   [USE_CXX11="yes"],
                   [USE_CXX11="yes"])

if test "${USE_CXX11}" = "yes"
then
   AC_MSG_NOTICE([R >= 3.4.0 detected])
   CC=`"${R_HOME}/bin/R" CMD config CC`
   CXX11=`"${R_HOME}/bin/R" CMD config CXX11`
   CXX11STD=`"${R_HOME}/bin/R" CMD config CXX11STD`
   CXX11PICFLAGS=`"${R_HOME}/bin/R" CMD config CXX11PICFLAGS`
   STDVER=c++11
else
   AC_MSG_NOTICE([R < 3.4.0 detected])
   CC=`"${R_HOME}/bin/R" CMD config CC`
   CXX11=`"${R_HOME}/bin/R" CMD config CXX1X`
   CXX11STD=`"${R_HOME}/bin/R" CMD config CXX1XSTD`
   CXX11PICFLAGS=`"${R_HOME}/bin/R" CMD config CXX1XPICFLAGS`
   STDVER=c++0x
fi

AC_SUBST(CC)
AC_SUBST(CXX11)
AC_SUBST(CXX11STD)
AC_SUBST(CXX11PICFLAGS)
AC_SUBST(STDVER)

AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT

