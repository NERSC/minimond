/* textprinter.c */

#include <stdio.h>
#include "mingmond.h"

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
