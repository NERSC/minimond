/* storage.c */

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

#ifndef STORAGE_H
#define STORAGE_H

#include "minimond.h"
#include <string.h>

metric_collection *MetricCollectionCreate(metric_collection *mc) {
    int c = 0;
    for (c = 0; c < METRIC_GROUPS_MAX; c++ ) {
        MetricGroupCreate(&(mc->mg[c]), "NEW");
    }
    return mc;
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

metric_group *MetricGroupNextFree(metric_collection *mc) {
    int c = 0;
    for(c = 0; c < METRIC_GROUPS_MAX; c++) {
        if(metric_group_is_new(&(mc->mg[c]))) {
            /* We found a NEW metric_group */
            return &(mc->mg[c]);
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

#endif /* STORAGE_H */
