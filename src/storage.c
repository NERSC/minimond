/* storage.c */

#include "mingmond.h"
#include <string.h>

metric_group *MetricGroupGroupCreate(metric_group *mg) {
    int c = 0;
    for (c = 0; c < METRIC_GROUPS_MAX; c++ ) {
        MetricGroupCreate(&mg[c], "NEW");
    }
    return mg;
}

metric_group *MetricGroupCreate(metric_group *mg, char *name) {
    int c = 0;
    metric_value val = (metric_value)0;

    s_strncpy(mg->name, name, NAME_MAX-1);

    for (c = 0; c < METRIC_GROUP_MAX_SIZE; c++ ) {
        MetricCreate(&(mg->metrics[c]), "NEW", VALUE_INT, val);
    }

    return mg;
}

int metric_group_is_new(metric_group *mg) {
    int is_new = 0;
    if(!(strcmp(mg->name,"NEW"))) {
        is_new = 1;
    }
    return is_new;
}

int metric_is_new(metric *m) {
    int is_new = 0;
    if(!(strcmp(m->name,"NEW"))) {
        is_new = 1;
    }
    return is_new;
}

metric_group *MetricGroupNextFree(metric_group *mg) {
    int c = 0;
    for(c = 0; c < METRIC_GROUPS_MAX; c++) {
        if(metric_group_is_new(&mg[c])) {
            /* We found a NEW metric_group */
            return &mg[c];
        }
    }

    /* We did not find a NEW metric_group */
    fatal_error("No remaining NEW metric_groups");
    return NULL;
}

metric *MetricCreate(metric *m, char *name, metric_type type,
        metric_value val) {
    s_strncpy(m->name, name, NAME_MAX-1);
    m->val = val;
    return m;

}

void MetricSetName(metric_group *mg, int count, char *name) {
    str_nospaces(name);
    s_strncpy(mg->metrics[count].name, name, NAME_MAX);
}

char *s_strncpy(char *dest, const char *src, size_t n) {
    char *value;

    value = strncpy(dest, src, n);
    dest[n-1] = '\0';

    return value;
}


