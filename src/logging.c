/* mingmond */

#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "mingmond.h"

FILE *logfile;
int log_active = 0;

void vlog(int log_level, char *format_str, va_list args) {
    char buf[MAX_LINE];
    vsnprintf(buf, MAX_LINE, format_str, args);
    if(log_active == 1) fputs(buf, logfile);
    else if (log_active < 0) fputs(buf, stderr);
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

void open_logfile(char *filename) {
    log_active = -1;
    file_open(&logfile, filename, "w");
    log_active = 1;
}

void close_logfile(void) {
    fclose(logfile);
    log_active = 0;
}

