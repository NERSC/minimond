/* display.c */

#include "mingmond.h"
#include <stdio.h>

metric_collection *MetricsPrint(
        metric_group *(*print_func)(metric_group *, config *c),
        metric_collection *mc, config *c) {
    int i = 0;
    for (i = 0; i < METRIC_GROUPS_MAX; i++) {
        if(!(metric_group_is_new(&(mc->mg[i])))) {
            print_func(&(mc->mg[i]), c);
        }
    }

    return mc;
}


