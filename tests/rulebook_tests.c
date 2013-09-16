#include "minunit.h"
#include "rulebook_util.h"
#include <reg/rule.h>
#include <reg/rulebook.h>

static Rulebook *rulebook = NULL;

char *test_next_state() {
  Rulebook_build(
    { .state = 1, .character = 'a', .next_state = 2 },
    { .state = 2, .character = 'b', .next_state = 1 }
  );

  mu_assert(Rulebook_next_state(rulebook, 1, 'a') == 2, "Didn't transition to state 2");
  mu_assert(Rulebook_next_state(rulebook, 1, 'b') == UNDEFINED, "Undefined transition succeeded");

  Rulebook_destroy(rulebook);
  return NULL;
}

char *test_next_states() {
  Rulebook_build(
    { .state = 1, .character = 'a', .next_state = 2 },
    { .state = 2, .character = 'a', .next_state = 3 }
  );

  unsigned int *next_states = Rulebook_next_states(
    rulebook,
    (unsigned int[MAX_STATES]){0,1,2,0},
    'a'
  );

  mu_assert(
    (next_states[1] == UNDEFINED &&
     next_states[2] == 2 && next_states[3] == 3),
    "Didn't transition from states 1 and 2 to states 2 and 3"
  );

  free(next_states);
  Rulebook_destroy(rulebook);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_next_state);
  mu_run_test(test_next_states);

  return NULL;
}

RUN_TESTS(all_tests);
