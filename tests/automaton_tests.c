#include "minunit.h"
#include "rulebook_util.h"
#include <reg/automaton.h>

static DFARulebook *rulebook = NULL;
static DFA *dfa = NULL;

char *test_accepting() {
  mu_assert(!DFA_accepting(dfa), "DFA accepting at state 1.");
  DFA_read_character(dfa, 'a');
  mu_assert(!DFA_accepting(dfa), "DFA accepting at state 2.");
  DFA_read_character(dfa, 'b');
  mu_assert(DFA_accepting(dfa), "DFA not accepting at state 3.");

  dfa->current_state = 1; // reset

  DFA_read_string(dfa, "ab");
  mu_assert(DFA_accepting(dfa), "DFA not accepting at state 3.");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  DFARulebook_build(
    { .state = 1, .character = 'a', .next_state = 2 },
    { .state = 2, .character = 'b', .next_state = 3 }
  );

  dfa = DFA_create(1, (unsigned int[]){3, 0}, rulebook);

  mu_run_test(test_accepting);

  DFARulebook_destroy(rulebook);
  DFA_destroy(dfa);

  return NULL;
}

RUN_TESTS(all_tests);
