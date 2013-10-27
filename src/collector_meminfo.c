/* collector.c */

#include <stdio.h>
#include <unistd.h>
#include "mingmond.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"

#define MEMINFO "/proc/meminfo"
#define MAX_LINE 100

metric_group *meminfo_collect(metric_group *mg) {
    FILE *meminfo = NULL;
    char buf[MAX_LINE];
    int c = 0;
    int label_end = 0;;
    int value_begin = 0;
    int value_end = 0;;
    int size;
    int l = 0;

    mg->type = VALUE_LONG;
    s_strncpy(mg->name, "meminfo", NAME_MAX);

    meminfo = fopen(MEMINFO, "r");

    if(meminfo == NULL) {
        fprintf(stderr, "Could not open %s: %s\n",
                MEMINFO,strerror(errno));
        fatal_error("Could not open MEMINFO file");
    }


    while (fgets(buf, MAX_LINE, meminfo)) {
        for (c = 0; c < strlen(buf); c++ ) {
            if(buf[c] == ':') {
                label_end = c - 1;
            }
            else if( (label_end > 0) && (value_begin == 0) ){
                if(buf[c] != ' ') {
                    value_begin = c;
                }
            }
            else if( (value_begin > 0) && (value_end == 0) ){ 
                if(buf[c] == ' ') {
                    value_end = c - 1;
                }
            }
        } 

        if (label_end > NAME_MAX) {
            size = NAME_MAX;
            fprintf(stderr,"label truncated.\n");
        }
        else {
            size = label_end + 2;
        }

        s_strncpy(mg->metrics[l].name, buf, size);

        size = value_end - value_begin;
        buf[value_begin + size] = '\0';

        mg->metrics[l].val.l = atoi(buf+value_begin)*1024;

        l++;
        if (l > METRIC_GROUP_MAX_SIZE) {
            fatal_error("Metric group max size exceeded");
        }

    }

    if(fclose(meminfo) != 0) {
        fprintf(stderr, "Could not close %s: %s\n",
                MEMINFO,strerror(errno));
        fatal_error("Could not close MEMINFO file");
    }

    return mg;
}
