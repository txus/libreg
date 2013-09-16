#ifndef _LIBREG_RULEBOOK_H_
#define _LIBREG_RULEBOOK_H_

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
unsigned int* Rulebook_next_states(Rulebook *rulebook, unsigned int states[], char character);
unsigned int* Rulebook_follow_free_moves(Rulebook *rulebook, unsigned int states[]);

#endif
