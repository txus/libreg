#include <stdlib.h>
#include <stdio.h>
#include <reg/rulebook.h>
#include <reg/automaton.h>

Rulebook*
Rulebook_create()
{
  Rulebook *rulebook = calloc(1, sizeof(Rulebook));
  return rulebook;
}

void
Rulebook_destroy(Rulebook *rulebook)
{
  for(int i=0; i < rulebook->count; i++) {
    FARule_destroy(rulebook->rules[i]);
  }
  free(rulebook);
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

Set*
Rulebook_next_states(Rulebook *rulebook, Set *states, char character)
{
  Set *next_states = Set_create();
  unsigned int state = UNDEFINED;

  Set_foreach(states, st, {
    state = Rulebook_next_state(rulebook, st, character);
    Set_push(next_states, state);
  })

  return next_states;
}

Set*
Rulebook_follow_free_moves(Rulebook *rulebook, Set *states)
{
  Set *more_states = Rulebook_next_states(rulebook, states, FREE_MOVE);

  Set_foreach(states, st, {
    Set_push(more_states, st);
  })

  return more_states;
}

