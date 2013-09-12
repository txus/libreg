#define Rulebook_build(...) {                       \
  FARule rules[] = (FARule[]) {__VA_ARGS__};           \
  unsigned short count = sizeof(rules)/sizeof(FARule); \
  rulebook = Rulebook_create();                     \
  for(int i=0; i < count; i++) {                       \
    Rulebook_add_rule(rulebook, &rules[i]);         \
  }                                                    \
}

