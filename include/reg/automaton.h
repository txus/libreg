#ifndef _LIBREG_AUTOMATON_H_
#define _LIBREG_AUTOMATON_H_

#include <reg/rulebook.h>

typedef struct DFA_s {
  unsigned int current_state;
  unsigned int accept_states[100];
  DFARulebook *rulebook;
} DFA;

DFA* DFA_create(unsigned int current_state, unsigned int accept_states[], DFARulebook *rulebook);
unsigned int DFA_accepting(DFA *dfa);
void DFA_read_character(DFA *dfa, char character);
#define DFA_destroy(A) (free(A))

#endif
