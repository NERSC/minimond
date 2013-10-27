/* display.h */


metric_group *MetricsPrint(metric_group *(*print_func)(metric_group *), metric_group *mg);
metric_group *dummy_printer(metric_group *mg);
