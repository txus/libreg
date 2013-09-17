#include <reg/set.h>

void
Set_push(Set *set, unsigned int value)
{
  int ret;
  khiter_t k;
  unsigned int key = value;
  k = kh_put(32, set, key, &ret);
  kh_value(set, k) = value;
}

unsigned int
Set_member(Set *set, unsigned int value)
{
  khiter_t k = kh_get(32, set, value);
  return !(k == kh_end(set));
}
