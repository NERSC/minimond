/* defs.h */
#ifndef DEFS_H
#define DEFS_H

/* Support daemonizing */
#define SUPPORT_DAEMONIZE 1
/* Daemonize by default */
#define DAEMONIZE 1

/* Support dropping privileges to MINGMOND_USER */
#define SUPPORT_DROP_PRIVILEGES 1
/* Drop privileges by default */
#define DROP_PRIVILEGES 1
/* Default privilege drop user */
#define MINGMOND_USER "ganglia"

/* Support logging to a file. */
#define SUPPORT_LOGFILE 1
/* Default logfile */
#define MINGMOND_LOG "/var/log/mingmond.log"

/* Log messages to stdout by default */
#define DEBUG_FG 0

/* How often, in seconds, that metrics should be collected. */
#define COLLECT_PERIOD 120

/*
 * The maximum length of a stored string, including the
 * trailing null byte. 
 */
#define MAX_LINE 400

/* Definitions of debug levels. */
#define LOG_DEBUG 7
#define LOG_EMERG 0

#endif /* DEFS_H */
