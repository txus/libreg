#include <stdlib.h>
#include <reg/set.h>
#include <reg/syntax.h>

ASTEmpty*
ASTEmpty_create()
{
  ASTEmpty *node = calloc(1, sizeof(ASTEmpty));
  node->node.type = AST_EMPTY;
  node->node.precedence = 3;
  return node;
}

ASTLiteral*
ASTLiteral_create(char character)
{
  ASTLiteral *node = calloc(1, sizeof(ASTLiteral));
  node->node.type = AST_LITERAL;
  node->node.precedence = 3;
  node->character = character;
  return node;
}

ASTConcatenate*
ASTConcatenate_create(ASTNode *first, ASTNode *second)
{
  ASTConcatenate *node = calloc(1, sizeof(ASTConcatenate));
  node->node.type = AST_CONCATENATE;
  node->node.precedence = 1;
  node->first = first;
  node->second = second;
  return node;
}

ASTChoose*
ASTChoose_create(ASTNode *first, ASTNode *second)
{
  ASTChoose *node = calloc(1, sizeof(ASTChoose));
  node->node.type = AST_CHOOSE;
  node->node.precedence = 0;
  node->first = first;
  node->second = second;
  return node;
}

ASTRepeat*
ASTRepeat_create(ASTNode *pattern)
{
  ASTRepeat *node = calloc(1, sizeof(ASTRepeat));
  node->node.type = AST_REPEAT;
  node->node.precedence = 2;
  node->pattern = pattern;
  return node;
}

NFA*
ASTEmpty_to_nfa(ASTEmpty *empty)
{
  Rulebook *rulebook = Rulebook_create();
  Set *current_states = Set_create();
  Set *accept_states = Set_create();

  Set_push(current_states, STATE(rulebook, 1));
  Set_push(accept_states, STATE(rulebook, 1));

  NFA *nfa = NFA_create(current_states, accept_states, rulebook);

  return nfa;
}
