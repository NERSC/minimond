/* args.c */

#include <stdlib.h>
#include <string.h>
#include "mingmond.h"

config cfg;

config *ConfigDefaultCreate(config *c) {
    s_strncpy(c->user, TARGET_USER, MAX_LINE);
    s_strncpy(c->logfile, LOGFILE, MAX_LINE);

    c->pidfile[0] = '\0';

#ifdef DAEMONIZE_DEFAULT
    c->daemonize = 1;
#else
    c->daemonize = 0;
#endif /* DAEMONIZE_DEFAULT */

    c->debug_fg = DEBUG_FG;
    c->drop_privileges = DROP_PRIVILEGES;

#ifdef EMBEDDEDGMETRIC
    s_strncpy(c->embg_host, "localhost", MAX_LINE);
    c->embg_port = 8649;
#endif /* EMBEDDEDGMETRIC */

    c->collectors = default_collectors;
    c->printers = default_printers;

    return c;
}

void parse_args(int argc, char **argv, config *c) {
    char buf[MAX_LINE];
    char *s;
    int arg;
    int count;

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

                if(!(strcmp(buf,"embg_host"))) {
                    s_strncpy(c->embg_host, s, MAX_LINE);
                }
                else if(!(strcmp(buf,"embg_port"))) {
                   count = sscanf(s,"%d", &(c->embg_port));
                   if (count != 1) {
                       fatal_error("Unable to handle port number: %s\n",buf);
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
