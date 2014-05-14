/* minimond */

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
#include "minimond.h"


int main (int argc, char **argv) {

    config cfg;

    parse_args(argc, argv, &cfg);

#if SUPPORT_LOGFILE == 1
    open_logfile(cfg.logfile);
#endif /* SUPPORT_LOGFILE */

#if SUPPORT_DAEMONIZE == 1
    if (cfg.daemonize == 1) {
        log_str(LOG_DEBUG,"Daemonizing");
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

