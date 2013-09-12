#ifndef _LIBREG_RULEBOOK_H_
#define _LIBREG_RULEBOOK_H_

#include <reg/rule.h>

typedef struct Rulebook_s {
  FARule *rules[100];
  unsigned int count;
} Rulebook;

Rulebook* Rulebook_create();
void Rulebook_add_rule(Rulebook *rulebook, FARule *rule);
unsigned int Rulebook_next_state(Rulebook *rulebook, unsigned int state, char character);
#define Rulebook_destroy(R) (free(R))

#endif
