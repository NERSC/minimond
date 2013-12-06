/* collector.c */

#include <stdio.h>
#include <unistd.h>
#include "mingmond.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

#define MEMINFO "/proc/meminfo"

metric_group *meminfo_collect(metric_group *mg) {
    FILE *meminfo = NULL;
    metric_file_open(&meminfo, MEMINFO);

    meminfo_collect_from_file(mg, meminfo);

    metric_file_close(meminfo);

    return mg;
}

metric_group *meminfo_collect_from_file(metric_group *mg, FILE *f) {

    char buf[MAX_LINE];
    char name_buf[MAX_LINE];
    int count = 0;
    int metric_count = 0;
    unsigned long metric_value = 0;

    mg->type = VALUE_LONG;
    s_strncpy(mg->name, "meminfo", NAME_MAX);


    while (fgets(buf, MAX_LINE, f)) {
        count = sscanf(buf," %32[^\t:]:%lu",
                name_buf,
                &metric_value);

        if (count != 2) continue;

        s_strncpy(mg->metrics[metric_count].name, name_buf, NAME_MAX);
        mg->metrics[metric_count].val.l = metric_value*1024;

        metric_count_incr(&metric_count);

    }


    return mg;
}
