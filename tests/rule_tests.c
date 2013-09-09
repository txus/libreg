#include "minunit.h"
#include <reg/rule.h>

static FARule *rule = NULL;

char *test_applies_to() {
  mu_assert(FARule_applies_to(rule, 1, 'a'), "Rule doesn't apply.");
  mu_assert(!FARule_applies_to(rule, 1, 'b'), "Rule does apply with the wrong char.");
  mu_assert(!FARule_applies_to(rule, 2, 'a'), "Rule does apply with the wrong state.");
  return NULL;
}

char *test_follow() {
  mu_assert(FARule_follow(rule) == 2, "Rule doesn't follow to the next state.");
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  rule = FARule_create(1, 'a', 2);

  mu_run_test(test_applies_to);
  mu_run_test(test_follow);

  FARule_destroy(rule);

  return NULL;
}

RUN_TESTS(all_tests);