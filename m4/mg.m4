AC_DEFUN([MG_ENABLE],[
    default_val=$2

    pushdef([en_N],enable-$1)
    pushdef([en_UN],enable_$1)
    pushdef([up_UN], translit($1, [a-z_], [A-Z_]))
    pushdef([descr],$3)

    pushdef([en_UN_DEF],"$enable_$1")


    AC_ARG_ENABLE($1,
                  [AS_HELP_STRING(--$en_N,
                  [descr @<:@default=$default_val@:>@])],
                  [], [en_UN=$default_val])


    AC_DEFINE_UNQUOTED(up_UN, en_UN_DEF, descr)

])dnl# AC_DEFUN([MG_ENABLE])

AC_DEFUN([MG_WITH],[
    default_val=$2

    pushdef([en_N],with-$1)
    pushdef([en_UN],with_$1)
    pushdef([up_UN], translit($1, [a-z_], [A-Z_]))
    pushdef([descr],$3)

    pushdef([en_UN_DEF],"$with_$1")


    AC_ARG_WITH($1,
                  [AS_HELP_STRING(--$en_N,
                  [descr @<:@default=$default_val@:>@])],
                  [], [en_UN=$default_val])



if test "$en_UN" == "yes"; then
    AC_DEFINE_UNQUOTED(up_UN, en_UN_DEF, descr)
else
    en_UN=no
fi

])dnl# AC_DEFUN([MG_WITH])
