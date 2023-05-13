#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include "heap.h"
#include "list.h"
#include "printGen.h"

typedef struct {
  char *nombre;
  int prior;
  int completa;
  int n_prec;
  List *prec;
} Tarea;

void lecturaAgregar(HashMap *lista) {
  char *tarea = (char*) malloc(30*sizeof(char));
  size_t max = 30;
  int prioridad;

  printf("Ingrese el nombre de la tarea: ");
  getline(&tarea, &max, stdin);
  printf("Ingrese su nivel de prioridad: ");
  scanf("%d", &prioridad);
  getchar();
  Tarea *data = (Tarea*) malloc(sizeof(Tarea));
  data->nombre = strdup(tarea);
  data->prior = prioridad;
  data->completa = 0;
  data->n_prec = 0;
  data->prec = createList();
  
  insertMap(lista, tarea, data);
}

void establecerPrior(HashMap *lista) {
  char *tareaPrim = (char*) malloc(30*sizeof(char));
  size_t max = 30;
  printf("Ingrese la tarea que debe realizarse primero: ");
  getline(&tareaPrim, &max, stdin);

  char *tareaSec = (char*) malloc(30*sizeof(char));
  max = 30;
  printf("Ingrese la otra tarea: ");
  getline(&tareaSec, &max, stdin);

  Pair *aux = searchMap(lista, tareaSec);
  Pair *princ = searchMap(lista, tareaPrim);
  if(!aux || !princ) {
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
      case '1' :
        lecturaAgregar(lista);
        break;

      case '2' :
        establecerPrior(lista);
        break;

      case '3' :
        // break;

      case '4' :
        printf("Aun en desarrollo\n");
        break;

      case '0' :
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