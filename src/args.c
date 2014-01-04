/* args.c */

#include "mingmond.h"

config cfg;

config *ConfigDefaultCreate(config *c) {
    s_strncpy(c->user, MINGMOND_USER, NAME_MAX-1);
    s_strncpy(c->logfile, MINGMOND_LOG, NAME_MAX-1);

    c->pidfile[0] = '\0';

    c->daemonize = DAEMONIZE;
    c->debug_fg = DEBUG_FG;
    c->drop_privileges = DROP_PRIVILEGES;

    c->collectors = default_collectors;
    c->printers = default_printers;

    return c;
}

void parse_args(int argc, char **argv, config *c) {
    if(!(ConfigDefaultCreate(c))) {
        fatal_error("Failed to load default configuration.\n");
    }
}
