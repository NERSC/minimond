/* minimond */

/*
 * MiniMond, Copyright (c) 2014, The Regents of the University of
 * California, through Lawrence Berkeley National Laboratory (subject to
 * receipt of any required approvals from the U.S. Dept. of Energy).  All
 * rights reserved.
 * 
 * If you have questions about your rights to use or distribute this
 * software, please contact Berkeley Lab's Technology Transfer Department
 * at  TTD@lbl.gov.
 * 
 * NOTICE.  This software is owned by the U.S. Department of Energy.  As
 * such, the U.S. Government has been granted for itself and others
 * acting on its behalf a paid-up, nonexclusive, irrevocable, worldwide
 * license in the Software to reproduce, prepare derivative works, and
 * perform publicly and display publicly.  Beginning five (5) years after
 * the date permission to assert copyright is obtained from the U.S.
 * Department of Energy, and subject to any subsequent five (5) year
 * renewals, the U.S. Government is granted for itself and others acting
 * on its behalf a paid-up, nonexclusive, irrevocable, worldwide license
 * in the Software to reproduce, prepare derivative works, distribute
 * copies to the public, perform publicly and display publicly, and to
 * permit others to do so.
 */

#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "minimond.h"

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
    exit(EXIT_FAILURE);
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

