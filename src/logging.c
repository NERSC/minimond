/* mingmond */

#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "mingmond.h"

FILE *logfile;

void vlog(int log_level, char *format_str, va_list args) {
    char buf[MAX_LINE];
    snprintf(buf, MAX_LINE, format_str, args);
    fputs(buf, logfile);
#if DEBUG_FG == 1
    fputs(buf, stderr);
#endif
}

void log_str(int log_level, char *format_str, ...) {
    va_list args;
    va_start(args, format_str);
    vlog(log_level, format_str, args);
    va_end(args);
}

void fatal_error(char *format_str, ...) {
    va_list args;
    va_start(args, format_str);
    vlog(LOG_EMERG, format_str, args);
    va_end(args);
    exit(-1);
}


void open_logfile(void) {
    logfile = fopen(MINGMOND_LOG, "w");
    if(logfile == NULL) {
        fprintf(stderr,"Failed to open logfile: %s\n",strerror(errno));
        exit(-1);
    }
}

void close_logfile(void) {
    fclose(logfile);
}
