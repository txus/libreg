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

ASTEmpty* ASTEmpty_create();
ASTLiteral* ASTLiteral_create(char character);
ASTConcatenate* ASTConcatenate_create(ASTNode *first, ASTNode *second);
ASTChoose* ASTChoose_create(ASTNode *first, ASTNode *second);
ASTRepeat* ASTRepeat_create(ASTNode *pattern);

NFA* ASTEmpty_to_nfa(ASTEmpty *empty);

#endif
