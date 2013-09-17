#include <stdlib.h>
#include <reg/automaton.h>

unsigned int
DFA_accepting(DFA *dfa)
{
  Set_foreach(dfa->accept_states, state, {
    if(state == dfa->current_state) return 1;
  })
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
DFA_create(unsigned int current_state, Set *accept_states, Rulebook *rulebook)
{
  DFA *automaton           = calloc(1, sizeof(DFA));
  automaton->current_state = current_state;
  automaton->accept_states = accept_states;
  automaton->rulebook      = rulebook;
  return automaton;
}

void
DFA_destroy(DFA *dfa)
{
  Set_destroy(dfa->accept_states);
  Rulebook_destroy(dfa->rulebook);
  free(dfa);
}

NFA*
NFA_create(Set *current_states, Set *accept_states, Rulebook *rulebook)
{
  NFA *automaton = calloc(1, sizeof(NFA));
  automaton->current_states = current_states;
  automaton->accept_states = accept_states;
  automaton->rulebook = rulebook;
  return automaton;
}

void
NFA_destroy(NFA *nfa)
{
  Set_destroy(nfa->current_states);
  Set_destroy(nfa->accept_states);
  Rulebook_destroy(nfa->rulebook);
  free(nfa);
}

unsigned int
NFA_accepting(NFA *nfa)
{
  Set *current_states = Rulebook_follow_free_moves(
    nfa->rulebook,
    nfa->current_states
    );

  Set_foreach(current_states, cur, {
    Set_foreach(nfa->accept_states, acc, {
      if(cur == acc)  {
        Set_destroy(current_states);
        return 1;
      }
    })
  })

  Set_destroy(current_states);
  return 0;
}

void
NFA_read_character(NFA *nfa, char character)
{
  Set *old_states = nfa->current_states;
  Set *new_states = Rulebook_next_states(nfa->rulebook, nfa->current_states, character);

  nfa->current_states = new_states;
  Set_destroy(old_states);
}

void
NFA_read_string(NFA *nfa, char *string)
{
  char ch;
  char *ptr = string;
  while((ch = *ptr++)) NFA_read_character(nfa, ch);
}
