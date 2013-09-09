#include <stdlib.h>
#include <reg/rule.h>

FARule*
FARule_create(unsigned int state, char character, unsigned int next_state)
{
  FARule *rule     = calloc(1, sizeof(FARule));
  rule->state      = state;
  rule->character  = character;
  rule->next_state = next_state;
  return rule;
}
