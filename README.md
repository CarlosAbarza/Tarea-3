# Tarea 3

# Guía de compilación y ejecución del programa:


## Pasos para compilar y ejecutar el programa

Para compilar y ejecutar el programa, sigue estos pasos:

1. Clona el repositorio desde GitHub ejecutando el siguiente comando en tu terminal:
    ```
    git clone [https://github.com/ignacio-ave/Tarea-N2-Stalker.git](https://github.com/CarlosAbarza/Tarea-3/tree/63aec6a9b2cd196d33422de0171748bdf4169a8a)
    ```
    
2. Abre una terminal en el directorio en el que se encuentran los archivos `main.c` y los archivos que componene el programa:
    - hashmap.c: Implementación de la tabla hash.
    - hashmap.h: Encabezado para la tabla hash.
    - list.c: Implementación de la lista enlazada.
    - list.h: Encabezado para la lista enlazada.
    - main.c: Código principal del programa.
    - Makefile: Archivo Makefile para compilar y enlazar el proyecto.
    - printformato.c: Funciones de formato para la salida impresa.
    - printformato.h: Encabezado para las funciones de formato.
    - README.md: Documentación del proyecto.
    - stack.h: Encabezado para la estructura de datos de pila

3. Escribe el comando `make -s` para compilar el programa:
    ```
    make -s
    ```
    
4. Escribe el comando `./main` para ejecutar el programa:
    ```
    ./main.c
    ```

## Opciones que funcionan:
1.  Agregar tarea (tarea, prioridad)
2.  Establecer precedencia entre tareas (tarea1, tarea2)
3.  Mostrar tareas por hacer
4.  Marcar tarea como completada (tarea)


### 1.  Agregar tarea (tarea, prioridad)
Esta función recibe el nombre de una tarea que se desea ingresar a la lista, junto con su prioridad. En ella se crea la variable "tarea", dejándola lista para establecer relaciones de precedencia o ser mostrada más adelante.


### 2.  Establecer precedencia entre tareas (tarea1, tarea2)
La función solicita que se ingrese el nombre de dos tareas en las que se quiera establecer la precedencia. La primera tarea deberá realizarse antes que la segunda, lo que se traduce en que la primera será precedente de la segunda. Para guardar la relación entre estas, se guarda dentro de un mapa en la variable "tarea", que conserva todos los precedentes.


### 3.  Mostrar tareas por hacer
La función agregarItemDef se encarga de agregar un ítem al inventario del jugador y actualizar el mapa de ítems con la información de qué jugadores tienen cada ítem.

La función agregarItemBuscar pide al usuario el nombre del jugador y del ítem a agregar, busca al jugador en el mapa de jugadores y, si existe, agrega el ítem al inventario del jugador llamando a agregarItemDef. También guarda esta acción en el historial del jugador.


### 4.  Marcar tarea como completada (tarea)
La función eliminarItemJugadores se encarga de eliminar un ítem del inventario de un jugador y actualizar el mapa de ítems con la información de qué jugadores tienen cada ítem.

Primero, la función pide al usuario que ingrese el nombre del jugador. Luego, busca al jugador en el mapa de jugadores utilizando el nombre ingresado. Si el jugador no existe, muestra un mensaje indicando esto y retorna. Si el jugador existe, pide al usuario que ingrese el nombre del ítem a eliminar.

Posteriormente, la función eliminaItemDelJugador se encarga de buscar el ítem en el inventario del jugador y, si lo encuentra, lo elimina del inventario y actualiza el mapa de ítems correspondiente. Si el ítem no existe en el inventario del jugador, muestra un mensaje indicándolo.

Si se logra eliminar el ítem, se guarda esta acción en el historial del jugador utilizando la estructura Acciones y la pila versiones del jugador.




## Herramientas usadas para el desarrollo:
  - replit (Para desarrollar el programa)
  - Github (Para guardar un backup del programa)
  - GPT (Para redactar parcialmente el archivo readme e impresiones del programa)


## Coevaluación del aporte individual
| Integrante | Participación | Responsabilidad | Comunicación | Calidad del trabajo | Trabajo en equipo | Pje Total |
|------------|--------------|----------------|--------------|------------------|------------------|------------------|
| Carlos    | 20           | 20             |  20          | 20               | 20               | 100               |
