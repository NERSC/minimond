m4_define(PROJECT_NAME,  [mingmond])
m4_define(PROJECT_EMAIL, [lmpezzaglia@lbl.gov])
m4_define(PROJECT_TAR,   [mingmond])
m4_define(PROJECT_MAJOR, 0)
m4_define(PROJECT_MINOR, 0)
m4_define(PROJECT_MICRO, 2)


AC_INIT(PROJECT_NAME, PROJECT_MAJOR.PROJECT_MINOR.PROJECT_MICRO,
                PROJECT_EMAIL, PROJECT_TAR)

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR([m4])

m4_include(m4/mg.m4)

AC_LANG(C)
AC_PROG_CC
AC_PROG_LIBTOOL
CFLAGS="-Wall -Werror"
AC_SUBST(CFLAGS)

AM_INIT_AUTOMAKE
AM_PROG_CC_C_O

MG_ENABLE([logfile], [/var/log/mingmond.log], [Default logfile location])
MG_ENABLE([target_user], [ganglia], [Default privilege drop user])
MG_ENABLE([daemonize_default], [yes], [Daemonize by default])

MG_WITH([check], [no], [Build "check" tests])
MG_WITH([embeddedgmetric], [no], [EmbeddedGmetric support])
MG_WITH([gmetric], [yes], [Gmetric support])

if test "$with_check" = "yes"; then
    AC_DEFINE([CHECK], [], [Support check testing framework])
    PKG_CHECK_MODULES([check], [check >= 0.9.4])
    AC_CONFIG_FILES(tests/Makefile)
fi

if test "$with_embeddedgmetric" = "yes"; then
    AC_DEFINE([EMBEDDEDGMETRIC], [], [Support EmbeddedGmetric])
    PKG_CHECK_MODULES([embeddedgmetric], [embeddedgmetric >= 1.3.0])
fi


if test "$with_gmetric" = "yes"; then
    AC_DEFINE([GMETRIC], [], [Support Gmetric])
    if test "$with_embeddedgmetric" = "yes"; then
        echo "Building with both Gmetric and EmbeddedGmetric is not recommended"
    fi
fi

AM_CONDITIONAL([SUPPORT_CHECK], [test "$with_check" = "yes"])
AM_CONDITIONAL([SUPPORT_EMBEDDEDGMETRIC], [test "$with_embeddedgmetric" = "yes"])
AM_CONDITIONAL([SUPPORT_GMETRIC], [test "$with_gmetric" = "yes"])






AM_CONFIG_HEADER(config.h)

AC_OUTPUT(Makefile src/Makefile)

AC_MSG_RESULT([

***********************************************************************
* PROJECT_NAME $VERSION configuration:
***********************************************************************
*   Daemonize by default.................$enable_daemonize_default
*   Log file location....................$enable_logfile
*   Target user..........................$enable_target_user
*   "make check" support ................$with_check
*   EmbeddedGmetric support..............$with_embeddedgmetric
*   Gmetric support......................$with_gmetric
***********************************************************************


])
