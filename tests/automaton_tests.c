#include "minunit.h"
#include "rulebook_util.h"
#include <reg/automaton.h>

static Rulebook *rulebook = NULL;
static DFA *dfa = NULL;
static NFA *nfa = NULL;

char *test_dfa_accepting() {
  Rulebook_build(
    { .state = 1, .character = 'a', .next_state = 2 },
    { .state = 2, .character = 'b', .next_state = 3 }
  );

  dfa = DFA_create(1, (unsigned int[]){3, 0}, rulebook);

  mu_assert(!DFA_accepting(dfa), "DFA accepting at state 1.");
  DFA_read_character(dfa, 'a');
  mu_assert(!DFA_accepting(dfa), "DFA accepting at state 2.");
  DFA_read_character(dfa, 'b');
  mu_assert(DFA_accepting(dfa), "DFA not accepting at state 3.");

  dfa->current_state = 1; // reset

  DFA_read_string(dfa, "ab");
  mu_assert(DFA_accepting(dfa), "DFA not accepting at state 3.");

  Rulebook_destroy(rulebook);
  DFA_destroy(dfa);
  return NULL;
}

char *test_nfa_accepting() {
  Rulebook_build(
    { .state = 1, .character = 'a', .next_state = 2 },
    { .state = 2, .character = 'a', .next_state = 3 }
  );

  nfa = NFA_create(
    (unsigned int[MAX_STATES]){1,2,0},
    (unsigned int[MAX_STATES]){3,4,0},
    rulebook);

  mu_assert(!NFA_accepting(nfa), "NFA accepting at states 1 and 2.");

  NFA_read_string(nfa, "a");

  mu_assert(NFA_accepting(nfa), "NFA not accepting at state 3.");

  Rulebook_destroy(rulebook);
  return NULL;
}

char *test_nfa_accepting_with_free_moves() {
  Rulebook_build(
    { .state = 1, .character = '\0', .next_state = 2 }
  );

  nfa = NFA_create(
    (unsigned int[MAX_STATES]){1,0},
    (unsigned int[MAX_STATES]){2,0},
    rulebook);

  mu_assert(NFA_accepting(nfa), "NFA not accepting at freely achieved state 4.");

  Rulebook_destroy(rulebook);
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
