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
    unsigned long long metric_value = 0;

    mg->type = VALUE_ULLONG;
    s_strncpy(mg->name, "meminfo", NAME_MAX);


    while (fgets(buf, MAX_LINE, f)) {
        count = sscanf(buf," %32[^\t:]:%llu",
                name_buf,
                &metric_value);

        if (count != 2) continue;

        s_strncpy(mg->metrics[metric_count].name, name_buf, NAME_MAX);
        mg->metrics[metric_count].val.llu = metric_value*1024;

        metric_count_incr(&metric_count);

    }


    return mg;
}
