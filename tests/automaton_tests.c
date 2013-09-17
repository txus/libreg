#include "minunit.h"
#include "rulebook_util.h"
#include <reg/automaton.h>

static Rulebook *rulebook = NULL;
static DFA *dfa = NULL;
static NFA *nfa = NULL;

char *test_dfa_accepting() {
  Rulebook_build(
    { .state = STATE(rulebook, 1), .character = 'a', .next_state = STATE(rulebook, 2) },
    { .state = STATE(rulebook, 2), .character = 'b', .next_state = STATE(rulebook, 3) }
  );

  Set *accept_states = Set_create();
  Set_push(accept_states, STATE(rulebook, 3));

  dfa = DFA_create(STATE(rulebook, 1), accept_states, rulebook);

  mu_assert(!DFA_accepting(dfa), "DFA accepting at state 1.");
  DFA_read_character(dfa, 'a');
  mu_assert(!DFA_accepting(dfa), "DFA accepting at state 2.");
  DFA_read_character(dfa, 'b');
  mu_assert(DFA_accepting(dfa), "DFA not accepting at state 3.");

  dfa->current_state = STATE(rulebook, 1); // reset

  DFA_read_string(dfa, "ab");
  mu_assert(DFA_accepting(dfa), "DFA not accepting at state 3.");

  Rulebook_destroy(rulebook);
  DFA_destroy(dfa);
  return NULL;
}

char *test_nfa_accepting() {
  Rulebook_build(
    { .state = STATE(rulebook, 1), .character = 'a', .next_state = STATE(rulebook, 2) },
    { .state = STATE(rulebook, 2), .character = 'a', .next_state = STATE(rulebook, 3) }
  );

  Set *initial_states = Set_create();
  Set *accept_states = Set_create();

  Set_push(initial_states, STATE(rulebook, 1));
  Set_push(initial_states, STATE(rulebook, 2));

  Set_push(accept_states, STATE(rulebook, 3));
  Set_push(accept_states, STATE(rulebook, 4));

  nfa = NFA_create(initial_states, accept_states, rulebook);

  mu_assert(!NFA_accepting(nfa), "NFA accepting at states 1 and 2.");

  NFA_read_string(nfa, "a");

  mu_assert(NFA_accepting(nfa), "NFA not accepting at state 3.");

  Rulebook_destroy(rulebook);
  NFA_destroy(nfa);
  return NULL;
}

char *test_nfa_accepting_with_free_moves() {
  Rulebook_build(
    { .state = STATE(rulebook, 1), .character = '\0', .next_state = STATE(rulebook, 2) }
  );

  Set *initial_states = Set_create();
  Set_push(initial_states, STATE(rulebook, 1));

  Set *accept_states = Set_create();
  Set_push(accept_states, STATE(rulebook, 2));

  nfa = NFA_create(initial_states, accept_states, rulebook);

  mu_assert(NFA_accepting(nfa), "NFA not accepting at freely achieved state 4.");

  Rulebook_destroy(rulebook);
  NFA_destroy(nfa);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_dfa_accepting);
  mu_run_test(test_nfa_accepting);
  mu_run_test(test_nfa_accepting_with_free_moves);

  return NULL;
}

RUN_TESTS(all_tests);
