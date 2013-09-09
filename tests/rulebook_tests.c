#include "minunit.h"
#include "rulebook_util.h"
#include <reg/rule.h>
#include <reg/rulebook.h>

static DFARulebook *rulebook = NULL;

char *test_next_state() {
  mu_assert(DFARulebook_next_state(rulebook, 1, 'a') == 2, "Didn't transition to state 2");
  mu_assert(DFARulebook_next_state(rulebook, 1, 'b') == UNDEFINED, "Undefined transition succeeded");
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  DFARulebook_build(
    { .state = 1, .character = 'a', .next_state = 2 },
    { .state = 2, .character = 'b', .next_state = 1 }
  );

  mu_run_test(test_next_state);

  DFARulebook_destroy(rulebook);

  return NULL;
}

RUN_TESTS(all_tests);
