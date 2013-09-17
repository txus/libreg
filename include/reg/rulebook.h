#ifndef _LIBREG_RULEBOOK_H_
#define _LIBREG_RULEBOOK_H_

#include <reg/set.h>
#include <reg/rule.h>
#define MAX_RULES 100

typedef struct Rulebook_s {
  FARule *rules[MAX_RULES];
  unsigned int count;
} Rulebook;

Rulebook* Rulebook_create();
void Rulebook_add_rule(Rulebook *rulebook, FARule *rule);
unsigned int Rulebook_next_state(Rulebook *rulebook, unsigned int state, char character);
#define Rulebook_destroy(R) (free(R))
Set* Rulebook_next_states(Rulebook *rulebook, Set *states, char character);
Set* Rulebook_follow_free_moves(Rulebook *rulebook, Set *states);

#endif
