#include <check.h>
#include <stdlib.h>
#include "../src/mingmond.h"

#define MEMINFO_TEST "meminfo_test_input.txt"
#define MEMINFO_TEST_LOG "meminfo_test_log.txt"
#define MEMINFO_TEST_OUTPUT "meminfo_test_output.txt"

#define DISKINFO_TEST "diskinfo_test_input.txt"
#define DISKINFO_TEST_LOG "diskinfo_test_log.txt"
#define DISKINFO_TEST_OUTPUT "diskinfo_test_output.txt"

#define NETDEV_TEST "netdev_test_input.txt"
#define NETDEV_TEST_LOG "netdev_test_log.txt"
#define NETDEV_TEST_OUTPUT "netdev_test_output.txt"

#define CPUSTAT_TEST "cpustat_test_input.txt"
#define CPUSTAT_TEST_LOG "cpustat_test_log.txt"
#define CPUSTAT_TEST_OUTPUT "cpustat_test_output.txt"

#define LOADAVG_TEST "loadavg_test_input.txt"
#define LOADAVG_TEST_LOG "loadavg_test_log.txt"
#define LOADAVG_TEST_OUTPUT "loadavg_test_output.txt"

#define MICSMC_TEST "micsmc_test_input.txt"
#define MICSMC_TEST_LOG "micsmc_test_log.txt"
#define MICSMC_TEST_OUTPUT "micsmc_test_output.txt"

#define PROCESS_ALL_TEST_LOG "process_all_test_log.txt"
#define PROCESS_ALL_TEST_OUTPUT "process_all_test_output.txt"

/* Compare the contents of file1 and file2. */
int compare_files(char *file1, char *file2) {

    /*
     * Create two buffers to hold bytes read from both files.
     * Pre-fill them with NULL bytes.
     */
    char buf1[10000];
    char buf2[10000];

    FILE *f1 = NULL;
    FILE *f2 = NULL;

    memset(buf1, '\0', 10000);
    memset(buf2, '\0', 10000);
    
    /* Open both files and read the bytes. */
    file_open(&f1, file1, "r");
    file_open(&f2, file2, "r");

    fread(buf1, 10000, 1, f1);
    fread(buf2, 10000, 1, f2);

    fclose(f1);
    fclose(f2);

    buf1[9999] = '\0';
    buf2[9999] = '\0';

    /* Compare both buffers */
    return(!(strcmp(buf1,buf2)));
}

/* Test that a set of metric groups can be created. */
START_TEST (test_MetricGroupGroupCreate) {
    metric_collection mc;
    MetricCollectionCreate(&mc);

    ck_assert_str_eq(mc.mg[0].name, "NEW");

}
END_TEST

/*
 * Test that we can create metric groups, set values, and read back
 * those values. 
 * Create a metric group, set some values, and then test that they are
 * properly read back from memory.
 */
START_TEST (test_dummy_collect) {
    metric_group mg;
    dummy_collect(&mg);

    ck_assert_str_eq(mg.name, "d");

    ck_assert(mg.type == VALUE_FLOAT);

    ck_assert_str_eq(mg.metrics[0].name, "m1");
    ck_assert_str_eq(mg.metrics[1].name, "m2");
    ck_assert_str_eq(mg.metrics[2].name, "m3");

    ck_assert(mg.metrics[0].val.f == 4);
    ck_assert(mg.metrics[1].val.f == 8);
    ck_assert(mg.metrics[2].val.f == 12);

}
END_TEST


void metric_collection_do(
        metric_group *(*collector_func)(metric_group *, FILE *),
        char *in, char *log) {
    open_logfile(log);
    FILE *mf = NULL;
    metric_collection mc;
    MetricCollectionCreate(&mc);
    ck_assert_str_eq(mc.mg[0].name, "NEW");

    metric_file_open(&mf, in);

    collector_func(&(mc.mg[0]), mf);
    metric_file_close(mf);
    MetricsPrint(&text_printer, &mc);
    close_logfile();
}

/* Test the meminfo collector */
START_TEST (test_meminfo_collect) {
    metric_collection_do(meminfo_collect_from_file, MEMINFO_TEST, MEMINFO_TEST_LOG);
    ck_assert(compare_files(MEMINFO_TEST_LOG,MEMINFO_TEST_OUTPUT));
}
END_TEST

/* Test the diskstats collector */
START_TEST (test_diskstats_collect) {
    metric_collection_do(diskstats_collect_from_file, DISKINFO_TEST, DISKINFO_TEST_LOG);
    ck_assert(compare_files(DISKINFO_TEST_LOG,DISKINFO_TEST_OUTPUT));
}
END_TEST

/* Test the netdev collector */
START_TEST (test_netdev_collect) {
    metric_collection_do(netdev_collect_from_file, NETDEV_TEST, NETDEV_TEST_LOG);
    ck_assert(compare_files(NETDEV_TEST_LOG,NETDEV_TEST_OUTPUT));
}
END_TEST

/* Test the cpustat collector */
START_TEST (test_cpustat_collect) {
    metric_collection_do(cpustat_collect_from_file, CPUSTAT_TEST, CPUSTAT_TEST_LOG);
    ck_assert(compare_files(CPUSTAT_TEST_LOG,CPUSTAT_TEST_OUTPUT));
}
END_TEST

/* Test the loadavg collector */
START_TEST (test_loadavg_collect) {
    metric_collection_do(loadavg_collect_from_file, LOADAVG_TEST, LOADAVG_TEST_LOG);
    ck_assert(compare_files(LOADAVG_TEST_LOG,LOADAVG_TEST_OUTPUT));
}
END_TEST

/* Test the micsmc collector */
START_TEST (test_micsmc_collect) {
    metric_collection_do(micsmc_collect_from_file, MICSMC_TEST, MICSMC_TEST_LOG);
    ck_assert(compare_files(MICSMC_TEST_LOG,MICSMC_TEST_OUTPUT));
}
END_TEST

/*
 * Test that running all collector/printer combos at once completes
 * normally
 */
START_TEST (test_process_all) {
    open_logfile(PROCESS_ALL_TEST_LOG);
    process_all();
    close_logfile();
}
END_TEST

/* Boilerplate code to run all tests and report results */
Suite *mingmond_suite (void) {
  Suite *s = suite_create ("mingmond");

  TCase *tc_main = tcase_create ("main");

  tcase_add_test (tc_main, test_MetricGroupGroupCreate);
  tcase_add_test (tc_main, test_dummy_collect);
  tcase_add_test (tc_main, test_cpustat_collect);
  tcase_add_test (tc_main, test_diskstats_collect);
  tcase_add_test (tc_main, test_loadavg_collect);
  tcase_add_test (tc_main, test_meminfo_collect);
  tcase_add_test (tc_main, test_micsmc_collect);
  tcase_add_test (tc_main, test_netdev_collect);
  tcase_add_test (tc_main, test_process_all);

  suite_add_tcase (s, tc_main);

  return s;
}

int main (void) {

  int number_failed;

  Suite *s = mingmond_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);

  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


