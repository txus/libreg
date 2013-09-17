#include <stdlib.h>
#include <reg/rule.h>
#include <reg/rulebook.h>

FARule*
FARule_create(Rulebook *rulebook, unsigned int state, char character, unsigned int next_state)
{
  FARule *rule     = calloc(1, sizeof(FARule));
  rule->state      = STATE(rulebook, state);
  rule->character  = character;
  rule->next_state = STATE(rulebook, next_state);
  return rule;
}
