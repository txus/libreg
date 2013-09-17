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
  mu_assert(((ASTLiteral*)node)->character == 'a', "Didn't get 'a' as literal.");

  ASTNode_destroy(node);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_parse_empty);
  mu_run_test(test_parse_literal);

  return NULL;
}

RUN_TESTS(all_tests);
