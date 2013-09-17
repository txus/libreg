#define Rulebook_build(...) {                       \
  rulebook = Rulebook_create();                     \
  FARule rules[] = (FARule[]) {__VA_ARGS__};           \
  unsigned short count = sizeof(rules)/sizeof(FARule); \
  for(int i=0; i < count; i++) {                       \
    Rulebook_add_rule(rulebook, &rules[i]);         \
  }                                                    \
}

