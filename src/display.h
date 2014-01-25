/* display.h */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "mingmond.h"
//#include "storage-model.h"

/*Print all metrics in mc using print_func */
metric_collection *MetricsPrint(MetricHandler *print_func,
        metric_collection *mc, config *c);

/* Print all metrics in plain text. */
metric_group *text_printer(metric_group *mg, config *c);

#ifdef GMETRIC
/* Send all metrics using the "gmetric" program, which is assumed to
 * be present. */
metric_group *gmetric_printer(metric_group *mg, config *c);
#endif /* GMETRIC */

#ifdef EMBEDDEDGMETRIC
/* Send all metrics using the "embeddedgmetric" library */
metric_group *gmetric_printer(metric_group *mg, config *c);
#endif /* CONFIG_SUPPORT_EMBEDDEDGMETRIC */

#endif /* DISPLAY_H */
