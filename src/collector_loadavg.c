/* collector.c */

/*
 * MiniMond, Copyright (c) 2014, The Regents of the University of
 * California, through Lawrence Berkeley National Laboratory (subject to
 * receipt of any required approvals from the U.S. Dept. of Energy).  All
 * rights reserved.
 * 
 * If you have questions about your rights to use or distribute this
 * software, please contact Berkeley Lab's Technology Transfer Department
 * at  TTD@lbl.gov.
 * 
 * NOTICE.  This software is owned by the U.S. Department of Energy.  As
 * such, the U.S. Government has been granted for itself and others
 * acting on its behalf a paid-up, nonexclusive, irrevocable, worldwide
 * license in the Software to reproduce, prepare derivative works, and
 * perform publicly and display publicly.  Beginning five (5) years after
 * the date permission to assert copyright is obtained from the U.S.
 * Department of Energy, and subject to any subsequent five (5) year
 * renewals, the U.S. Government is granted for itself and others acting
 * on its behalf a paid-up, nonexclusive, irrevocable, worldwide license
 * in the Software to reproduce, prepare derivative works, distribute
 * copies to the public, perform publicly and display publicly, and to
 * permit others to do so.
 */

#include <stdio.h>
#include <unistd.h>
#include "minimond.h"
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
