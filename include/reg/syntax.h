#ifndef _LIBREG_SYNTAX_H_
#define _LIBREG_SYNTAX_H_

#include <reg/automaton.h>

typedef enum {
  AST_EMPTY = 0,
  AST_LITERAL,
  AST_CONCATENATE,
  AST_CHOOSE,
  AST_REPEAT,
} ASTType;

typedef struct ASTNode_s {
  ASTType type;
  unsigned int precedence;
} ASTNode;

typedef struct ASTEmpty_s {
  ASTNode node;
} ASTEmpty;

typedef struct ASTLiteral_s {
  ASTNode node;
  char character;
} ASTLiteral;

typedef struct ASTConcatenate_s {
  ASTNode node;
  ASTNode *first;
  ASTNode *second;
} ASTConcatenate;

typedef struct ASTChoose_s {
  ASTNode node;
  ASTNode *first;
  ASTNode *second;
} ASTChoose;

typedef struct ASTRepeat_s {
  ASTNode node;
  ASTNode *pattern;
} ASTRepeat;

void ASTNode_destroy(ASTNode *node);
ASTEmpty* ASTEmpty_create();
ASTLiteral* ASTLiteral_create(char character);
ASTConcatenate* ASTConcatenate_create(ASTNode *first, ASTNode *second);
ASTChoose* ASTChoose_create(ASTNode *first, ASTNode *second);
ASTRepeat* ASTRepeat_create(ASTNode *pattern);

NFA* ASTNode_to_nfa(ASTNode *node);
NFA* ASTEmpty_to_nfa(ASTEmpty *node);
NFA* ASTLiteral_to_nfa(ASTLiteral *node);
NFA* ASTConcatenate_to_nfa(ASTConcatenate *node);
NFA* ASTChoose_to_nfa(ASTChoose *node);

#endif
