/* display.h */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "minimond.h"
//#include "storage-model.h"

/*Print all metrics in mc using print_func */
metric_collection *MetricsPrint(MetricHandler *print_func,
        metric_collection *mc, config *c);

/* Print all metrics in plain text. */
metric_group *text_printer(metric_group *mg, config *c);

#ifdef AMQP
/* Send all metrics via AMQP */
metric_group *amqp_printer(metric_group *mg, config *c);
#endif /* AMQP */

#ifdef GMETRIC
/* Send all metrics using the "gmetric" program, which is assumed to
 * be present. */
metric_group *gmetric_printer(metric_group *mg, config *c);
#endif /* GMETRIC */

#ifdef EMBEDDEDGMETRIC
/* Send all metrics using the "embeddedgmetric" library */
metric_group *embeddedgmetric_printer(metric_group *mg, config *c);
#endif /* EMBEDDEDGMETRIC */

#endif /* DISPLAY_H */
