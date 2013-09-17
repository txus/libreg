#include "minunit.h"
#include <reg/set.h>

Set *set = NULL;

char *test_push() {
  Set *set = Set_create();

  Set_push(set, 138904);
  Set_push(set, 138904);
  Set_push(set, 138904);

  unsigned int count = 0;
  unsigned int val = 0;

  Set_foreach(set, value, {
    count++;
    val = value;
  })

  mu_assert(count == 1, "Set pushed more than one number.");
  mu_assert(val == 138904, "Setforeach didn't yield the expected value.");
  mu_assert(Set_member(set, 138904), "Set doesnt have the member.");
  mu_assert(!Set_member(set, 138913), "Set has more members.");

  Set_destroy(set);

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_push);

  return NULL;
}

RUN_TESTS(all_tests);
