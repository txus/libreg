#include <stdlib.h>
#include <reg/rulebook.h>

DFARulebook*
DFARulebook_create()
{
  DFARulebook *rulebook = calloc(1, sizeof(DFARulebook));
  return rulebook;
}

void
DFARulebook_add_rule(DFARulebook *rulebook, FARule *rule) {
  rulebook->rules[rulebook->count] = rule;
  rulebook->count++;
}

static inline FARule*
DFARulebook_rule_for(DFARulebook *rulebook, unsigned int state, char character)
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
DFARulebook_next_state(DFARulebook *rulebook, unsigned int state, char character)
{
  unsigned int next_state = UNDEFINED;
  FARule *rule = DFARulebook_rule_for(rulebook, state, character);

  if(rule) next_state = FARule_follow(rule);

  return next_state;
}
