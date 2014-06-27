/* printer_amqp.c */


#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimond.h"


#ifdef AMQPLOGGER
#include <amqpLogger.h>


metric_group *amqplogger_printer(metric_group *mg, config *c) {
    char buf[MAX_LINE];
    int i = 0;
    metric m;


    amqpLogger logger;
    logger.amqp.output_warnings=1;
    amqpLogger_initialize(&logger, AMQP_SERVER_AUTO, "", "", "", "", '|');
    amqpLogger_setidentifiers(&logger, "nodehealth", "health_all");


    for (i = 0; i < METRIC_GROUP_MAX_SIZE ; i++) {

        if(c->debug) { log_str(LOG_DEBUG,"Sending amqplogger metrics\n"); }

        m = mg->metrics[i];

        if(metric_is_new(&m)) {
            break;
        }


        switch(mg->type) {
            case VALUE_INT:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%d", mg->name, m.name, m.val.i);
                break;
            case VALUE_LONG:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%ld", mg->name, m.name, m.val.l);
                break;
            case VALUE_ULLONG:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%llu", mg->name, m.name, m.val.llu);
                break;
            case VALUE_FLOAT:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%f", mg->name, m.name, m.val.f);
                break;
            case VALUE_DOUBLE:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%lf", mg->name, m.name, m.val.d);
                break;
            default:
                fatal_error("Unsupported metric type: %d\n", mg->type);
                break;
        }
        if(c->debug) { log_str(LOG_DEBUG,"Calling lograw amqplogger metrics\n"); }

        if(amqpLogger_lograw(&logger, mg->name, buf, strlen(buf)+1) != 0) {
            log_str(LOG_DEBUG,
                    "Failed to send on amqpLogger connection: %s.  Metrics will not be sent during this collection period\n", buf);
        }
        else if(c->debug) {
            log_str(LOG_DEBUG,
                    "Sent %s on amqpLogger connection\n",
                    buf);
        }
        if(c->debug) {
            log_str(LOG_DEBUG,"Done sending amqplogger metrics\n");
        }

    }

    return mg;

}
#endif /* AMQPLOGGER */
