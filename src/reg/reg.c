#include <reg/reg.h>
#include <reg/parser.h>

Reg*
Reg_compile(char *regexp)
{
  ASTNode *root = parse(regexp);
  NFA *nfa = ASTNode_to_nfa(root);
  ASTNode_destroy(root);
  return nfa;
}

unsigned int
Reg_match(Reg *reg, char *string)
{
  NFA_reset(reg);
  NFA_read_string(reg, string);
  return NFA_accepting(reg);
}