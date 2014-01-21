/* collector.c */

#include "mingmond.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>


metric_group *MetricsCollect(metric_group
        *(*collector_func)(metric_group *, config *),
        metric_collection *mc, config *c) {
    return collector_func(MetricGroupNextFree(mc), c);
}

metric_group *dummy_collect(metric_group *mg) {
    mg->type = VALUE_FLOAT;

    s_strncpy(mg->name, "d", NAME_MAX);

    s_strncpy(mg->metrics[0].name, "m1", NAME_MAX);
    mg->metrics[0].val.f = 4;
    s_strncpy(mg->metrics[1].name, "m2", NAME_MAX);
    mg->metrics[1].val.f = 8;
    s_strncpy(mg->metrics[2].name, "m3", NAME_MAX);
    mg->metrics[2].val.f = 12;

    return mg;
}

void metric_file_open(FILE **metric_file, const char *filename) {

    file_open(metric_file,filename, "r");
}

void metric_file_popen(FILE **metric_file, const char *cmdline) {

    *metric_file = popen(cmdline, "r");

    if(*metric_file == NULL) {
        fatal_error("Could not popen %s: %s\n",
                cmdline,strerror(errno));
    }
}

void metric_file_pclose(FILE *metric_file) {

    int exit_status = -1;

    exit_status = pclose(metric_file);
    if(exit_status != 0) {
        fatal_error("Could not pclose %s: %s; exit status %d\n",
                "metric file",strerror(errno),exit_status);
    }

}

void metric_file_close(FILE *metric_file) {
    file_close(metric_file);
}

void metric_count_incr(int *metric_count) {
    if (*metric_count == METRIC_GROUP_MAX_SIZE) {
        fatal_error("Metric group max size (%d) exceeded",
                METRIC_GROUP_MAX_SIZE);
    }
    (*metric_count)++;
}
