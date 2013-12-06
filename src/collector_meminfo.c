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
    char buf[MAX_LINE];
    char name_buf[MAX_LINE];
    int count = 0;
    int metric_count = 0;
    unsigned long metric_value = 0;

    mg->type = VALUE_LONG;
    s_strncpy(mg->name, "meminfo", NAME_MAX);

    metric_file_open(&meminfo, MEMINFO);

    while (fgets(buf, MAX_LINE, meminfo)) {
        count = sscanf(buf," %32[^\t:]:%lu",
                name_buf,
                &metric_value);

        if (count != 2) continue;

        s_strncpy(mg->metrics[metric_count].name, name_buf, NAME_MAX);
        mg->metrics[metric_count].val.l = metric_value*1024;

        metric_count_incr(&metric_count);

    }

    metric_file_close(meminfo);

    return mg;
}
