#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if (!pq) {
    printf("No se ingreso una cola\n");
    return NULL;
  }

  else if (pq->size == 0) {
    printf("La cola esta vacia\n");
    return NULL;
  }

  return pq->heapArray[0].data;
}

void* crearNode(void* data, int priority) {
  heapElem *new = (heapElem*) malloc(sizeof(heapElem));
  if (!new) {
    printf("No se pudo reservar memoria\n");
    return NULL;
  }

  new->data = data;
  new->priority = priority;
  return new;
}


void heap_push(Heap* pq, void* data, int priority){
  if (!pq) {
    printf("No se ingreso una cola\n");
    return;
  }
  
  if (pq->size == pq->capac) {
    pq->capac = (pq->capac * 2) + 1;
    pq->heapArray = (heapElem*) realloc(pq->heapArray, pq->capac*sizeof(heapElem));
    if (!pq->heapArray) {
      printf("Error al reservar memoria\n");
      return;
    }
  }

  heapElem *new = crearNode(data, priority);
  if (!new) return;
  
  pq->heapArray[pq->size] = *new;
  free(new);
  int aux = pq->size;
  pq->size++;

  while (pq->heapArray[aux].priority > pq->heapArray[(aux-1) / 2].priority) {
    heapElem temp = pq->heapArray[aux];
    pq->heapArray[aux] = pq->heapArray[(aux-1)/2];
    aux = (aux-1) / 2;
    pq->heapArray[aux] = temp;
  }
  return;
}

void reordenar(Heap *pq) {
  int aux = 0;
  while (aux*2 + 2 <= pq->size) {
    if (pq->heapArray[aux].priority > pq->heapArray[2*aux + 1].priority) 
      return;
    else if (pq->heapArray[aux].priority > pq->heapArray[2*aux + 2].priority)
      return;

    else if (pq->heapArray[(2*aux) + 1].priority > pq->heapArray[(2*aux) + 2].priority) {
      heapElem temp = pq->heapArray[aux];
      pq->heapArray[aux] = pq->heapArray[2*aux + 1];
      aux = aux*2 + 1;
      pq->heapArray[aux] = temp;
    }

    else {
      heapElem temp = pq->heapArray[aux];
      pq->heapArray[aux] = pq->heapArray[2*aux + 2];
      aux = aux*2 + 2;
      pq->heapArray[aux] = temp;
    }
  }
}

void heap_pop(Heap* pq){
  if (!pq) {
    printf("No se ingreso una cola\n");
    return;
  }

  else if (pq->size == 0) {
    printf("La cola esta vacia\n");
    return;
  }

  pq->heapArray[0] = pq->heapArray[pq->size-1];
  pq->size--;
  reordenar(pq);
}

Heap* createHeap(){
  Heap *new = (Heap*) malloc(sizeof(Heap));
  if (!new) {
    printf("No se pudo crear el heap\n");
    return NULL;
  }

  new->heapArray = (heapElem*) malloc(3* sizeof(heapElem));
  if (!new->heapArray) {
    printf("No se pudo reservar memoria para el heap\n");
    return NULL;
  }

  new->size = 0;
  new->capac = 3;
  return new;
}
