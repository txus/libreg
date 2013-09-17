#ifndef _LIBREG_SYNTAX_H_
#define _LIBREG_SYNTAX_H_

typedef enum {
  AST_EMPTY = 0,
  AST_LITERAL,
  AST_CONCATENATE,
  AST_CHOOSE,
  AST_REPEAT,
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

typedef struct AST_Concatenate_s {
  AST_Node node;
  AST_Node *first;
  AST_Node *second;
} AST_Concatenate;

typedef struct AST_Choose_s {
  AST_Node node;
  AST_Node *first;
  AST_Node *second;
} AST_Choose;

typedef struct AST_Repeat_s {
  AST_Node node;
  AST_Node *pattern;
} AST_Repeat;

AST_Empty* AST_Empty_create();
AST_Literal* AST_Literal_create(char character);
AST_Concatenate* AST_Concatenate_create(AST_Node *first, AST_Node *second);
AST_Choose* AST_Choose_create(AST_Node *first, AST_Node *second);
AST_Repeat* AST_Repeat_create(AST_Node *pattern);

#endif
