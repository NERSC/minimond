/* collector.c */

#include <stdio.h>
#include <unistd.h>
#include "mingmond.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

#define LOADAVG "/proc/loadavg"
#define MAX_LINE 100

metric_group *loadavg_collect(metric_group *mg) {
    FILE *loadavg = NULL;
    char buf[MAX_LINE];
    char name[MAX_LINE];
    int count = 0;
    int metric_count = 0;
    float f[METRIC_GROUP_MAX_SIZE];

    const char *labels[] = { "load_one", "load_five", "load_fifteen",
                             "proc_run", "proc_total"
                           };

    mg->type = VALUE_FLOAT;
    s_strncpy(mg->name, "loadavg", NAME_MAX);

    metric_file_open(&loadavg, LOADAVG);

    /*
     * $ cat /proc/loadavg
     * 0.30 0.32 0.38 2/785 20214
     */
    while (fgets(buf, MAX_LINE, loadavg)) {
        //count = sscanf(buf,"%f %f %f %f/%f %*s",
        count = sscanf(buf,"%f %f %f %f/%f",
                &f[0],
                &f[1],
                &f[2],
                &f[3],
                &f[4]
                );

        if (count != 5) continue;

        for( count=0 ; labels[count] != NULL; count++, metric_count_incr(&metric_count) ) { 

            printf("mc:%d, count:%d %s %f\n",metric_count, count, labels[count], f[count]);
            snprintf(name, MAX_LINE, "%s", labels[count] );
            s_strncpy(mg->metrics[metric_count].name, name, NAME_MAX);
            mg->metrics[metric_count].val.f = f[count];

        }

    }

    metric_file_close(loadavg);

    return mg;
}
