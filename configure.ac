m4_define(PROJECT_NAME,  [mingmond])
m4_define(PROJECT_EMAIL, [larry@nersc.gov])
m4_define(PROJECT_TAR,   [mingmond])
m4_define(PROJECT_MAJOR, 0)
m4_define(PROJECT_MINOR, 0)
m4_define(PROJECT_MICRO, 0)

AC_INIT(PROJECT_NAME, PROJECT_MAJOR.PROJECT_MINOR.PROJECT_MICRO,
                PROJECT_EMAIL, PROJECT_TAR)

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
CFLAGS="-Wall -Werror"
AC_SUBST(CFLAGS)

AM_INIT_AUTOMAKE
AM_PROG_CC_C_O

PKG_CHECK_MODULES([CHECK], [check >= 0.9.4]) 

AM_CONFIG_HEADER(config.h)

AC_OUTPUT(Makefile src/Makefile tests/Makefile)
