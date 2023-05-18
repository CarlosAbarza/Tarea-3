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
  int visit;
  HashMap *misPrec;
  List *soyPrec;
} Tarea;

void lecturaAgregar(HashMap *lista) {
  char *tarea = (char *)malloc(30 * sizeof(char));
  size_t max = 30;
  int prioridad;

  printf("Ingrese el nombre de la tarea: ");
  size_t wunus = getline(&tarea, &max, stdin);
  printf("Ingrese su nivel de prioridad: ");
  wunus = scanf("%d", &prioridad);
  getchar();
  Tarea *data = (Tarea *)malloc(sizeof(Tarea));
  data->nombre = strdup(tarea);
  data->prior = prioridad;
  data->visit = 0;
  data->misPrec = createMap(5);
  data->soyPrec = createList();
  insertMap(lista, tarea, data);
}

void establecerPrior(HashMap *lista) {
  char *tareaPrim = (char *)malloc(30 * sizeof(char));
  size_t max = 30;
  printf("Ingrese la tarea que debe realizarse primero: ");
  size_t wunus = getline(&tareaPrim, &max, stdin);

  char *tareaSec = (char *)malloc(30 * sizeof(char));
  max = 30;
  printf("Ingrese la otra tarea: ");
  wunus = getline(&tareaSec, &max, stdin);

  Tarea *dataSec = valueRet(searchMap(lista, tareaSec));
  Tarea *dataPrin = valueRet(searchMap(lista, tareaPrim));
  if (!dataSec || !dataPrin) {
    printf("Una de las tareas no fue ingresada\n");
    return;
  }
  
  insertMap(dataSec->misPrec, dataPrin->nombre, dataPrin);
  pushBack(dataPrin->soyPrec, dataSec);
  free(tareaPrim);
  free(tareaSec);
  return;
}

// void mostrarTareas(Heap *pq, HashMap *lista) {

// }
void mostrar(HashMap*lista, Heap *monticulo) {
  Tarea *current;
  int quedan = 1;
  printf("                       Nombre|Prioridad |Precedente/s\n");
  while (quedan){
    current = valueRet(firstMap(lista));
    while (current) {
      quedan = 0;
      Tarea *precedentes = NULL;
      if (sizeMap(current->misPrec))
        precedentes = valueRet(firstMap(current->misPrec));
      if (!precedentes && !current->visit) {
        heap_push(monticulo, current, current->prior);
        current->visit = 1;
      }
      else if (!current->visit){
        while (precedentes) {
          // Tarea *tareaPrec = valueRet(searchMap(lista, precedentes->nombre));
          if (!precedentes->visit) {
            quedan = 1;
            precedentes = NULL;
            continue;
          }
          precedentes = valueRet(nextMap(current->misPrec));
        }
        if (!quedan) {
          heap_push(monticulo, current, current->prior);
          current->visit = 1;
        }
        searchMap(lista, current->nombre);
      }
      current = valueRet(nextMap(lista));
    }
    if (!heap_top(monticulo)) 
      break;
    
    Tarea *hacer = heap_top(monticulo);
    Tarea *antes = valueRet(firstMap(hacer->misPrec));
    char tarea[30];
    strcpy(tarea, hacer->nombre);
    for (int i = 0; i < (30 - strlen(tarea)); i++)
      printf(" ");
    tarea[strlen(tarea) - 1] = '\0';
    printf("%s|", tarea);
    char prio[5];
    sprintf(prio, "%d", hacer->prior);
    for (int i = 0; i < (10 - strlen(prio)); i++)
      printf(" ");
    printf("%d|", hacer->prior);
    int cont = 0;
    while (antes) {
      strcpy(tarea, antes->nombre);
      tarea[strlen(tarea) - 1] = '\0';
      if (cont != 0)
        printf(", ");
      printf("%s", tarea);
      antes = valueRet(nextMap(hacer->misPrec));
      cont++;
    }
    printf("\n");
    heap_pop(monticulo);
    
    quedan = 1;
  }
  current = valueRet(firstMap(lista));
  while (current) {
    current->visit = 0;
    current = valueRet(nextMap(lista));
  }
}

int main() {
  Heap *tareasOrd = createHeap();
  HashMap *lista = createMap(10);

  char opcion[30];
  while (1) {
    printMenu();
    size_t wunus = scanf("%[^\n]", opcion);
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