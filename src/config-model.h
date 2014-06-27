/* config-model.h */
#ifndef CONFIG_MODEL_H
#define CONFIG_MODEL_H

#include "defs.h"

/* Configuration settings */
typedef struct config {
    char user[MAX_LINE];
    char logfile[MAX_LINE];
    char pidfile[MAX_LINE];
    unsigned int collect_period;
    int drop_privileges;
    int debug;
    int debug_fg;
    int daemonize;
    void **collectors;
    void **printers;

# ifdef EMBEDDEDGMETRIC
    char embg_host[MAX_LINE];
    int embg_port;
# endif /* EMBEDDEDGMETRIC */

# ifdef AMQP
    char amqp_host[MAX_LINE];
    char amqp_exchange[MAX_LINE];
    char amqp_routingkey[MAX_LINE];
    int amqp_port;
# endif /* AMQP */
} config;

#endif /* CONFIG_MODEL_H */
