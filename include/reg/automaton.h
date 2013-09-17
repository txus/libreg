#ifndef _LIBREG_AUTOMATON_H_
#define _LIBREG_AUTOMATON_H_

#include <reg/set.h>
#include <reg/rulebook.h>

typedef struct DFA_s {
  unsigned int current_state;
  Set *accept_states;
  Rulebook *rulebook;
} DFA;

DFA* DFA_create(unsigned int current_state, Set *accept_states, Rulebook *rulebook);
unsigned int DFA_accepting(DFA *dfa);
void DFA_read_character(DFA *dfa, char character);
void DFA_read_string(DFA *dfa, char *string);
void DFA_destroy(DFA *dfa);

typedef struct NFA_s {
  Set *initial_states;
  Set *current_states;
  Set *accept_states;
  Rulebook *rulebook;
} NFA;

NFA* NFA_create(Set *initial_states, Set *accept_states, Rulebook *rulebook);
void NFA_reset(NFA *nfa);
unsigned int NFA_accepting(NFA *nfa);
void NFA_follow_free_moves(NFA *nfa);
void NFA_read_character(NFA *nfa, char character);
void NFA_read_string(NFA *nfa, char *string);
void NFA_destroy(NFA *nfa);

#endif
