AC_PREREQ([2.64])
AC_INIT(Pys, 1.0, jared@lostsidedead.biz)
AM_INIT_AUTOMAKE(Pys, 1.0)
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LANG_CPLUSPLUS

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

LDPREFIX=${prefix}

if test  ${prefix} = "NONE"; then
LDPREFIX=/usr/local
fi

_PREFIX=$LDPREFIX


AC_SUBST(_PREFIX)


AC_OUTPUT(Makefile src/Makefile)


