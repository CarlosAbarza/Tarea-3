#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"
#include "printGen.h"

void lecturaAgregar(Heap *pq) {
  char *tarea = (char*) malloc(30*sizeof(char));
  size_t max = 30;
  int prioridad;

  printf("Ingrese el nombre de la tarea: ");
  getline(&tarea, &max, stdin);
  printf("Ingrese su nivel de prioridad: ");
  scanf("%d", &prioridad);
  getchar();
  heap_push(pq, tarea, prioridad);
}

void establecerPrior(Heap* pq) {
  char *tareaPrim = (char*) malloc(30*sizeof(char));
  size_t max = 30;
  getline(&tareaPrim, &max, stdin);

  char *tareaSec = (char*) malloc(30*sizeof(char));
  max = 30;
  getline(&tareaSec, &max, stdin);
  
}






int main() {
  Heap *pq = createHeap();

  char opcion[30];
  while (1) {
    printMenu();
    scanf("%[^\n]", opcion);
    getchar();
    if (strlen(opcion) > 1)
      strcpy(opcion, "next");
    switch (opcion[0]) {
      case '1' :
        lecturaAgregar(pq);
        break;

      case '2' :
        
        // break;

      case '3' :
        // break;

      case '4' :
        printf("Aun en desarrollo\n");
        break;

      case '0' :
        printf("Hasta luego\n");
        free(pq);
        return 0;

      default:
        printf("Opción inválida. Por favor, ingrese un número válido.\n");
        break;
  }
}
  
}