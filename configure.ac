AC_INIT([RcppParallel], 2018.1.0)

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  AC_MSG_ERROR([could not determine R_HOME])
fi

R_VERSION=`"${R_HOME}/bin/R" --vanilla --slave -e "cat(as.character(getRversion()))"`
if test "${R_VERSION}" \< "3.4.0"; then
  R_CXX11_PREFIX="CXX1X"
else
  R_CXX11_PREFIX="CXX11"
fi

AC_SUBST(R_CXX11_PREFIX)
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT

