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
  int most;
  HashMap *misPrec;
  HashMap *soyPrec;
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
  data->most = 0;
  data->misPrec = createMap(5);
  data->soyPrec = createMap(5);
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
  insertMap(dataPrin->soyPrec, dataSec->nombre, dataSec);
  free(tareaPrim);
  free(tareaSec);
  return;
}

void desmarcar(HashMap *tareas) {
  Tarea *current = valueRet(firstMap(tareas));
  while (current) {
    current->visit = 0;
    current->most = 0;
    current = valueRet(nextMap(tareas));
  }
}

void mostrarMont(Heap *cola) {
  Tarea *hacer = heap_top(cola);
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
  hacer->most = 1;
  printf("\n");
  heap_pop(cola);
}

void mostrar(HashMap *lista) {
  Heap *monticulo = createHeap();
  Tarea *current;
  int quedan = 1;
  printf("                       Nombre|Prioridad |Precedente/s\n");
  while (quedan) {
    current = valueRet(firstMap(lista));
    while (current) {
      quedan = 0;
      Tarea *precedentes = NULL;
      if (sizeMap(current->misPrec))
        precedentes = valueRet(firstMap(current->misPrec));

      if (!precedentes && !current->visit) {
        heap_push(monticulo, current, current->prior);
        current->visit = 1;
      } else if (!current->visit) {
        while (precedentes) {
          if (!precedentes->visit || !precedentes->most) {
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
      }
      current = valueRet(nextMap(lista));
    }
    if (!heap_top(monticulo))
      break;

    mostrarMont(monticulo);
    quedan = 1;
  }
  // current = valueRet(firstMap(lista));
  desmarcar(lista);
}

void eliminarDeSusPrec(Tarea *elim) {
  Tarea *dsp = valueRet(firstMap(elim->soyPrec));
  while (dsp) {
    eraseMap(dsp->misPrec, elim->nombre);
    dsp = valueRet(nextMap(elim->soyPrec));
  }
}

void eliminarDeMisPrec(Tarea *elim) {
  Tarea *ant = valueRet(firstMap(elim->misPrec));
  while (ant) {
    eraseMap(ant->soyPrec, elim->nombre);
    ant = valueRet(nextMap(elim->misPrec));
  }
}

void eliminarTarea(HashMap *lista) {
  char *nombre = (char *)malloc(30 * sizeof(char));
  size_t max = 30;
  printf("Ingrese el nombre de la tarea que desea eliminar: ");
  size_t wunus = getline(&nombre, &max, stdin);
  if (!nombre || !wunus) {
    printf("Error al leer el nombre de la tarea\n");
    return;
  }

  Tarea *tareaElim = valueRet(searchMap(lista, nombre));
  if (!tareaElim) {
    printf("La tarea ingresada no esta en la lista\n");
    return;
  }

  Tarea *ant = valueRet(firstMap(tareaElim->misPrec));
  Tarea *dsp = valueRet(firstMap(tareaElim->soyPrec));
  if (!ant) {
    eliminarDeSusPrec(tareaElim);
    eraseMap(lista, tareaElim->nombre);
    printf("Tarea eliminada con éxito\n");
    return;
  }

  printf("¿Estás seguro que desea eliminar la tarea?\n");
  printf("Para confirmar ingrese s | Para cancelar ingrese n\n");
  char opcion;
  scanf("%c", &opcion);
  getchar();

  if (opcion == 's') {
    if (dsp)
      eliminarDeSusPrec(tareaElim);
    eliminarDeMisPrec(tareaElim);
    eraseMap(lista, tareaElim->nombre);
    printf("Tarea eliminada con éxito\n");
  } else
    return;
}

int main() {
  HashMap *lista = createMap(10);
  size_t wunus;
  char opcion[30];
  while (1) {
    printMenu();
    wunus = 8;
    wunus = scanf("%[^\n]", opcion);
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
      mostrar(lista);
      break;

    case '4':
      eliminarTarea(lista);
      break;

    case '0':
      printf("Hasta luego\n");
      free(lista);
      return 0;

    default:
      printf("Opción inválida. Por favor, ingrese un número válido.\n");
      break;
    }
  }
}