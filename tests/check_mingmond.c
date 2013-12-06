#include <check.h>
#include <stdlib.h>
#include "../src/mingmond.h"

START_TEST (test_MetricGroupGroupCreate) {
    metric_group metric_groups[METRIC_GROUPS_MAX];
    MetricGroupGroupCreate(metric_groups);

    ck_assert_str_eq(metric_groups[0].name, "NEW");

}
END_TEST




/* Boilerplate code to run all tests and report results */
Suite *mingmond_suite (void) {
  Suite *s = suite_create ("mingmond");

  TCase *tc_main = tcase_create ("main");

  tcase_add_test (tc_main, test_MetricGroupGroupCreate);

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


