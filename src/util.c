/* mingmond */

#define _GNU_SOURCE
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

void drop_privileges(void) {

    struct passwd const *mingmond_u;

    /* Retrieve the passwd structure for the unprivileged user. */
    errno = 0;
    mingmond_u = getpwnam(MINGMOND_USER);

    if (mingmond_u==NULL) {
        fprintf(logfile,"getpwnam failed for %s: %s\n",MINGMOND_USER, strerror(errno));
        fatal_error("Failed to drop privileges");
    }

    /* Drop privileges */
    if( setgroups(1, &(mingmond_u->pw_gid)) != 0) {
      fprintf(logfile, "setgroups() failed: %s", strerror(errno));
      fatal_error("Failed to drop privileges");
    }

    if(setresgid(mingmond_u->pw_gid, mingmond_u->pw_gid, mingmond_u->pw_gid) != 0 ) {
      fprintf(logfile, "setresgid to %d failed: %s", mingmond_u->pw_gid, strerror(errno));
      fatal_error("Failed to drop privileges");
    }

    if(setresuid(mingmond_u->pw_uid, mingmond_u->pw_uid, mingmond_u->pw_uid) != 0 ) {
      fprintf(logfile, "setresuid to %d failed: %s", mingmond_u->pw_uid, strerror(errno));
      fatal_error("Failed to drop privileges");
    }
}


void daemonize(void) {
    pid_t child_pid;
    pid_t session_id;

    child_pid = fork();

    if (child_pid < 0) {
        /* Fork failed */
        fprintf(logfile, "fork() failed: %s\n",strerror(errno));
        fatal_error("Failed to fork()");
    }
    else if (child_pid > 0) {
        /* Parent process */
        exit(0);
    }

    /* Child process */
    umask(0);
    session_id = setsid();
    if (session_id < 0) {
        fatal_error("Failed to setsid()");
    }

    
    if ((chdir("/")) < 0) {
        fatal_error("Failed to chdir()");
    }

    
    close_fd(STDIN_FILENO);
    close_fd(STDOUT_FILENO);
    close_fd(STDERR_FILENO);
    close_logfile();
    open_logfile();

}

void close_fd(int fd) {
  int ret;
  ret = close(fd);

  if(ret != 0) {
    fprintf(logfile,"close() failed: %s\n",strerror(errno));
    fatal_error("Failed to close()");
  }
}
