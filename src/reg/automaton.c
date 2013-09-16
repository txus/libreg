#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

NFA*
NFA_create(unsigned int current_states[], unsigned int accept_states[], Rulebook *rulebook)
{
  NFA *automaton = calloc(1, sizeof(NFA));

  for(int i=0; i < MAX_STATES; i++) {
    automaton->current_states[current_states[i]] = current_states[i];
    automaton->accept_states[accept_states[i]] = accept_states[i];
  }

  automaton->rulebook = rulebook;
  return automaton;
}

unsigned int
NFA_accepting(NFA *nfa)
{
  NFA_states_foreach(nfa->current_states, i, {
    NFA_states_foreach(nfa->accept_states, j, {
      if(nfa->current_states[i] == nfa->accept_states[j]) return 1;
    })
  })

  return 0;
}

void
NFA_read_character(NFA *nfa, char character)
{
  unsigned int *old_states = nfa->current_states;
  unsigned int *new_states = Rulebook_next_states(nfa->rulebook, nfa->current_states, character);

  NFA_states_foreach(new_states, i, {
    old_states[i] = UNDEFINED;
    old_states[new_states[i]] = new_states[i];
  })

  free(new_states);
}

void
NFA_read_string(NFA *nfa, char *string)
{
  char ch;
  char *ptr = string;
  while((ch = *ptr++)) NFA_read_character(nfa, ch);
}
