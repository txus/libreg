#define DFARulebook_build(...) {                       \
  FARule rules[] = (FARule[]) {__VA_ARGS__};           \
  unsigned short count = sizeof(rules)/sizeof(FARule); \
  rulebook = DFARulebook_create();                     \
  for(int i=0; i < count; i++) {                       \
    DFARulebook_add_rule(rulebook, &rules[i]);         \
  }                                                    \
}

