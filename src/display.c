/* display.c */

#include "mingmond.h"
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


