/* textprinter.c */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mingmond.h"

#define GMETRIC_COMMAND_SIZE 1024
#define GMETRIC_VALUE_SIZE 128

metric_group *gmetric_printer(metric_group *mg) {
    char buf[GMETRIC_COMMAND_SIZE];
    char type_buf[GMETRIC_VALUE_SIZE];
    int c = 0;
    int ret = 0;
    metric m;

    for (c = 0; c < METRIC_GROUP_MAX_SIZE ; c++) {

        m = mg->metrics[c];

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



        printf("system(%s)\n",buf);
        ret = system(buf);

        if(ret < 0) {
            fprintf(stderr, "system() failed: %d\n", ret);
            fatal_error("system() failed");
        }
        else if (ret > 0) {
            fprintf(stderr, "system() command failed: %d\n", ret);
            fatal_error("system() command failed");
        }

    }



    return mg;
}
