#ifndef _LIBREG_SET_H_
#define _LIBREG_SET_H_

#include <reg/khash.h>

KHASH_MAP_INIT_INT(32, unsigned int)

typedef khash_t(32) Set;

#define Set_create() kh_init(32)
#define Set_foreach(S, V, C) \
  { \
    khiter_t k; \
    unsigned int V; \
    for(k = kh_begin((S)); k != kh_end((S)); ++k) { \
      if (kh_exist((S), k)) { \
        V = kh_value((S), k); \
        C \
      } \
    }\
  }

unsigned int Set_member(Set *set, unsigned int value);
#define Set_remove(S, K) kh_del(32, (S), (K))
#define Set_destroy(S) kh_destroy(32, (S))

void Set_push(Set *set, unsigned int value);

#endif
