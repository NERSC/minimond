/* mingmond */

#define _GNU_SOURCE
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "mingmond.h"

void process_all() {
    void *collectors[] = { 
        cpustat_collect,
        diskstats_collect,
        loadavg_collect,
        meminfo_collect,
        micsmc_collect,
        netdev_collect,
        NULL };

    void *printers[] = {
        text_printer,
        NULL };

    int i = 0;
    metric_collection mc;

    log_str(LOG_DEBUG,"Sizeof mg(%lu) metric(%lu) all(%lu)\n",
            sizeof(metric_group), sizeof(metric),
            sizeof(metric_group)*METRIC_GROUPS_MAX);

    if(!(MetricCollectionCreate(&mc))) {
        fatal_error("Failed to create metric group collection.");
    }

    for (i = 0; collectors[i] != NULL ; i++) {
        MetricsCollect(collectors[i], &mc);
    }

    for (i = 0; printers[i] != NULL ; i++) {
        MetricsPrint(printers[i], &mc);
    }
}


void drop_privileges(void) {

    struct passwd const *mingmond_u;

    /* Retrieve the passwd structure for the unprivileged user. */
    errno = 0;
    mingmond_u = getpwnam(MINGMOND_USER);

    if (mingmond_u==NULL) {
        fatal_error("getpwnam failed for %s: %s\n",MINGMOND_USER, strerror(errno));
    }

    /* Drop privileges */
    if( setgroups(1, &(mingmond_u->pw_gid)) != 0) {
      fatal_error("setgroups() failed: %s", strerror(errno));
    }

    if(setresgid(mingmond_u->pw_gid, mingmond_u->pw_gid, mingmond_u->pw_gid) != 0 ) {
      fatal_error("setresgid to %d failed: %s", mingmond_u->pw_gid, strerror(errno));
    }

    if(setresuid(mingmond_u->pw_uid, mingmond_u->pw_uid, mingmond_u->pw_uid) != 0 ) {
      fatal_error("setresuid to %d failed: %s", mingmond_u->pw_uid, strerror(errno));
    }
}


void daemonize(void) {
    pid_t child_pid;
    pid_t session_id;

    child_pid = fork();

    if (child_pid < 0) {
        /* Fork failed */
        fatal_error("fork() failed: %s\n",strerror(errno));
    }
    else if (child_pid > 0) {
        /* Parent process */
        exit(0);
    }

    /* Child process */
    umask(0);
    session_id = setsid();
    if (session_id < 0) {
        fatal_error("Failed to setsid(): %s\n",strerror(errno));
    }

    
    if ((chdir("/")) < 0) {
        fatal_error("Failed to chdir(): %s\n",strerror(errno));
    }

    
    close_fd(STDIN_FILENO);
    close_fd(STDOUT_FILENO);
    close_fd(STDERR_FILENO);

#ifdef MINGMOND_LOG
    close_logfile();
    open_logfile(MINGMOND_LOG);
#endif

}

void close_fd(int fd) {
  int ret;
  ret = close(fd);

  if(ret != 0) {
    fatal_error("close() failed: %s\n",strerror(errno));
  }
}

void file_open(FILE **f, const char *filename, const char *bits) {
    *f = fopen(filename, bits);

    if(*f == NULL) {
        log_str(LOG_EMERG,"Could not open %s: %s\n",
                filename,strerror(errno));
    }
}

void str_nospaces(char *s) {
    for ( ; *s; s++ ) {
        if (*s == ' ') *s = '_';
    }
}

char *s_strncpy(char *dest, const char *src, size_t n) {
    char *value;

    value = strncpy(dest, src, n);
    dest[n-1] = '\0';

    return value;
}

