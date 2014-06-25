/* printer_gmetric.c */

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

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimond.h"

#ifdef GMETRIC

#define GMETRIC_COMMAND_SIZE 1024
#define GMETRIC_VALUE_SIZE 128

metric_group *gmetric_printer(metric_group *mg, config *c) {
    char buf[GMETRIC_COMMAND_SIZE];
    char type_buf[GMETRIC_VALUE_SIZE];
    int i = 0;
    int ret = 0;
    metric m;

    for (i = 0; i < METRIC_GROUP_MAX_SIZE ; i++) {

        m = mg->metrics[i];

        if(metric_is_new(&m)) {
            break;
        }


        switch(mg->type) {
            case VALUE_INT:
                snprintf(type_buf, GMETRIC_VALUE_SIZE, "-t %s -v %d",
                        "int32", m.val.i);
                break;
            case VALUE_LONG:
                snprintf(type_buf, GMETRIC_VALUE_SIZE, "-t %s -v %lu",
                        "int32", m.val.l);
                break;
            case VALUE_FLOAT:
                snprintf(type_buf, GMETRIC_VALUE_SIZE, "-t %s -v %f",
                        "float", m.val.f);
                break;
            case VALUE_DOUBLE:
                snprintf(type_buf, GMETRIC_VALUE_SIZE, "-t %s -v %f",
                        "double", m.val.d);
                break;
            default:
                fatal_error("Unsupported metric type\n");
                break;
        }

        snprintf(buf,GMETRIC_COMMAND_SIZE,
                "gmetric -n '%.32s_%.32s' %.100s -u bytes -x %d",
                mg->name, m.name, type_buf, COLLECT_PERIOD*3);



#ifdef DEBUG
        log_str(LOG_DEBUG,"system(%s)\n",buf);
#endif

        ret = system(buf);

        if(ret < 0) {
            fatal_error("system() failed: %d\n", ret);
        }
        else if (ret > 0) {
            fatal_error("system() command failed: %d\n", ret);
        }

    }



    return mg;
}

#endif /* GMETRIC */
