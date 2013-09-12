#include <stdlib.h>
#include <reg/automaton.h>

unsigned int
DFA_accepting(DFA *dfa)
{
  for(int i=0; i < sizeof(&(dfa->accept_states)) / sizeof(unsigned int); i++) {
    if(dfa->accept_states[i] == dfa->current_state) {
      return 1;
    }
  }
  return 0;
}

void
DFA_read_character(DFA *dfa, char character)
{
  dfa->current_state = Rulebook_next_state(dfa->rulebook, dfa->current_state, character);
}

void
DFA_read_string(DFA *dfa, char *string)
{
  char ch;
  char *ptr = string;
  while((ch = *ptr++)) DFA_read_character(dfa, ch);
}

DFA*
DFA_create(unsigned int current_state, unsigned int accept_states[], Rulebook *rulebook)
{
  DFA *automaton           = calloc(1, sizeof(DFA));
  automaton->current_state = current_state;
  for(int i=0; i < (sizeof(&accept_states) / sizeof(unsigned int)); i++) {
    automaton->accept_states[i] = accept_states[i];
  }
  automaton->rulebook      = rulebook;
  return automaton;
}
