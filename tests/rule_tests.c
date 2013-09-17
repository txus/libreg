#include "minunit.h"
#include "rulebook_util.h"
#include <reg/rule.h>
#include <reg/rulebook.h>

static FARule *rule = NULL;
static Rulebook *rulebook = NULL;

char *test_applies_to() {
  mu_assert(FARule_applies_to(rule, STATE(rulebook, 1), 'a'), "Rule doesn't apply.");
  mu_assert(!FARule_applies_to(rule, STATE(rulebook, 1), 'b'), "Rule does apply with the wrong char.");
  mu_assert(!FARule_applies_to(rule, STATE(rulebook, 2), 'a'), "Rule does apply with the wrong state.");
  return NULL;
}

char *test_follow() {
  mu_assert(FARule_follow(rule) == STATE(rulebook, 2), "Rule doesn't follow to the next state.");
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  Rulebook_build(
    { .state = 1, .character = 'a', .next_state = 2 }
  );
  rule = rulebook->rules[0];

  mu_run_test(test_applies_to);
  mu_run_test(test_follow);

  Rulebook_destroy(rulebook);

  return NULL;
}

RUN_TESTS(all_tests);