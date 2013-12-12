/* collector.c */

#include <stdio.h>
#include <unistd.h>
#include "mingmond.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

#define LOADAVG "/proc/loadavg"

metric_group *loadavg_collect(metric_group *mg) {
    FILE *loadavg = NULL;
    metric_file_open(&loadavg, LOADAVG);

    loadavg_collect_from_file(mg, loadavg);

    metric_file_close(loadavg);

    return mg;
}

metric_group *loadavg_collect_from_file(metric_group *mg, FILE *f) {
    char buf[MAX_LINE];
    char name[MAX_LINE];
    int count = 0;
    int metric_count = 0;
    float fv[METRIC_GROUP_MAX_SIZE];

    const char *labels[] = { "load_one", "load_five", "load_fifteen",
                             "proc_run", "proc_total", NULL
                           };

    mg->type = VALUE_FLOAT;
    s_strncpy(mg->name, "loadavg", NAME_MAX);

    /*
     * $ cat /proc/loadavg
     * 0.30 0.32 0.38 2/785 20214
     */
    while (fgets(buf, MAX_LINE, f)) {
        count = sscanf(buf," %f %f %f %f/%f",
                &fv[0],
                &fv[1],
                &fv[2],
                &fv[3],
                &fv[4]
                );

        if (count != 5) continue;

        for( count=0 ; labels[count] != NULL; count++, metric_count_incr(&metric_count) ) { 

            snprintf(name, MAX_LINE, "%s", labels[count] );
            s_strncpy(mg->metrics[metric_count].name, name, NAME_MAX);
            mg->metrics[metric_count].val.f = fv[count];

        }

    }

    return mg;
}
