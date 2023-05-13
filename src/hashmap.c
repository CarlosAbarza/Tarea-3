#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  long indiceH = hash(key, map->capacity);
  Pair *aux = createPair(key, value);
  if (map->size / map->capacity > 0.7)
    enlarge(map);
  for (long i = 0; i < map->capacity;i++) {
    if (!map->buckets[indiceH] || !map->buckets[indiceH]->key) {
      map->buckets[indiceH] = aux;
      map->size++;
      map->current = indiceH;
      return;
    }
    if (is_equal(key, map->buckets[indiceH]->key))
      return;
    indiceH++;
    if (indiceH == map->capacity)
      indiceH = 0;
  }
  // enlarge(map);
  // insertMap(map, key, value);
}

void enlarge(HashMap * map) {
    // enlarge_called = 1; //no borrar (testing purposes)
  Pair **old_buckets = map->buckets;
  map->buckets = (Pair**) calloc(map->capacity*2, sizeof(Pair*));
  map->capacity *= 2;
  map->size = 0;
  map->current = -1;
  for (long i = 0; i < map->capacity/2; i++) {
    if (old_buckets[i]) {
      if (old_buckets[i]->key)
        insertMap(map, old_buckets[i]->key, old_buckets[i]->value);
    }
  }
}


HashMap * createMap(long capacity) {
  HashMap *local = (HashMap*) malloc(sizeof(HashMap));
  local->buckets = (Pair**) calloc(capacity, sizeof(Pair*));
  local->size = 0;
  local->capacity = capacity;
  local->current = -1;
  return local;
}

void eraseMap(HashMap * map,  char * key) {    
  if (searchMap(map, key)) {
    map->buckets[map->current]->key = NULL;
    map->size--;
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  long indiceH = hash(key, map->capacity);
  for (long i = 0; i < map->capacity;i++) {
    if (!map->buckets[indiceH])
      return NULL;
    else if (!map->buckets[indiceH]->key)
      return NULL;
    if (is_equal(key, map->buckets[indiceH]->key)) {
      map->current = indiceH;
      return map->buckets[indiceH];
    }
    indiceH++;
    if (indiceH == map->capacity)
      indiceH = 0;
  }
  return NULL;
}

Pair * firstMap(HashMap * map) {
  for (long i = 0; i < map->capacity; i++) {
    if (!map->buckets[i])
      continue;
    if (map->buckets[i]->key){
      map->current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {
  long pos = (map->current + 1);
  for (long i = map->current; i < map->capacity; i++,pos++) {
    if (map->buckets[pos])
      if (map->buckets[pos]->key) {
        map->current = pos;
        return map->buckets[pos];
      }
  }
  return NULL;
}

long sizeMap(HashMap *jugadores){
  return jugadores->size;
}
