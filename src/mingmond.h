#ifndef MINGMOND_H
#define MINGMOND_H

#include "collector.h"
#include "display.h"

/* Support daemonizing */
#define SUPPORT_DAEMONIZE 1
/* Daemonize by default */
#define DAEMONIZE 1

/* Support dropping privileges to MINGMOND_USER */
#define SUPPORT_DROP_PRIVILEGES 1
/* Drop privileges by default */
#define DROP_PRIVILEGES 1
/* Default privilege drop user */
#define MINGMOND_USER "ganglia"

/* Support logging to a file. */
#define SUPPORT_LOGFILE 1
/* Default logfile */
#define MINGMOND_LOG "/var/log/mingmond.log"

/* Log messages to stdout by default */
#define DEBUG_FG 0

/* How often, in seconds, that metrics should be collected. */
#define COLLECT_PERIOD 120

/*
 * The maximum length of a stored string, including the
 * trailing null byte. 
 */
#define MAX_LINE 400

/* Definitions of debug levels. */
#define LOG_DEBUG 7
#define LOG_EMERG 0

extern FILE *logfile;

/* Configuration settings */
typedef struct config {
    char user[MAX_LINE];
    char logfile[MAX_LINE];
    char pidfile[MAX_LINE];
    int drop_privileges;
    int debug_fg;
    int daemonize;
    void **collectors;
    void **printers;
} config;

extern void *default_collectors[];
extern void *default_printers[];


config *ConfigDefaultCreate(config *c);
void close_fd(int fd);
void daemonize(void);
void drop_privileges(char *user);
void fatal_error(char *format_str, ...);
void vlog(int log_level, char *format_str, va_list args);
void log_str(int log_level, char *format_str, ...);
void open_logfile(char *filename);
void close_logfile(void);
void file_open(FILE **f, const char *filename, const char *bits);
void parse_args(int argc, char **argv, config *c);

/* Replace all spaces in s with underscores */
void str_nospaces(char *s);

/* Process all metrics */
void process_all(config *c);

/*
 * "Safe" version on the strncpy function.
 * Explicitly set the final byte to '\0'
 */
char *s_strncpy(char *dest, const char *src, size_t n);



/*
 * Ganglia metrics:
 *
 * load_one       One minute load average (module load_module)
 * load_five      Five minute load average (module load_module)
 * load_fifteen   Fifteen minute load average (module load_module)
 * proc_run       Total number of running processes (module proc_module)
 * proc_total     Total number of processes (module proc_module)
 *
 * cpu_aidle      Percent of time since boot idle CPU (module cpu_module)
 * cpu_idle       Percentage of time that the CPU or CPUs were idle and the system did not have an outstanding disk I/O request (module cpu_module)
 * cpu_intr       cpu_intr (module cpu_module)
 * cpu_nice       Percentage of CPU utilization that occurred while executing at the user level with nice priority (module cpu_module)
 * cpu_num        Total number of CPUs (module cpu_module)
 * cpu_sintr      cpu_sintr (module cpu_module)
 * cpu_speed      CPU Speed in terms of MHz (module cpu_module)
 * cpu_steal      cpu_steal (module cpu_module)
 * cpu_system     Percentage of CPU utilization that occurred while executing at the system level (module cpu_module)
 * cpu_user       Percentage of CPU utilization that occurred while executing at the user level (module cpu_module)
 * cpu_wio        Percentage of time that the CPU or CPUs were idle during which the system had an outstanding disk I/O request (module cpu_modul
 * boottime       The last time that the system was started (module sys_module)
 * mem_sreclaimableAmount of reclaimable slab memory (module mem_module)
 * os_release     Operating system release date (module sys_module)
 * mem_total      Total amount of memory displayed in KBs (module mem_module)
 * disk_free      Total free disk space (module disk_module)
 * gexec          gexec available (module core_metrics)
 * mem_cached     Amount of cached memory (module mem_module)
 * mtu            Network maximum transmission unit (module sys_module)
 * pkts_in        Packets in per second (module net_module)
 * location       Location of the machine (module core_metrics)
 * bytes_in       Number of bytes in per second (module net_module)
 * swap_total     Total amount of swap space displayed in KBs (module mem_module)
 * bytes_out      Number of bytes out per second (module net_module)
 * mem_free       Amount of available memory (module mem_module)
 * os_name        Operating system name (module sys_module)
 * sys_clock      Time as reported by the system clock (module sys_module)
 * mem_buffers    Amount of buffered memory (module mem_module)
 * part_max_used  Maximum percent used for all partitions (module disk_module)
 * disk_total     Total available disk space (module disk_module)
 * heartbeat      Last heartbeat (module core_metrics)
 * mem_shared     Amount of shared memory (module mem_module)
 * machine_type   System architecture (module sys_module)
 * e)
 * pkts_out       Packets out per second (module net_module)
 * swap_free      Amount of available swap memory (module mem_module)
 */

#endif /* MINGMOND_H */
