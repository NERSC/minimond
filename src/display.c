/* display.c */

#include "mingmond.h"
#include <stdio.h>

metric_collection *MetricsPrint(metric_group *(*print_func)(metric_group *), metric_collection *mc) {
    int c = 0;
    for (c = 0; c < METRIC_GROUPS_MAX; c++) {
        if(!(metric_group_is_new(&(mc->mg[c])))) {
            print_func(&(mc->mg[c]));
        }
    }

    return mc;
}


