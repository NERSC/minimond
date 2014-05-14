/* textprinter.c */

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
#include "minimond.h"

metric_group *text_printer(metric_group *mg, config *c) {
    int i = 0;
    metric m;

    for (i = 0; i < METRIC_GROUP_MAX_SIZE ; i++) {

        m = mg->metrics[i];

        if(metric_is_new(&m)) {
            break;
        }

        log_str(LOG_EMERG,"%20s_%-20s : ",mg->name, m.name);
        //fprintf(stderr,"%20s_%-20s : ",mg->name, m.name);
        switch(mg->type) {
            case VALUE_INT:
                log_str(LOG_EMERG,"int:%d\n", m.val.i);
                break;
            case VALUE_LONG:
                log_str(LOG_EMERG,"long:%lu\n", m.val.l);
                break;
            case VALUE_FLOAT:
                log_str(LOG_EMERG,"float:%f\n", m.val.f);
                break;
            default:
                fatal_error("Unsupported metric type %d\n", mg->type);
                break;
        }
    }



    return mg;
}
