/* display.h */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "storage-model.h"

/*Print all metrics in mc using print_func */
metric_collection *MetricsPrint(MetricHandler *print_func, metric_collection *mc);

/* Print all metrics in plain text. */
metric_group *text_printer(metric_group *mg);

/* Send all metrics using the "gmetric" program, which is assumed to
 * be present. */
metric_group *gmetric_printer(metric_group *mg);

#endif /* DISPLAY_H */
