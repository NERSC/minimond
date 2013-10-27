/* collector.h */

/* Collect metrics for metric_group mg using collector_func */
metric_group *MetricsCollect(metric_group
        *(*collector_func)(metric_group *), metric_group *mg);

/* A very simple collection function for test purposes */
metric_group *dummy_collect(metric_group *mg);
