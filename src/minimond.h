#ifndef MINIMOND_H
#define MINIMOND_H

#include "../config.h"
#include "defs.h"
#include "collector.h"
#include "config-model.h"
#include "display.h"


extern FILE *logfile;



extern void *default_collectors[];
extern void *default_printers[];


config *ConfigDefaultCreate(config *c);
void close_fd(int fd);
void close_logfile(void);
void daemonize(config *c);
void drop_privileges(char *user);
void fatal_error(char *format_str, ...);

/* Write the current pid to the file at filename. */
void write_pidfile(char *filename);

/* Open filename using the FILE * at f and with the passed mode bits.  */
void file_open(FILE **f, const char *filename, const char *bits);

/* Close the file at f. */
void file_close(FILE *f);

/* Open filename as the logfile. */
void open_logfile(char *filename);

/*
 * Process arguments in argv and update the configuration
 * accordingly.
 */
void parse_args(int argc, char **argv, config *c);

/* Print usage messages. */
void usage(char *progname);
void usage_and_fail(char *progname);

/* Log format_str at log_level to the appropriate log. */
void log_str(int log_level, char *format_str, ...);
void vlog(int log_level, char *format_str, va_list args);

/* Replace all spaces in s with underscores */
void str_nospaces(char *s);

/* Process all metrics */
void process_all(config *c);

/*
 * "Safe" version on the strncpy function.
 * Explicitly set the final byte to '\0'
 */
char *s_strncpy(char *dest, const char *src, size_t n);


#endif /* MINIMOND_H */
