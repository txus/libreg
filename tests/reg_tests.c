#include "minunit.h"
#include <reg/reg.h>

char *test_simple() {
  Reg *reg = Reg_compile("abc");
  mu_assert(!Reg_match(reg, "ab"), "Should not match 'ab'.");
  mu_assert(!Reg_match(reg, "abcd"), "Should not match 'abcd'.");
  mu_assert(Reg_match(reg, "abc"), "Should match 'abc'.");
  Reg_destroy(reg);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_simple);

  return NULL;
}

RUN_TESTS(all_tests);
