/* collector.h */

#include <stdio.h>

/* Collect metrics for metric_group mg using collector_func */
metric_group *MetricsCollect(metric_group
        *(*collector_func)(metric_group *), metric_group *mg);

/* A very simple collection function for test purposes */
metric_group *dummy_collect(metric_group *mg);

metric_group *netdev_collect(metric_group *mg);

void metric_file_open(FILE **metric_file, const char *filename);
void metric_file_close(FILE *metric_file);

long unsigned *next_item(long unsigned *d, int *count);

void metric_count_incr(int *metric_count);
