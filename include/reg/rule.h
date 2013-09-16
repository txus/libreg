#ifndef _LIBREG_RULE_H_
#define _LIBREG_RULE_H_

#define UNDEFINED 0
#define FREE_MOVE '\0'
#define MAX_STATES 100

typedef struct FARule_s {
  unsigned int state;
  char character;
  unsigned int next_state;
} FARule;

FARule* FARule_create(unsigned int state, char character, unsigned int next_state);
#define FARule_applies_to(R, S, C) ((R)->state == (S) && (R)->character == (C))
#define FARule_follow(R) ((R)->next_state)
#define FARule_destroy(R) (free(R))

#endif
