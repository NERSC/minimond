lib_LTLIBRARIES = libmingmond.la
libmingmond_la_SOURCES = args.c logging.c util.c storage.c display.c storage.h mingmond.h collector.h collector.c collector_meminfo.c printer_text.c collector_netdev.c collector_diskstats.c collector_loadavg.c collector_cpustat.c collector_mmpmon.c
if SUPPORT_GMETRIC
libmingmond_la_SOURCES += printer_gmetric.c
endif
if SUPPORT_EMBEDDEDGMETRIC
libmingmond_la_SOURCES += printer_embeddedgmetric.c
libmingmond_la_LIBADD = $(EMBEDDEDGMETRIC_LIBS)
endif

sbin_PROGRAMS = mingmond
mingmond_SOURCES = main.c
mingmond_LDADD = libmingmond.la
mingmond_CFLAGS = -static
