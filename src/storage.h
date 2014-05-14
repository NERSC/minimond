/*
 * storage.h
 *
 * Definitions of minimond data structrues
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

/* A collection of metric groups. */
typedef struct mc {
    metric_group mg[METRIC_GROUPS_MAX];
} metric_collection;
