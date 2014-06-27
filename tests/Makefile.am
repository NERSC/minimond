TESTS = check_minimond
check_PROGRAMS = check_minimond
check_minimond_SOURCES = check_minimond.c $(top_builddir)/src/minimond.h
check_minimond_CFLAGS = @check_CFLAGS@
check_minimond_LDADD = $(top_builddir)/src/libminimond.la @check_LIBS@
if SUPPORT_AMQP
check_minimond_LDADD += $(AMQP_LIBS)
endif
