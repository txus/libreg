#include "minunit.h"
#include <reg/syntax.h>

char *test_empty() {
  ASTEmpty *node = ASTEmpty_create();
  NFA *nfa = ASTEmpty_to_nfa(node);

  mu_assert(NFA_accepting(nfa), "Empty NFA is not accepting.");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_empty);

  return NULL;
}

RUN_TESTS(all_tests);
