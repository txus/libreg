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

  mu_assert(node->type == AST_LITERAL, "Didn't get literal node.");

  ASTLiteral *literal  = (ASTLiteral*)node;

  mu_assert(literal->character == 'a', "Didn't get 'a' literal.");

  ASTNode_destroy(node);
  return NULL;
}

char *test_parse_concatenate() {
  ASTNode *node = parse("ab");

  mu_assert(node->type == AST_CONCATENATE, "Didn't get concatenate node.");

  ASTConcatenate *concat    = (ASTConcatenate*)node;

  mu_assert(concat->first->type == AST_LITERAL, "First is not a literal.");
  mu_assert(concat->second->type == AST_LITERAL, "Second is not a literal.");

  ASTLiteral     *first     = (ASTLiteral*)concat->first;
  ASTLiteral     *second     = (ASTLiteral*)concat->second;
  mu_assert(first->character == 'a', "First character is not an 'a'.");
  mu_assert(second->character == 'b', "Second character is not a 'b'.");

  ASTNode_destroy(node);
  return NULL;
}

char *test_parse_concatenate_multiple() {
  ASTNode *node = parse("abc");

  mu_assert(node->type == AST_CONCATENATE, "Didn't get concatenate node.");

  ASTConcatenate *concat    = (ASTConcatenate*)node;

  mu_assert(concat->first->type == AST_LITERAL, "First is not a literal.");
  mu_assert(concat->second->type == AST_CONCATENATE, "Second is not a concatenate.");

  ASTLiteral *first = (ASTLiteral*)concat->first;
  mu_assert(first->character == 'a', "First character is not an 'a'.");

  ASTConcatenate *second = (ASTConcatenate*)concat->second;
  mu_assert(second->first->type == AST_LITERAL, "Subfirst is not a literal.");
  mu_assert(second->second->type == AST_LITERAL, "Subfirst is not a literal.");

  ASTLiteral *subfirst = (ASTLiteral*)second->first;
  ASTLiteral *subsecond = (ASTLiteral*)second->second;
  mu_assert(subfirst->character == 'b', "Subfirst character is not a 'b'.");
  mu_assert(subsecond->character == 'c', "Subsecond character is not a 'c'.");

  ASTNode_destroy(node);
  return NULL;
}

char *test_parse_choose() {
  ASTNode *node = parse("a|b");

  mu_assert(node->type == AST_CHOOSE, "Didn't get choose node.");

  ASTChoose *choose = (ASTChoose*)node;

  mu_assert(choose->first->type  == AST_LITERAL, "First is not a literal.");
  mu_assert(choose->second->type == AST_LITERAL, "Second is not a literal.");

  ASTLiteral *a  = (ASTLiteral*)choose->first;
  ASTLiteral *b  = (ASTLiteral*)choose->second;

  mu_assert(a->character == 'a', "first character is not 'a'.");
  mu_assert(b->character == 'b', "second character is not 'b'.");

  ASTNode_destroy(node);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_parse_empty);
  mu_run_test(test_parse_literal);
  mu_run_test(test_parse_concatenate);
  mu_run_test(test_parse_concatenate_multiple);
  mu_run_test(test_parse_choose);

  return NULL;
}

RUN_TESTS(all_tests);
