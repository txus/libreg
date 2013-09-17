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

void
ASTNode_destroy(ASTNode *node)
{
  switch(node->type) {
  case AST_EMPTY: free(node); break;
  case AST_LITERAL: free(node); break;
  case AST_CONCATENATE:
                    ASTNode_destroy(((ASTConcatenate*)node)->first);
                    ASTNode_destroy(((ASTConcatenate*)node)->second);
                    free(node);
                    break;
  case AST_CHOOSE:
                    ASTNode_destroy(((ASTChoose*)node)->first);
                    ASTNode_destroy(((ASTChoose*)node)->second);
                    free(node);
                    break;
  case AST_REPEAT:
                    ASTNode_destroy(((ASTRepeat*)node)->pattern);
                    free(node);
                    break;
  }
}

NFA*
ASTNode_to_nfa(ASTNode *node)
{
  switch(node->type) {
  case AST_EMPTY: return ASTEmpty_to_nfa((ASTEmpty*)node);
  case AST_LITERAL: return ASTLiteral_to_nfa((ASTLiteral*)node);
  case AST_CONCATENATE: return ASTConcatenate_to_nfa((ASTConcatenate*)node);
  case AST_CHOOSE: return ASTChoose_to_nfa((ASTChoose*)node);
  default: return NULL;
  }
}

NFA*
ASTEmpty_to_nfa(ASTEmpty *node)
{
  Rulebook *rulebook = Rulebook_create();
  Set *current_states = Set_create();
  Set *accept_states = Set_create();

  Set_push(current_states, STATE(rulebook, 1));
  Set_push(accept_states, STATE(rulebook, 1));

  return NFA_create(current_states, accept_states, rulebook);
}

NFA*
ASTLiteral_to_nfa(ASTLiteral *node)
{
  Rulebook *rulebook = Rulebook_create();
  Set *current_states = Set_create();
  Set *accept_states = Set_create();

  Set_push(current_states, STATE(rulebook, 1));
  Set_push(accept_states, STATE(rulebook, 2));
  Rulebook_add_rule(rulebook, FARule_create(rulebook, STATE(rulebook, 1), node->character, STATE(rulebook, 2)));

  return NFA_create(current_states, accept_states, rulebook);
}

NFA*
ASTConcatenate_to_nfa(ASTConcatenate *node)
{
  Rulebook *rulebook = Rulebook_create();
  Set *current_states = Set_create();
  Set *accept_states = Set_create();

  NFA *first = ASTNode_to_nfa(node->first);
  NFA *second = ASTNode_to_nfa(node->second);

  Set_foreach(first->current_states, state, {
    Set_push(current_states, state);
  })

  Set_foreach(second->accept_states, state, {
    Set_push(accept_states, state);
  })

  unsigned int second_start_state = UNDEFINED;
  Set_foreach(second->current_states, state, {
    second_start_state = state; // there's only one
  })

  Set_foreach(first->accept_states, state, {
    Rulebook_add_rule(
      rulebook,
      FARule_create(
        rulebook,
        state,
        FREE_MOVE,
        second_start_state
      )
    );
  })

  for(int i=0; i < first->rulebook->count; i++) {
    FARule *r = first->rulebook->rules[i];
    Rulebook_add_rule(
      rulebook,
      FARule_create(
        rulebook,
        r->state,
        r->character,
        r->next_state
        )
      );
  }

  for(int i=0; i < second->rulebook->count; i++) {
    FARule *r = second->rulebook->rules[i];
    Rulebook_add_rule(
      rulebook,
      FARule_create(
        rulebook,
        r->state,
        r->character,
        r->next_state
        )
      );
  }

  NFA_destroy(first);
  NFA_destroy(second);

  return NFA_create(current_states, accept_states, rulebook);
}

NFA*
ASTChoose_to_nfa(ASTChoose *node)
{
  Rulebook *rulebook = Rulebook_create();
  Set *current_states = Set_create();
  Set *accept_states = Set_create();

  NFA *first = ASTNode_to_nfa(node->first);
  NFA *second = ASTNode_to_nfa(node->second);

  Set_push(current_states, STATE(rulebook, 1));

  Set_foreach(first->current_states, state, {
    Rulebook_add_rule(
      rulebook,
      FARule_create(
        rulebook,
        STATE(rulebook, 1),
        FREE_MOVE,
        state
      )
    );
  })

  Set_foreach(second->current_states, state, {
    Rulebook_add_rule(
      rulebook,
      FARule_create(
        rulebook,
        STATE(rulebook, 1),
        FREE_MOVE,
        state
      )
    );
  })

  Set_foreach(first->accept_states, state, {
    Set_push(accept_states, state);
  })

  Set_foreach(second->accept_states, state, {
    Set_push(accept_states, state);
  })

  for(int i=0; i < first->rulebook->count; i++) {
    FARule *r = first->rulebook->rules[i];
    Rulebook_add_rule(
      rulebook,
      FARule_create(
        rulebook,
        r->state,
        r->character,
        r->next_state
        )
      );
  }

  for(int i=0; i < second->rulebook->count; i++) {
    FARule *r = second->rulebook->rules[i];
    Rulebook_add_rule(
      rulebook,
      FARule_create(
        rulebook,
        r->state,
        r->character,
        r->next_state
        )
      );
  }

  NFA_destroy(first);
  NFA_destroy(second);

  return NFA_create(current_states, accept_states, rulebook);
}
