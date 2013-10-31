/* collector.c */

#include "mingmond.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

metric_group *MetricsCollect(metric_group
        *(*collector_func)(metric_group *), metric_group *mg) {
    return collector_func(MetricGroupNextFree(mg));
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

unsigned long *next_lu(unsigned long *d, int *count) {
    (*count)++;
    return &d[(*count)-1];
}

float *next_f(float *f, int *count) {
    printf("next_f: %d\n",*count);
    (*count)++;
    return &f[(*count)-1];
}

void metric_file_open(FILE **metric_file, const char *filename) {

    *metric_file = fopen(filename, "r");

    if(*metric_file == NULL) {
        fprintf(stderr, "Could not open %s: %s\n",
                filename,strerror(errno));
        fatal_error("Could not open file");
    }
}

void metric_file_close(FILE *metric_file) {

    if(fclose(metric_file) != 0) {
        fprintf(stderr, "Could not close %s: %s\n",
                "metric file",strerror(errno));
        fatal_error("Could not close metric file");
    }

}
void metric_count_incr(int *metric_count) {
    if (*metric_count == METRIC_GROUP_MAX_SIZE) {
        fatal_error("Metric group max size exceeded");
    }
    (*metric_count)++;
}
