/* collector.c */

#include "storage.h"
#include "collector.h"

metric_group *MetricsCollect(metric_group *(*collector_func)(metric_group *), metric_group *mg) {
    return collector_func(MetricGroupNextFree(mg));
}

metric_group *dummy_collect(metric_group *mg) {
    s_strncpy(mg->name, "dummy", NAME_MAX);
    mg->type = 0;

    s_strncpy(mg->metrics[0].name, "m1", NAME_MAX);
    mg->metrics[0].val.i = 4;

    return mg;
}
