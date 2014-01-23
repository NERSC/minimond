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
              [], [enable_check=no])

if test "$enable_check" = "yes"; then
    AC_DEFINE([ENABLE_CHECK], [], [Support check testing framework])
    PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
    AC_CONFIG_FILES(tests/Makefile)
fi
AM_CONDITIONAL([SUPPORT_CHECK], [test "$enable_check" = "yes"])

AC_ARG_WITH([logfile],
              [AS_HELP_STRING([--with-logfile],
              [Logfile location @<:@default=DATADIR/log/mingmond.log@:>@])],
              [], [with_logfile=/var/log/mingmond.log])

AC_DEFINE_UNQUOTED([LOGFILE], ["$with_logfile"], [Logfile location])

AC_ARG_WITH([target_user],
              [AS_HELP_STRING([--with-target_user],
              [Target target_user @<:@default=ganglia@:>@])],
              [], [with_target_user=ganglia])

AC_DEFINE_UNQUOTED([TARGET_USER], ["$with_target_user"], [Default privilege drop user])

AC_ARG_WITH([daemonize_default],
              [AS_HELP_STRING([--with-daemonize_default],
              [Target daemonize_default @<:@default=yes@:>@])],
              [], [with_daemonize_default=yes])

case $with_daemonize_default in
    yes)
        with_daemonize_default=1 ;;
    *)
        with_daemonize_default=0 ;;
esac

AC_DEFINE_UNQUOTED([DAEMONIZE],  [$with_daemonize_default], [Daemonize by default])

AM_CONFIG_HEADER(config.h)

AC_OUTPUT(Makefile src/Makefile)

AC_MSG_RESULT([

*********************************************
* PROJECT_NAME $VERSION configuration:
*********************************************
*   Enable tests.........................$enable_check
*   Log file location....................$with_logfile
*   Target user..........................$with_target_user
*   Daemonize by default.................$with_daemonize_default
*********************************************


])
