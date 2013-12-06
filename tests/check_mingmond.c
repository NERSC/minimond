#include <check.h>
#include <stdlib.h>
#include "../src/mingmond.h"

#define MEMINFO_TEST "meminfo_test_input.txt"
#define MEMINFO_TEST_LOG "meminfo_test_log.txt"
#define MEMINFO_TEST_OUTPUT "meminfo_test_output.txt"

int compare_files(char *file1, char *file2) {

    char buf1[10000];
    char buf2[10000];

    FILE *f1 = NULL;
    FILE *f2 = NULL;
    
    file_open(&f1, file1, "r");
    file_open(&f2, file2, "r");

    fread(buf1, 10000, 1, f1);
    fread(buf2, 10000, 1, f2);

    buf1[9999] = '\0';
    buf2[9999] = '\0';

    return(!(strcmp(buf1,buf2)));
}

/* Test that a set of metric groups can be created. */
START_TEST (test_MetricGroupGroupCreate) {
    metric_group metric_groups[METRIC_GROUPS_MAX];
    MetricGroupGroupCreate(metric_groups);

    ck_assert_str_eq(metric_groups[0].name, "NEW");

}
END_TEST

/* Test that we can create metric groups, set values, and read back
 * those values. */
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

/* Test the meminfo collector */
START_TEST (test_meminfo_collect) {
    open_logfile(MEMINFO_TEST_LOG);
    FILE *mf = NULL;
    metric_group mgs[METRIC_GROUPS_MAX];
    MetricGroupGroupCreate(mgs);
    ck_assert_str_eq(mgs[0].name, "NEW");

    metric_file_open(&mf, MEMINFO_TEST);

    meminfo_collect_from_file(mgs, mf);
    metric_file_close(mf);
    MetricsPrint(&text_printer, mgs);
    close_logfile();

    ck_assert(compare_files(MEMINFO_TEST_LOG,MEMINFO_TEST_OUTPUT));
}
END_TEST





/* Boilerplate code to run all tests and report results */
Suite *mingmond_suite (void) {
  Suite *s = suite_create ("mingmond");

  TCase *tc_main = tcase_create ("main");

  tcase_add_test (tc_main, test_MetricGroupGroupCreate);
  tcase_add_test (tc_main, test_dummy_collect);
  tcase_add_test (tc_main, test_meminfo_collect);

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


