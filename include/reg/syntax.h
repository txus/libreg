#ifndef _LIBREG_SYNTAX_H_
#define _LIBREG_SYNTAX_H_

typedef enum {
  AST_EMPTY = 0,
  AST_LITERAL
} AST_Type;

typedef struct AST_Node_s {
  AST_Type type;
  unsigned int precedence;
} AST_Node;

typedef struct AST_Empty_s {
  AST_Node node;
} AST_Empty;

typedef struct AST_Literal_s {
  AST_Node node;
  char character;
} AST_Literal;

AST_Empty* AST_Empty_create();
AST_Literal* AST_Literal_create(char character);

#endif
