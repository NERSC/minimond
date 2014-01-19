/* mingmond */

#include <stdlib.h>
#include "mingmond.h"


int main (int argc, char **argv) {

    config cfg;

    parse_args(argc, argv, &cfg);

#if SUPPORT_LOGFILE == 1
    open_logfile(cfg.logfile);
#endif /* SUPPORT_LOGFILE */

#if SUPPORT_DAEMONIZE == 1
    if (cfg.daemonize) {
        daemonize(&cfg);
    }
#endif /* SUPPORT_DAEMONIZE */

    if(cfg.pidfile[0]) {
        write_pidfile(cfg.pidfile);
    }

#if DROP_PRIVILEGES == 1
    if (cfg.drop_privileges) {
        drop_privileges(cfg.user);
    }
#endif

    while(1) {

        process_all(&cfg);

#if SUPPORT_LOGFILE == 1
        fflush(logfile);
#endif /* SUPPORT_LOGFILE */

        sleep(COLLECT_PERIOD);
    }

#ifdef SUPPORT_LOGFILE
    close_logfile();
#endif

    return(EXIT_SUCCESS);
}

