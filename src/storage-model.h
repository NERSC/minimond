/*
 * storage-model.h
 *
 * Definitions of minimond data interface
 *
 */

#ifndef STORAGE_MODEL_H
#define STORAGE_MODEL_H

#include "config-model.h"
#include "storage.h"

/*
 * Set up a new group of metric groups.
 * Set all associated metric groups to a "NEW" state.
 */
metric_collection *MetricCollectionCreate(metric_collection *mc);

/*
 * Set up a new metric group with the given name.  Set all
 * associated metrics to a "NEW" state.
 */
metric_group *MetricGroupCreate(metric_group *mg, char *name);

/* Create a new metric with the give name and value. */
metric *MetricCreate(metric *m, char *name, metric_type type,
        metric_value val);

/* Set the name of metric number count in group mg to name */
void MetricSetName(metric_group *mg, int count, char *name);

/*
 * Return a pointer to the next metric_group in metric_collection mc
 * is still in a "NEW" state
 */
metric_group *MetricGroupNextFree(metric_collection *mc);

/*
 * Check if a metric group is still in a "NEW" state
 * Returns 1 if NEW, 0 otherwise
 */
int metric_group_is_new(metric_group *mg);

/*
 * Check if a metric is still in a "NEW" state
 * Returns 1 if NEW, 0 otherwise
 */
int metric_is_new(metric *m);

/*
 * A function which takes a metric_group* as input and returns a
 * metric_group*
 */
typedef metric_group *(MetricHandler)(metric_group *, config *);

#endif /* STORAGE_MODEL_H */
