#include "hashmap.h"
#include "heap.h"
#include "list.h"
#include "printGen.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *nombre;
  int prior;
  int completa;
  int visit;
  int n_prec;
  List *prec;
} Tarea;

void lecturaAgregar(HashMap *lista) {
  char *tarea = (char *)malloc(30 * sizeof(char));
  size_t max = 30;
  int prioridad;

  printf("Ingrese el nombre de la tarea: ");
  getline(&tarea, &max, stdin);
  printf("Ingrese su nivel de prioridad: ");
  scanf("%d", &prioridad);
  getchar();
  Tarea *data = (Tarea *)malloc(sizeof(Tarea));
  data->nombre = strdup(tarea);
  data->prior = prioridad;
  data->completa = 0;
  data->visit = 0;
  data->n_prec = 0;
  data->prec = createList();

  insertMap(lista, tarea, data);
}

void establecerPrior(HashMap *lista) {
  char *tareaPrim = (char *)malloc(30 * sizeof(char));
  size_t max = 30;
  printf("Ingrese la tarea que debe realizarse primero: ");
  getline(&tareaPrim, &max, stdin);

  char *tareaSec = (char *)malloc(30 * sizeof(char));
  max = 30;
  printf("Ingrese la otra tarea: ");
  getline(&tareaSec, &max, stdin);

  Pair *aux = searchMap(lista, tareaSec);
  Pair *princ = searchMap(lista, tareaPrim);
  if (!aux || !princ) {
    printf("Una de las tareas no fue ingresada\n");
    return;
  }
  Tarea *dataSec = aux->value;
  pushFront(dataSec->prec, princ->value);
  dataSec->n_prec++;
  free(tareaPrim);
  free(tareaSec);
  return;
}

// void mostrarTareas(Heap *pq, HashMap *lista) {

// }

void mostrar(HashMap *lista, Heap *monticulo) {
  Pair *current;
  int quedan = 1;
  while (quedan){
    current = firstMap(lista);
    while (current && current->key) {
      quedan = 0;
      Tarea *data = current->value;
      Tarea *precedentes = first(data->prec);
      if (!precedentes && !data->visit) {
        heap_push(monticulo, data, data->prior);
        data->visit = 1;
      }
      else if (!data->visit){
        while (precedentes) {
          Pair *prec = searchMap(lista, precedentes->nombre);
          Tarea *aux = prec->value;
          if (!aux->visit) {
            quedan = 1;
            precedentes = NULL;
            continue;
          }
          precedentes = next(data->prec);
        }
        if (!quedan) {
          heap_push(monticulo, data, data->prior);
          data->visit = 1;
        }
        searchMap(lista, current->key);
      }
      current = nextMap(lista);
    }
    if (!heap_top(monticulo)) 
      return;
    while (heap_top(monticulo)) {
      Tarea *hacer = heap_top(monticulo);
      Tarea *antes = first(hacer->prec);
      printf("%s, %d", hacer->nombre, hacer->prior);
      while (antes) {
        printf(", %s", antes->nombre);
        antes = next(hacer->prec);
      }
      printf(".\n");
      heap_pop(monticulo);
    }
    quedan = 1;
  }
}



int main() {
  Heap *tareasOrd = createHeap();
  HashMap *lista = createMap(10);

  char opcion[30];
  while (1) {
    printMenu();
    scanf("%[^\n]", opcion);
    getchar();
    if (strlen(opcion) > 1)
      strcpy(opcion, "next");
    switch (opcion[0]) {
    case '1':
      lecturaAgregar(lista);
      break;

    case '2':
      establecerPrior(lista);
      break;

    case '3':
      mostrar(lista, tareasOrd);
      break;

    case '4':
      printf("Aun en desarrollo\n");
      break;

    case '0':
      printf("Hasta luego\n");
      free(tareasOrd);
      free(lista);
      return 0;

    default:
      printf("Opción inválida. Por favor, ingrese un número válido.\n");
      break;
    }
  }
}