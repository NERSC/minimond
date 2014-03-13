/* collector.c */

#include <stdio.h>
#include <unistd.h>
#include "mingmond.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

/* #define MMPMON "echo io_s | /usr/lpp/mmfs/bin/mmpmon -s" */
#define MMPMON "/usr/lpp/mmfs/bin/mmpmon_printstats"

metric_group *mmpmon_collect(metric_group *mg) {
    char cmd_buf[MAX_LINE];
    FILE *mmpmon = NULL;

    if(access(MMPMON, X_OK) == 0) {

        snprintf(cmd_buf, MAX_LINE, "sudo %s", MMPMON );
        log_str(LOG_DEBUG, "Running: %s\n",cmd_buf );

        metric_file_popen(&mmpmon, cmd_buf);

        mmpmon_collect_from_file(mg, mmpmon);

        metric_file_pclose(mmpmon);

    }

    return mg;
}

metric_group *mmpmon_collect_from_file(metric_group *mg, FILE *f) {

    char buf[MAX_LINE];
    char name[MAX_LINE];
    char name_buf[MAX_LINE];
    int count = 0;
    int metric_count = 0;
    unsigned long metric_value = 0;

    mg->type = VALUE_LONG;
    s_strncpy(mg->name, "gpfs", NAME_MAX);


    while (fgets(buf, MAX_LINE, f)) {
        count = sscanf(buf," %32[^\t:]:%lu",
                name_buf,
                &metric_value);

        if (count != 2) continue;

        snprintf(name, MAX_LINE, "total_%s", name_buf );

        MetricSetName(mg, metric_count, name);

        mg->metrics[metric_count].val.l = metric_value;
        metric_count_incr(&metric_count);

    }


    return mg;
}
