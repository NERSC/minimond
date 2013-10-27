/* mingmond */

#include <stdio.h>
//#include <unistd.h>
#include "mingmond.h"

int main (int argc, char **argv) {
    printf("Sizeof metric_group(%lu) metric(%lu) all_metric_groups(%lu)\n",sizeof(metric_group), sizeof(metric), sizeof(metric_group)*METRIC_GROUPS_MAX);

    metric_group metric_groups[METRIC_GROUPS_MAX];

    if(!(MetricGroupGroupCreate(metric_groups))) {
        fatal_error("Failed to create metric group collection.");
    }

    MetricsCollect(&dummy_collect, metric_groups);
    MetricsPrint(&dummy_printer, metric_groups);

    if(!(MetricGroupGroupCreate(metric_groups))) {
        fatal_error("Failed to create metric group collection.");
    }
    return 1;

}

void fatal_error(char *s) {
    fprintf(stderr,"%s\n",s);
}
