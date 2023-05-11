#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"
#include "printGen.h"

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
        printf("funciona\n");
        break;

      case '2' :
        printf("no funciona\n");
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