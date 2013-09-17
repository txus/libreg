#include <stdlib.h>
#include <reg/syntax.h>

AST_Empty*
AST_Empty_create()
{
  AST_Empty *empty = calloc(1, sizeof(AST_Empty));
  empty->node.type = AST_EMPTY;
  empty->node.precedence = 3;
  return empty;
}

AST_Literal*
AST_Literal_create(char character)
{
  AST_Literal *literal = calloc(1, sizeof(AST_Literal));
  literal->node.type = AST_LITERAL;
  literal->node.precedence = 3;
  literal->character = character;
  return literal;
}
