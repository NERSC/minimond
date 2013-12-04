/* mingmond */

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

#include "collector_meminfo.h"

FILE *logfile;

int main (int argc, char **argv) {
    open_logfile();
#if DAEMONIZE == 1
    daemonize();
#endif
    drop_privileges();

    fprintf(logfile,"Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);

    metric_group metric_groups[METRIC_GROUPS_MAX];


    while(1) {
        if(!(MetricGroupGroupCreate(metric_groups))) {
            fatal_error("Failed to create metric group collection.");
        }

        log_str(LOG_DEBUG,"Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);

        MetricsCollect(&meminfo_collect, metric_groups);
        MetricsCollect(&netdev_collect, metric_groups);
        MetricsCollect(&diskstats_collect, metric_groups);
        MetricsCollect(&loadavg_collect, metric_groups);
        MetricsCollect(&cpustat_collect, metric_groups);
        MetricsCollect(&micsmc_collect, metric_groups);

        MetricsPrint(&text_printer, metric_groups);
        //MetricsPrint(&gmetric_printer, metric_groups);

        log_str(LOG_DEBUG,"Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);
        //fclose(logfile);
        //open_logfile();
        fflush(logfile);
        sleep(COLLECT_PERIOD);
    }

    fclose(logfile);
    close_logfile();

    return 1;
}

