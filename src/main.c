/* mingmond */

#include <stdio.h>
#include <stdlib.h>
#include "mingmond.h"

#include "collector_meminfo.h"

int main (int argc, char **argv) {
    printf("Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);

    metric_group metric_groups[METRIC_GROUPS_MAX];

    if(!(MetricGroupGroupCreate(metric_groups))) {
        fatal_error("Failed to create metric group collection.");
    }

    while(1) {
        printf("Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);
        MetricsCollect(&meminfo_collect, metric_groups);
        //MetricsPrint(&text_printer, metric_groups);
        MetricsPrint(&gmetric_printer, metric_groups);
        sleep(COLLECT_PERIOD);
    }

    return 1;
}

void fatal_error(char *s) {
    fprintf(stderr,"%s\n",s);
    exit(-1);
}
