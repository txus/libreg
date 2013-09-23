#include "minunit.h"
#include <reg/parser.h>

char *test_parse_empty() {
  ASTNode *node = parse("");

  mu_assert(node->type == AST_EMPTY, "Didn't get empty node.");

  ASTNode_destroy(node);
  return NULL;
}

char *test_parse_literal() {
  ASTNode *node = parse("a");

  mu_assert(node->type == AST_CONCATENATE, "Didn't get concatenate node.");

  ASTConcatenate *concat = (ASTConcatenate*)node;
  ASTLiteral     *first  = (ASTLiteral*)concat->first;
  ASTEmpty       *second = (ASTEmpty*)concat->second;

  mu_assert(first->character == 'a', "Didn't get 'a' literal.");
  mu_assert(second->node.type == AST_EMPTY, "Didn't get empty node second.");

  ASTNode_destroy(node);
  return NULL;
}

char *test_parse_concatenate() {
  ASTNode *node = parse("ab");

  mu_assert(node->type == AST_CONCATENATE, "Didn't get concatenate node.");

  ASTConcatenate *concat    = (ASTConcatenate*)node;

  mu_assert(concat->first->type == AST_LITERAL, "First is not a literal.");
  mu_assert(concat->second->type == AST_CONCATENATE, "Second is not a concat.");

  ASTLiteral     *first     = (ASTLiteral*)concat->first;
  ASTConcatenate *second    = (ASTConcatenate*)concat->second;
  mu_assert(first->character == 'a', "First character is not an 'a'.");

  mu_assert(second->first->type == AST_LITERAL, "Subfirst is not a literal.");
  mu_assert(second->second->type == AST_EMPTY, "Subsecond is not an empty.");

  ASTLiteral *subfirst  = (ASTLiteral*)second->first;

  mu_assert(subfirst->character == 'b', "Subfirst character is not an 'b'.");

  ASTNode_destroy(node);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_parse_empty);
  mu_run_test(test_parse_literal);
  mu_run_test(test_parse_concatenate);

  return NULL;
}

RUN_TESTS(all_tests);
