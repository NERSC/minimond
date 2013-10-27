/* display.h */


metric_group *MetricsPrint(metric_group *(*print_func)(metric_group *), metric_group *mg);

metric_group *text_printer(metric_group *mg);

metric_group *gmetric_printer(metric_group *mg);
