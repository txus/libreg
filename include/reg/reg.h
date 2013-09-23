#ifndef _LIBREG_REG_H_
#define _LIBREG_REG_H_

#include <reg/automaton.h>

typedef NFA Reg;

Reg* Reg_compile(char *regexp);
unsigned int Reg_match(Reg *reg, char *string);
#define Reg_destroy NFA_destroy

#endif
