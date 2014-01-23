m4_define(PROJECT_NAME,  [mingmond])
m4_define(PROJECT_EMAIL, [lmpezzaglia@lbl.gov])
m4_define(PROJECT_TAR,   [mingmond])
m4_define(PROJECT_MAJOR, 0)
m4_define(PROJECT_MINOR, 0)
m4_define(PROJECT_MICRO, 1)

AC_INIT(PROJECT_NAME, PROJECT_MAJOR.PROJECT_MINOR.PROJECT_MICRO,
                PROJECT_EMAIL, PROJECT_TAR)

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_LIBTOOL
CFLAGS="-Wall -Werror"
AC_SUBST(CFLAGS)

AM_INIT_AUTOMAKE
AM_PROG_CC_C_O

AC_ARG_ENABLE([check],
              [AS_HELP_STRING([--enable-check],
              [enable tests with check @<:@default=no@:>@])],
              [], [enable_check=check])


if test "$enable_check" = "yes"; then
    AC_DEFINE([ENABLE_CHECK], [], [Support check testing framework])
    PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
    AC_CONFIG_FILES(tests/Makefile)
fi
AM_CONDITIONAL([SUPPORT_CHECK], [test "$enable_check" = "yes"])

AM_CONFIG_HEADER(config.h)

AC_OUTPUT(Makefile src/Makefile)
