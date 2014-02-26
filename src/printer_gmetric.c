/* printer_gmetric.c */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mingmond.h"

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
