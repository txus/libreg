#include "minunit.h"
#include <reg/syntax.h>

char *test_empty() {
  ASTEmpty *node = ASTEmpty_create();
  NFA *nfa = ASTNode_to_nfa((ASTNode*)node);

  mu_assert(NFA_accepting(nfa), "Empty NFA is not accepting.");

  NFA_destroy(nfa);
  ASTNode_destroy((ASTNode*)node);
  return NULL;
}

char *test_literal() {
  ASTLiteral *node = ASTLiteral_create('a');
  NFA *nfa = ASTNode_to_nfa((ASTNode*)node);

  mu_assert(!NFA_accepting(nfa), "Literal NFA is accepting before it should.");

  NFA_read_character(nfa, 'a');

  mu_assert(NFA_accepting(nfa), "Literal NFA is not accepting.");

  NFA_destroy(nfa);
  ASTNode_destroy((ASTNode*)node);
  return NULL;
}

char *test_concatenate() {
  ASTLiteral *a = ASTLiteral_create('a');
  ASTLiteral *b = ASTLiteral_create('b');
  ASTConcatenate *node = ASTConcatenate_create((ASTNode*)a, (ASTNode*)b);

  NFA *nfa = ASTNode_to_nfa((ASTNode*)node);

  mu_assert(!NFA_accepting(nfa), "Concatenate NFA is accepting before it should (first step).");

  NFA_read_character(nfa, 'a');
  mu_assert(!NFA_accepting(nfa), "Concatenate NFA is accepting before it should (second step).");

  NFA_read_character(nfa, 'b');
  mu_assert(NFA_accepting(nfa), "Concatenate NFA is not accepting.");

  NFA_destroy(nfa);
  ASTNode_destroy((ASTNode*)node);
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_empty);
  mu_run_test(test_literal);
  mu_run_test(test_concatenate);

  return NULL;
}

RUN_TESTS(all_tests);
