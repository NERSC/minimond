/* collector.c */

#include <stdio.h>
#include <unistd.h>
#include "mingmond.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

#define DISKSTATS "/proc/diskstats"


metric_group *diskstats_collect(metric_group *mg) {
    FILE *diskstats = NULL;

    char buf[MAX_LINE];
    char name[MAX_LINE];
    char name_buf[MAX_LINE];

    int count = 0;
    int metric_count = 0;
    int c=0;
    long unsigned d[METRIC_GROUP_MAX_SIZE];

    /* These names are from mod_diskstat */
    const char *labels[] = { "readIO", "readMerge", "readSectors",
                             "readTicks", "writeIO", "writeMerge",
                             "writeSectors", "writeTicks", "inFlight",
                             "ioTicks", "inQueue"
                           };

    mg->type = VALUE_LONG;
    s_strncpy(mg->name, "diskstats", NAME_MAX);

    metric_file_open(&diskstats, DISKSTATS);

    while (fgets(buf, MAX_LINE, diskstats)) {
        c=0;
        /*
         * maj    min   dev  rIO  rMer rSec  rTick   wIO  wMer  wSec  wTick inFli ioTick  inQueue
         * 8      17    sdb1 1887 3905 46336 29476   0    0     0     0     0     28308   29467
         * %*     %*    %s   d[0] d[1] d[2]  d[3]    d[4] d[5]  d[6]  d[7]  d[8]  d[9]    d[10]
         */
        count = sscanf(buf," %*d %*d %32[^\t ] %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                name_buf,
                &d[0],
                &d[1],
                &d[2],
                &d[3],
                &d[4],
                &d[5],
                &d[6],
                &d[7],
                &d[8],
                &d[9],
                &d[10]
                );

        if (count != 12) continue;

        for( count=0 ; labels[count] != NULL; count++, metric_count_incr(&metric_count) ) { 


            snprintf(name, MAX_LINE, "%s_%s", name_buf, labels[count] );
            s_strncpy(mg->metrics[metric_count].name, name, NAME_MAX);
            mg->metrics[metric_count].val.l = d[count];

        }

    }


    metric_file_close(diskstats);

    return mg;
}
