#include <stdlib.h>
#include <reg/syntax.h>

AST_Empty*
AST_Empty_create()
{
  AST_Empty *node = calloc(1, sizeof(AST_Empty));
  node->node.type = AST_EMPTY;
  node->node.precedence = 3;
  return node;
}

AST_Literal*
AST_Literal_create(char character)
{
  AST_Literal *node = calloc(1, sizeof(AST_Literal));
  node->node.type = AST_LITERAL;
  node->node.precedence = 3;
  node->character = character;
  return node;
}

AST_Concatenate*
AST_Concatenate_create(AST_Node *first, AST_Node *second)
{
  AST_Concatenate *node = calloc(1, sizeof(AST_Concatenate));
  node->node.type = AST_CONCATENATE;
  node->node.precedence = 1;
  node->first = first;
  node->second = second;
  return node;
}

AST_Choose*
AST_Choose_create(AST_Node *first, AST_Node *second)
{
  AST_Choose *node = calloc(1, sizeof(AST_Choose));
  node->node.type = AST_CHOOSE;
  node->node.precedence = 0;
  node->first = first;
  node->second = second;
  return node;
}

AST_Repeat*
AST_Repeat_create(AST_Node *pattern)
{
  AST_Repeat *node = calloc(1, sizeof(AST_Repeat));
  node->node.type = AST_REPEAT;
  node->node.precedence = 2;
  node->pattern = pattern;
  return node;
}
