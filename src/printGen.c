#include <stdio.h>
#include "printGen.h"

void printMenu() {
    printf("\n");
    printf("╭──────────────────────────────────────────────────────────╮\n");
    printf("│                     MENU PRINCIPAL                       │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ 1. Agregar tarea                                         │\n");
    printf("│ 2. Establecer precedencia entre tareas                   │\n");
    printf("│ 3. Mostrar tareas por hacer                              │\n");
    printf("│ 4. Marcar tarea como completada                          │\n");
    // printf("│ 5. Deshacer última acción                                │\n");
    // printf("│ 6. Cargar datos de tareas desde un archivo de texto      │\n");
    printf("│ 0. Salir                                                 │\n");
    printf("╰──────────────────────────────────────────────────────────╯\n");
    printf("\nIngrese el número de la opción deseada: ");
}