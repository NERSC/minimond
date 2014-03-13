/* collector.h */

#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <stdio.h>
#include "storage-model.h"


/* Collect metrics for metric_collection mc using collector_func */
metric_group *MetricsCollect(MetricHandler *collector_func,
        metric_collection *mc, config *c);

/* A very simple collection function for test purposes */
metric_group *dummy_collect(metric_group *mg);

metric_group *cpustat_collect(metric_group *mg);
metric_group *diskstats_collect(metric_group *mg);
metric_group *loadavg_collect(metric_group *mg);
metric_group *meminfo_collect(metric_group *mg);
metric_group *micsmc_collect(metric_group *mg);
metric_group *mmpmon_collect(metric_group *mg);
metric_group *netdev_collect(metric_group *mg);

metric_group *cpustat_collect_from_file(metric_group *mg, FILE *f);
metric_group *diskstats_collect_from_file(metric_group *mg, FILE *f);
metric_group *loadavg_collect_from_file(metric_group *mg, FILE *f);
metric_group *meminfo_collect_from_file(metric_group *mg, FILE *f);
metric_group *micsmc_collect_from_file(metric_group *mg, FILE *f);
metric_group *mmpmon_collect_from_file(metric_group *mg, FILE *f);
metric_group *netdev_collect_from_file(metric_group *mg, FILE *f);

void metric_file_open(FILE **metric_file, const char *filename);
void metric_file_close(FILE *metric_file);
void metric_file_popen(FILE **metric_file, const char *filename);
void metric_file_pclose(FILE *metric_file);

unsigned long *next_lu(unsigned long *d, int *count);
float *next_f(float *f, int *count);

void metric_count_incr(int *metric_count);
void micsmc_insert_metric(metric_group *mg, int *metric_count, char
        *mic_name, char *name_buf, float f);

#endif /* DISPLAH_H */
