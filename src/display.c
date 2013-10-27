/* display.c */

#include "storage.h"
#include "display.h"
#include <stdio.h>

metric_group *MetricsPrint(metric_group *(*print_func)(metric_group *), metric_group *mg) {
    int c = 0;
    for (c = 0; c < METRIC_GROUPS_MAX; c++) {
        if(!(metric_group_is_new(&mg[c]))) {
            print_func(&mg[c]);
        }
    }

    return mg;
}

metric_group *dummy_printer(metric_group *mg) {
    printf("Metric group name: %s\n",mg->name);
    printf("Metric 0 name: %s\n",mg->metrics[0].name);
    printf("Metric 0 value: %d\n",mg->metrics[0].val.i);

    return mg;
}

