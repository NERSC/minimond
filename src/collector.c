/* collector.c */

#include <stdio.h>
#include "storage.h"
#include "collector.h"

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
