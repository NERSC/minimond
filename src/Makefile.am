lib_LTLIBRARIES = libminimond.la
libminimond_la_SOURCES = args.c logging.c util.c storage.c display.c storage.h minimond.h collector.h collector.c collector_meminfo.c printer_text.c collector_netdev.c collector_diskstats.c collector_loadavg.c collector_cpustat.c collector_mmpmon.c
if SUPPORT_GMETRIC
libminimond_la_SOURCES += printer_gmetric.c
endif
if SUPPORT_EMBEDDEDGMETRIC
libminimond_la_SOURCES += printer_embeddedgmetric.c
libminimond_la_LIBADD = $(EMBEDDEDGMETRIC_LIBS)
endif

sbin_PROGRAMS = minimond
minimond_SOURCES = main.c
minimond_LDADD = libminimond.la
minimond_CFLAGS = -static
