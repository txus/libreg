#ifndef _LIBREG_AUTOMATON_H_
#define _LIBREG_AUTOMATON_H_

#include <reg/rulebook.h>

typedef struct DFA_s {
  unsigned int current_state;
  unsigned int accept_states[MAX_STATES];
  Rulebook *rulebook;
} DFA;

DFA* DFA_create(unsigned int current_state, unsigned int accept_states[], Rulebook *rulebook);
unsigned int DFA_accepting(DFA *dfa);
void DFA_read_character(DFA *dfa, char character);
void DFA_read_string(DFA *dfa, char *string);
#define DFA_destroy(A) (free(A))

#define NFA_states_foreach(S, I, C) \
  for(int I=1; I < MAX_STATES; I++) { \
    if(S[I] == UNDEFINED) continue; \
    C \
  }

typedef struct NFA_s {
  unsigned int current_states[MAX_STATES];
  unsigned int accept_states[MAX_STATES];
  Rulebook *rulebook;
} NFA;

NFA* NFA_create(unsigned int current_states[], unsigned int accept_states[], Rulebook *rulebook);
unsigned int NFA_accepting(NFA *nfa);
void NFA_read_character(NFA *nfa, char character);
void NFA_read_string(NFA *nfa, char *string);
#define NFA_destroy(A) (free(A))

#endif
