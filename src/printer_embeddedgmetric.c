/* printer_embeddedgmetric.c */

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


#ifdef EMBEDDEDGMETRIC
#include "embeddedgmetric.h"


metric_group *embeddedgmetric_printer(metric_group *mg, config *c) {
    char buf[MAX_LINE];
    int i = 0;
    metric m;

    gmetric_t g;
    gmetric_message_t g_msg;

    gmetric_create(&g);

    if(!gmetric_open(&g, c->embg_host, c->embg_port)) {
        log_str(LOG_DEBUG,
                "Failed to open EmbeddedGmetric connection: %s.  Metrics will not be sent during this collection period\n",
                strerror(errno));
        return mg;
    }

    for (i = 0; i < METRIC_GROUP_MAX_SIZE ; i++) {

        m = mg->metrics[i];

        if(metric_is_new(&m)) {
            break;
        }

        gmetric_message_clear(&g_msg);

        snprintf(buf, MAX_LINE, "%.32s_%.32s", mg->name, m.name);
        g_msg.name = buf;


        switch(mg->type) {
            case VALUE_INT:
                g_msg.type = GMETRIC_VALUE_UNSIGNED_INT;
                g_msg.value.v_uint = m.val.i;
                break;
            case VALUE_LONG:
                g_msg.type = GMETRIC_VALUE_UNSIGNED_INT;
                g_msg.value.v_uint = m.val.l;
                break;
            case VALUE_ULLONG:
                /* Convert the value to a form supported by gmetric. */
                g_msg.type = GMETRIC_VALUE_DOUBLE;
                g_msg.value.v_double = (double)m.val.llu;
                break;
            case VALUE_FLOAT:
                g_msg.type = GMETRIC_VALUE_FLOAT;
                g_msg.value.v_float = m.val.f;
                break;
            case VALUE_DOUBLE:
                g_msg.type = GMETRIC_VALUE_DOUBLE;
                g_msg.value.v_double = m.val.d;
                break;
            default:
                fatal_error("Unsupported metric type: %d\n", mg->type);
                break;
        }

        g_msg.slope = GMETRIC_SLOPE_BOTH;

        g_msg.tmax = c->collect_period*3;
        g_msg.dmax = 0;

        if(gmetric_send(&g, &g_msg) == -1) {
            log_str(LOG_DEBUG,
                    "Failed to send on EmbeddedGmetric connection: %s.  Metrics will not be sent during this collection period\n",
                    strerror(errno));
        }
        else if(c->debug) {
            switch(mg->type) {
                case VALUE_INT:
                    break;
                case VALUE_LONG:
                    break;
                case VALUE_FLOAT:
                    break;
                case VALUE_DOUBLE:
                    log_str(LOG_DEBUG,
                            "Sent %s:%lf on EmbeddedGmetric connection to %s:%d\n",
                            g_msg.name,g_msg.value.v_double,
                            c->embg_host, c->embg_port);
                    break;
                default:
                    log_str(LOG_DEBUG,
                            "Sent on EmbeddedGmetric connection to %s:%d\n",
                            c->embg_host, c->embg_port);
                    break;
        }
        }



    }

    gmetric_close(&g);
    return mg;

}
#endif /* EMBEDDEDGMETRIC */
