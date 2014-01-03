lib_LTLIBRARIES = libmingmond.la
libmingmond_la_SOURCES = logging.c util.c storage.c display.c storage.h mingmond.h collector.h collector.c collector_meminfo.c printer_text.c printer_gmetric.c collector_netdev.c collector_diskstats.c collector_loadavg.c collector_cpustat.c collector_micsmc.c

bin_PROGRAMS = mingmond
mingmond_SOURCES = main.c
mingmond_LDADD = libmingmond.la
mingmond_CFLAGS = -static
