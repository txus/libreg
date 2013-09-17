#include "minunit.h"
#include "rulebook_util.h"
#include <reg/rule.h>
#include <reg/rulebook.h>

static Rulebook *rulebook = NULL;

char *test_next_state() {
  Rulebook_build(
    { .state = STATE(rulebook, 1), .character = 'a', .next_state = STATE(rulebook, 2) },
    { .state = STATE(rulebook, 2), .character = 'b', .next_state = STATE(rulebook, 1) }
  );

  mu_assert(Rulebook_next_state(rulebook, STATE(rulebook, 1), 'a') == STATE(rulebook, 2), "Didn't transition to state 2");
  mu_assert(Rulebook_next_state(rulebook, STATE(rulebook, 1), 'b') == UNDEFINED, "Undefined transition succeeded");

  Rulebook_destroy(rulebook);
  return NULL;
}

char *test_next_states() {
  Rulebook_build(
    { .state = STATE(rulebook, 1), .character = 'a', .next_state = STATE(rulebook, 2) },
    { .state = STATE(rulebook, 2), .character = 'a', .next_state = STATE(rulebook, 3) }
  );

  Set *previous_states = Set_create();
  Set_push(previous_states, STATE(rulebook, 1));
  Set_push(previous_states, STATE(rulebook, 2));

  Set *next_states = Rulebook_next_states(rulebook, previous_states, 'a');

  mu_assert(
    (!Set_member(next_states, STATE(rulebook, 1)) &&
     Set_member(next_states, STATE(rulebook, 2)) &&
     Set_member(next_states, STATE(rulebook, 3))),
    "Didn't transition from states 1 and 2 to states 2 and 3"
  );

  Set_destroy(previous_states);
  Set_destroy(next_states);

  Rulebook_destroy(rulebook);
  return NULL;
}

char *test_follow_free_moves() {
  Rulebook_build(
    { .state = STATE(rulebook, 1), .character = '\0', .next_state = STATE(rulebook, 2) },
    { .state = STATE(rulebook, 2), .character = '\0', .next_state = STATE(rulebook, 3) }
  );

  Set *initial_states = Set_create();
  Set_push(initial_states, STATE(rulebook, 1));
  Set_push(initial_states, STATE(rulebook, 2));

  Set *next_states = Rulebook_follow_free_moves(rulebook, initial_states);

  mu_assert(
    (Set_member(next_states, STATE(rulebook, 1)) &&
     Set_member(next_states, STATE(rulebook, 2)) &&
     Set_member(next_states, STATE(rulebook, 3))),
    "Didn't follow free moves from states 1 and 2 to states 2 and 3"
  );

  Rulebook_destroy(rulebook);
  Set_destroy(initial_states);
  Set_destroy(next_states);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  message = NULL;
  mu_run_test(test_next_state);
  mu_run_test(test_next_states);
  mu_run_test(test_follow_free_moves);

  return NULL;
}

RUN_TESTS(all_tests);
