/*
 * storage.h
 *
 * Definitions of mingmond data structrues
 *
 */

#include <unistd.h>

/*
 * The maximum length of a metric or metric group name, including the
 * NULL byte.
 */
#define NAME_MAX 24

/* The maximum number of metrics in a metric group. */
#define METRIC_GROUP_MAX_SIZE 1024

/* The maximum number of metric groups. */
#define METRIC_GROUPS_MAX 16

/* A metric value */
union metric_value {
    int i;
    long l;
    char c;
    float f;
    double d;
};
typedef union metric_value metric_value;

/* Various types of metrics; */
enum metric_type {
    VALUE_INT,
    VALUE_LONG,
    VALUE_CHAR,
    VALUE_FLOAT,
    VALUE_DOUBLE
};
typedef enum metric_type metric_type;

/* A single metric measurement */
typedef struct metric {
    char name[NAME_MAX];
    metric_value val;
} metric;

/* A group of up to METRIC_GROUP_MAX_SIZE metrics */
typedef struct metric_group {
    char name[NAME_MAX];
    metric_type type;
    metric metrics[METRIC_GROUP_MAX_SIZE];
} metric_group;


/*
 * Set up a new group of metric groups.
 * Set all associated metric groups to a "NEW" state.
 */
metric_group *MetricGroupGroupCreate(metric_group *mg);

/*
 * Set up a new metric group with the given name.  Set all
 * associated metrics to a "NEW" state.
 */
metric_group *MetricGroupCreate(metric_group *mg, char *name);

/* Create a new metric with the give name and value. */
metric *MetricCreate(metric *m, char *name, metric_type type,
        metric_value val);

/*
 * Return a pointer to the next metric_group in the array at *mg that
 * is still in a "NEW" state
 */
metric_group *MetricGroupNextFree(metric_group *mg);

/*
 * "Safe" version on the strncpy function.
 * Explicitly set the final byte to '\0'
 */
char *s_strncpy(char *dest, const char *src, size_t n);

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
