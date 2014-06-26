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

#define NET_DEV "/proc/net/dev"

metric_group *netdev_collect(metric_group *mg) {
    FILE *netdev = NULL;
    metric_file_open(&netdev, NET_DEV);

    netdev_collect_from_file(mg, netdev);

    metric_file_close(netdev);

    return mg;
}

metric_group *netdev_collect_from_file(metric_group *mg, FILE *f) {

    char buf[MAX_LINE];
    char name[MAX_LINE];
    char netdev_name_buf[MAX_LINE];

    int count = 0;
    int metric_count = 0;
    int c=0;
    long long unsigned d[METRIC_GROUP_MAX_SIZE];
    const char *labels[] = { "rx_bytes", "rx_packets", "rx_errs", "rx_drop", "rx_fifo", "rx_frame", "rx_compressed", "rx_multicast",
                            "tx_bytes", "tx_packets", "tx_errs", "tx_drop", "tx_fifo", "tx_frame", "tx_compressed", "tx_multicast",
                            NULL };

    mg->type = VALUE_ULLONG;
    s_strncpy(mg->name, "netdev", NAME_MAX);

    while (fgets(buf, MAX_LINE, f)) {
        c=0;
        /*
         * iface:bytes packets errs drop fifo frame compressed multicast bytes packets errs drop fifo colls carrier compressed
         * %s   :d[0]  d[1]    d[2] d[3] d[4] d[5]  d[6]       d[7]      d[8]  d[9]    d[10]d[11]d[12]d[13] d[14]   d[15]
         */
        count = sscanf(buf," %32[^\t:]:%llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                netdev_name_buf,
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
                &d[10],
                &d[11],
                &d[12],
                &d[13],
                &d[14],
                &d[15]
                );

        if (count != 17) continue;


        for( count=0 ; labels[count] != NULL; count++, metric_count_incr(&metric_count) ) { 


            snprintf(name, MAX_LINE, "%s_%s", netdev_name_buf, labels[count] );
            s_strncpy(mg->metrics[metric_count].name, name, NAME_MAX);
            mg->metrics[metric_count].val.llu = d[count];

        }

    }



    return mg;
}
