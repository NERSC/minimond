/* printer_embeddedgmetric.c */


#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mingmond.h"


#ifdef EMBEDDEDGMETRIC
#include "embeddedgmetric.h"


metric_group *embeddedgmetric_printer(metric_group *mg, config *c) {
    int i = 0;
    metric m;

    gmetric_t g;
    gmetric_message_t g_msg;

    gmetric_create(&g);

    if(!gmetric_open(&g, c->embg_host, c->embg_port)) {
        log_str(LOG_DEBUG,"Failed to open EmbeddedGmetric connection: %s.  Metrics will not be sent during this collection period\n", strerror(errno));
        return mg;
    }

    for (i = 0; i < METRIC_GROUP_MAX_SIZE ; i++) {

        m = mg->metrics[i];

        if(metric_is_new(&m)) {
            break;
        }

        gmetric_message_clear(&g_msg);



        switch(mg->type) {
            case VALUE_INT:
                g_msg.type = GMETRIC_VALUE_INT;
                g_msg.value.v_int = m.val.i;
                break;
            case VALUE_LONG:
                g_msg.type = GMETRIC_VALUE_INT;
                g_msg.value.v_int = m.val.l;
                break;
            case VALUE_FLOAT:
                g_msg.type = GMETRIC_VALUE_FLOAT;
                g_msg.value.v_int = m.val.f;
                break;
            default:
                fatal_error("Unsupported metric type: %d\n", mg->type);
                break;
        }

        g_msg.slope = GMETRIC_SLOPE_BOTH;

        g_msg.tmax = COLLECT_PERIOD*3;
        g_msg.dmax = 0;

        if(gmetric_send(&g, &g_msg) == -1) {
            log_str(LOG_DEBUG,"Failed to send on EmbeddedGmetric connection: %s.  Metrics will not be sent during this collection period\n", strerror(errno));
        }



    }

    gmetric_close(&g);
    return mg;

}
#endif /* EMBEDDEDGMETRIC */
