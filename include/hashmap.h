#ifndef HashMap_h
#define HashMap_h

typedef struct HashMap HashMap;

typedef struct Pair {
  char *key;
  void *value;
} Pair;

HashMap *createMap(long capacity);

void insertMap(HashMap *table, char *key, void *value);

void eraseMap(HashMap *table, char *key);

Pair *searchMap(HashMap *table, char *key);

Pair *firstMap(HashMap *table);

Pair *nextMap(HashMap *table);

void enlarge(HashMap *map);

long sizeMap(HashMap *jugadores);

void *valueRet(Pair *key_value);

#endif /* HashMap_h */