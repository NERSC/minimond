/* mingmond */

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "mingmond.h"

#include "collector_meminfo.h"

int main (int argc, char **argv) {
    drop_privileges();

    printf("Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);

    metric_group metric_groups[METRIC_GROUPS_MAX];


    while(1) {
        if(!(MetricGroupGroupCreate(metric_groups))) {
            fatal_error("Failed to create metric group collection.");
        }
        printf("Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);
        MetricsCollect(&meminfo_collect, metric_groups);
        MetricsCollect(&netdev_collect, metric_groups);
        MetricsCollect(&diskstats_collect, metric_groups);
        MetricsCollect(&loadavg_collect, metric_groups);
        MetricsCollect(&cpustat_collect, metric_groups);
        MetricsPrint(&text_printer, metric_groups);
        //MetricsPrint(&gmetric_printer, metric_groups);
        printf("Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);
        sleep(COLLECT_PERIOD);
    }

    return 1;
}

void fatal_error(char *s) {
    fprintf(stderr,"%s\n",s);
    exit(-1);
}

void drop_privileges(void) {

    struct passwd const *mingmond_u;

    /* Retrieve the passwd structure for the unprivileged user. */
    errno = 0;
    mingmond_u = getpwnam(MINGMOND_USER);

    if (mingmond_u==NULL) {
        fprintf(stderr,"getpwnam failed for %s: %s\n",MINGMOND_USER, strerror(errno));
        fatal_error("Failed to drop privileges");
    }

    /* Drop privileges */
    if( setgroups(1, &(mingmond_u->pw_gid)) != 0) {
      fprintf(stderr, "setgroups() failed: %s", strerror(errno));
      fatal_error("Failed to drop privileges");
    }

    if(setresgid(mingmond_u->pw_gid, mingmond_u->pw_gid, mingmond_u->pw_gid) != 0 ) {
      fprintf(stderr, "setresgid to %d failed: %s", mingmond_u->pw_gid, strerror(errno));
      fatal_error("Failed to drop privileges");
    }

    if(setresuid(mingmond_u->pw_uid, mingmond_u->pw_uid, mingmond_u->pw_uid) != 0 ) {
      fprintf(stderr, "setresuid to %d failed: %s", mingmond_u->pw_uid, strerror(errno));
      fatal_error("Failed to drop privileges");
    }
}
