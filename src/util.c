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

/* The default set of collector modules. */
void *default_collectors[] = { 
    cpustat_collect,
    diskstats_collect,
    loadavg_collect,
    meminfo_collect,
    micsmc_collect,
    netdev_collect,
    NULL };

/* The default set of printer modules. */
void *default_printers[] = {
    gmetric_printer,
    /* text_printer, */
    NULL };

void process_all(config *c) {

    int i = 0;
    metric_collection mc;

    log_str(LOG_DEBUG,"Sizeof mg(%lu) metric(%lu) all(%lu)\n",
            sizeof(metric_group), sizeof(metric),
            sizeof(metric_group)*METRIC_GROUPS_MAX);

    if(!(MetricCollectionCreate(&mc))) {
        fatal_error("Failed to create metric group collection.");
    }

    for (i = 0; c->collectors[i] != NULL ; i++) {
        MetricsCollect(c->collectors[i], &mc, c);
    }

    for (i = 0; c->printers[i] != NULL ; i++) {
        MetricsPrint(c->printers[i], &mc, c);
    }
}


void drop_privileges(char *user) {

    struct passwd const *mingmond_u;

    /* Retrieve the passwd structure for the unprivileged user. */
    errno = 0;
    mingmond_u = getpwnam(user);

    if (mingmond_u==NULL) {
        fatal_error("getpwnam failed for %s: %s\n", user, strerror(errno));
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


void daemonize(config *c) {
    pid_t child_pid;
    pid_t session_id;

    child_pid = fork();

    if (child_pid < 0) {
        /* Fork failed */
        fatal_error("fork() failed: %s\n",strerror(errno));
    }
    else if (child_pid > 0) {
        /* Parent process */
        exit(EXIT_SUCCESS);
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

#ifdef LOGFILE
    close_logfile();
    open_logfile(c->logfile);
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
        fatal_error("Could not open %s: %s\n",
                filename,strerror(errno));
    }
}

void file_close(FILE *f) {

    if(fclose(f) != 0) {
        fatal_error("Could not close %s: %s\n",
                "file",strerror(errno));
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

void usage(char *progname) {
    printf("%s [-p pidfile] [-v]\n",progname);
}

void usage_and_fail(char *progname) {
    usage(progname);
    fatal_error("Invalid usage");
}

void write_pidfile(char *filename) {
    FILE *f;
    file_open(&f, filename, "w");
    fprintf(f, "%ld\n", (long)getpid());
    file_close(f);
}

