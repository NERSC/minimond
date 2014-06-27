/* args.c */

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

#include <stdlib.h>
#include <string.h>
#include "minimond.h"

config cfg;

config *ConfigDefaultCreate(config *c) {
    s_strncpy(c->user, TARGET_USER, MAX_LINE);
    s_strncpy(c->logfile, LOGFILE, MAX_LINE);

    c->pidfile[0] = '\0';
    c->collect_period = COLLECT_PERIOD;

#ifdef DAEMONIZE_DEFAULT
    c->daemonize = 1;
#else
    c->daemonize = 0;
#endif /* DAEMONIZE_DEFAULT */

    c->debug = DEBUG;
    c->debug_fg = DEBUG_FG;
    c->drop_privileges = DROP_PRIVILEGES;

#ifdef EMBEDDEDGMETRIC
    s_strncpy(c->embg_host, "localhost", MAX_LINE);
    c->embg_port = 8649;
#endif /* EMBEDDEDGMETRIC */

#ifdef AMQP
    s_strncpy(c->amqp_host, "localhost", MAX_LINE);
    c->amqp_port = 5672;
    s_strncpy(c->amqp_exchange, "amqp_direct", MAX_LINE);
    s_strncpy(c->amqp_routingkey, "nodestats", MAX_LINE);
#endif /* AMQP */

    c->collectors = default_collectors;
    c->printers = default_printers;

    return c;
}

void parse_args(int argc, char **argv, config *c) {
    char buf[MAX_LINE];
    char *s;
    int arg;
#ifdef EMBEDDEDGMETRIC
    int count;
#endif /* EMBEDDEDGMETRIC */

    if(!(ConfigDefaultCreate(c))) {
        fatal_error("Failed to load default configuration.\n");
    }
    while ((arg = getopt(argc, argv, "D:fhl:np:v")) != -1) {
        switch(arg) {
            case 'f':
                c->daemonize = 0;
               break;
            case 'n':
                c->drop_privileges = 0;
               break;
            case 'D':
                s_strncpy(buf, optarg, MAX_LINE);
                s = strstr(buf,"=");
                if(!s) {
                    fatal_error("Failed to parse -D option: %s\n", optarg);
                }

                *s = '\0';
                s++;

                if(strlen(s) < 1) {
                    fatal_error("Unreasonably short value for -D option: %s\n", buf);
                }

#ifdef EMBEDDEDGMETRIC
                if(!(strcmp(buf,"embg_host"))) {
                    s_strncpy(c->embg_host, s, MAX_LINE);
                }
                else if(!(strcmp(buf,"embg_port"))) {
                   count = sscanf(s,"%d", &(c->embg_port));
                   if (count != 1) {
                       fatal_error("Unable to handle port number: %s\n",buf);
                   }
                }
#endif /* EMBEDDEDGMETRIC */
#ifdef AMQP
                if(!(strcmp(buf,"amqp_host"))) {
                    s_strncpy(c->embg_host, s, MAX_LINE);
                }
                else if(!(strcmp(buf,"amqp_port"))) {
                   count = sscanf(s,"%d", &(c->amqp_port));
                   if (count != 1) {
                       fatal_error("Unable to handle period number: %s\n",buf);
                   }
                }
#endif /* AMQP */
                else if(!(strcmp(buf,"collect_period"))) {
                   count = sscanf(s,"%u", &(c->collect_period));
                   if (count != 1) {
                       fatal_error("Unable to handle period number: %s\n",buf);
                   }
                }
                else if(!(strcmp(buf,"debug"))) {
                   count = sscanf(s,"%u", &(c->debug));
                   if (count != 1) {
                       fatal_error("Unable to handle debug number: %s\n",buf);
                   }
                }
                else if(!(strcmp(buf,"debug_fg"))) {
                   count = sscanf(s,"%u", &(c->debug_fg));
                   if (count != 1) {
                       fatal_error("Unable to handle debug_fg number: %s\n",buf);
                   }
                }
               else {
                   fatal_error("Unknown option: %s\n", buf);
               }
               log_str(LOG_DEBUG,"Read config option: %s -> %s\n",buf, s);
               break;
            case 'l':
                s_strncpy(c->logfile, optarg, MAX_LINE);
                break;
            case 'p':
                s_strncpy(c->pidfile, optarg, MAX_LINE);
                break;
            case 'v':
                printf("%s\n",PACKAGE_STRING);
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                usage(argv[0]);
                exit(EXIT_SUCCESS);
                break;
            case '?':
                usage_and_fail(argv[0]);
                break;
        }
    }
}
