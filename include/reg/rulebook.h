#ifndef _LIBREG_RULEBOOK_H_
#define _LIBREG_RULEBOOK_H_

#include <reg/rule.h>

typedef struct DFARulebook_s {
  FARule *rules[100];
  unsigned int count;
} DFARulebook;

DFARulebook* DFARulebook_create();
void DFARulebook_add_rule(DFARulebook *rulebook, FARule *rule);
unsigned int DFARulebook_next_state(DFARulebook *rulebook, unsigned int state, char character);
#define DFARulebook_destroy(R) (free(R))

#endif
