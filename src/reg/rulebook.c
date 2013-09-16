#include <stdlib.h>
#include <string.h>
#include <reg/rulebook.h>
#include <reg/automaton.h>

Rulebook*
Rulebook_create()
{
  Rulebook *rulebook = calloc(1, sizeof(Rulebook));
  return rulebook;
}

void
Rulebook_add_rule(Rulebook *rulebook, FARule *rule) {
  rulebook->rules[rulebook->count] = rule;
  rulebook->count++;
}

static inline FARule*
Rulebook_rule_for(Rulebook *rulebook, unsigned int state, char character)
{
  for(int i=0; i < rulebook->count; i++) {
    FARule *rule = rulebook->rules[i];
    if(FARule_applies_to(rule, state, character)) {
      return rule;
    }
  }
  return NULL;
}

unsigned int 
Rulebook_next_state(Rulebook *rulebook, unsigned int state, char character)
{
  unsigned int next_state = UNDEFINED;
  FARule *rule = Rulebook_rule_for(rulebook, state, character);

  if(rule) next_state = FARule_follow(rule);

  return next_state;
}

unsigned int*
Rulebook_next_states(Rulebook *rulebook, unsigned int states[], char character)
{
  unsigned int *next_states = calloc(MAX_STATES, sizeof(unsigned int));
  unsigned int state = UNDEFINED;

  NFA_states_foreach(states, i, {
    state = Rulebook_next_state(rulebook, states[i], character);
    next_states[state] = state;
  })

  return next_states;
}

unsigned int*
Rulebook_follow_free_moves(Rulebook *rulebook, unsigned int states[])
{
  unsigned int *more_states = Rulebook_next_states(rulebook, states, FREE_MOVE);

  NFA_states_foreach(states, i, {
    more_states[i] = states[i];
  })

  return more_states;
}

