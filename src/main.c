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

/* La función lee el nombre y la prioridad de la tarea que se desea
ingresar, inicializa la tarea con los datos ingresados y la guarda
en una tabla hash.
*/

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

/* La función lee el nombre de las dos tareas en las que se quiere
establecer la relación de precedencia. Primero lee la tarea que será
el precedente y luego la tarea a la que se le ingresará el precedente.
Una vez leídas, guarda la primera tarea en el atributo "misPrec" de
la segunda tarea, y guarda la segunda tarea en el atributo "soyPrec"
de la primera tarea.
*/

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

/* Se restablece la variable "visit" y "most" para cada tarea, evitando
problemas al mostrarlas nuevamente.
*/

void desmarcar(HashMap *tareas) {
  Tarea *current = valueRet(firstMap(tareas));
  while (current) {
    current->visit = 0;
    current->most = 0;
    current = valueRet(nextMap(tareas));
  }
}

/* Muestra la tarea que debería realizarse primero, mostrando su nombre,
prioridad y sus precedentes en caso de tenerlos.
*/

void mostrarMont(Heap *cola) {
  Tarea *hacer = heap_top(cola);
  Tarea *antes = valueRet(firstMap(hacer->misPrec));
  char tarea[100];
  strcpy(tarea, hacer->nombre);
  if (strlen(tarea) < 30) {
    for (int i = 0; i < (30 - strlen(tarea)); i++)
      printf(" ");
  }
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

/* Arma una cola con prioridad, sacando únicamente las tareas que son
posibles de realizar en el momento. En caso de tener precedentes, no
las agrega a la cola hasta que sus precedentes hayan sido mostrados.
*/

void mostrar(HashMap *lista) {
  Heap *monticulo = createHeap();
  Tarea *current;
  int agregar;
  int contV = 0;
  printf("                       Nombre|Prioridad |Precedente/s\n");
  while (1) {
    current = valueRet(firstMap(lista));
    if (contV == sizeMap(lista)) 
      current = NULL;
    while (current) {
      agregar = 1;
      Tarea *precedentes = NULL;
      if (sizeMap(current->misPrec))
        precedentes = valueRet(firstMap(current->misPrec));

      if (!precedentes && !current->visit) {
        heap_push(monticulo, current, current->prior);
        current->visit = 1;
        contV++;
      } else if (!current->visit) {
        while (precedentes) {
          if (!precedentes->visit || !precedentes->most) {
            agregar = 0;
            precedentes = NULL;
            continue;
          }
          precedentes = valueRet(nextMap(current->misPrec));
        }
        if (agregar) {
          heap_push(monticulo, current, current->prior);
          current->visit = 1;
          contV++;
        }
      }
      current = valueRet(nextMap(lista));
    }
    if (!heap_top(monticulo))
      break;

    mostrarMont(monticulo);
  }
  desmarcar(lista);
}

/* Elimina la tarea de todas las tareas en las que está marcada como
precedente, esto se determina utilizando el atributo 'soyPrec'.
*/

void eliminarDeSusPrec(Tarea *elim) {
  Tarea *dsp = valueRet(firstMap(elim->soyPrec));
  while (dsp) {
    eraseMap(dsp->misPrec, elim->nombre);
    dsp = valueRet(nextMap(elim->soyPrec));
  }
}

/* Elimina la tarea en las que lo tienen marcado como que son sus
precedentes, es decir, desde "soyPrec" de las tareas registradas
en "misPrec" de la eliminada.
*/

void eliminarDeMisPrec(Tarea *elim) {
  Tarea *ant = valueRet(firstMap(elim->misPrec));
  while (ant) {
    eraseMap(ant->soyPrec, elim->nombre);
    ant = valueRet(nextMap(elim->misPrec));
  }
}

/* Realiza la lectura de la tarea que se desea marcar como completada.
En caso de que la tarea tenga precedentes, se solicitará una
confirmación. Si se confirma, se procede a eliminar la tarea y las
relaciones de precedencia en las que estaba presente.
*/

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
  wunus = scanf("%c", &opcion);
  getchar();

  if (opcion == 's') {
    if (dsp)
      eliminarDeSusPrec(tareaElim);
    eliminarDeMisPrec(tareaElim);
    eraseMap(lista, tareaElim->nombre);
    printf("Tarea eliminada con éxito\n");
  } 
  else if (opcion == 'n') 
    printf("Eliminación cancelada\n");
  
  else 
    printf("Opcion invalida, acción cancelada\n");
  
}

/* Aquí se realiza el menú, donde se ingresa la opción deseada y se
deriva a la función correspondiente para cumplir la tarea requerida.
*/

int main() {
  HashMap *lista = createMap(10);
  size_t wunus;
  char opcion[30];
  while (1) {
    printMenu();
    wunus = 8;
    wunus = scanf("%[^\n]", opcion);
    getchar();
    printf("\n------------------------------------------------------------\n\n");
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
    printf("\n------------------------------------------------------------\n");
  }
}