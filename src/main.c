/* mingmond */

#include <stdlib.h>
#include "mingmond.h"

extern FILE *logfile;

int main (int argc, char **argv) {

#ifdef MINGMOND_LOG
    open_logfile(MINGMOND_LOG);
#endif

#if DAEMONIZE == 1
    daemonize();
#endif

#if DROP_PRIVILEGES == 1
    drop_privileges();
#endif

    while(1) {

        process_all();

#ifdef MINGMOND_LOG
        fflush(logfile);
#endif

        sleep(COLLECT_PERIOD);
    }

#ifdef MINGMOND_LOG
    close_logfile();
#endif

    return EXIT_SUCCESS;
}

