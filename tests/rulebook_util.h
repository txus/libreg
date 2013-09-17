#define Rulebook_build(...) {                       \
  rulebook = Rulebook_create();                     \
  FARule rules[] = (FARule[]) {__VA_ARGS__};           \
  unsigned short count = sizeof(rules)/sizeof(FARule); \
  for(int i=0; i < count; i++) {                       \
    FARule *rule = FARule_create( \
      rulebook, \
      rules[i].state, \
      rules[i].character, \
      rules[i].next_state); \
    Rulebook_add_rule(rulebook, rule);         \
  }                                                    \
}

