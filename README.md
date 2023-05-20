# Tarea 3

# Guía de compilación y ejecución del programa:


## Pasos para compilar y ejecutar el programa

Para compilar y ejecutar el programa, sigue estos pasos:

1. Clona el repositorio desde GitHub ejecutando el siguiente comando en tu terminal:
    ```
    git clone https://github.com/CarlosAbarza/Tarea-3.git
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
Esta función no recibe ningún parámetro externo. Su objetivo es mostrar por pantalla las tareas ordenadas según su prioridad y su precedencia. La precedencia es especialmente importante, ya que puede hacer que tareas con menor prioridad se realicen antes que tareas con prioridad máxima.

La función comienza recorriendo la lista de tareas y colocando en un heap las tareas que no tienen precedentes o cuyos precedentes ya han sido mostrados, ya que esto indica que pueden ser realizadas en ese momento. Una vez que todas las tareas han sido extraídas del heap y mostradas, la función finaliza su ejecución.


### 4.  Marcar tarea como completada (tarea)
Esta función recibe el nombre de la tarea que se desea marcar como completada. En caso de que la tarea no tenga relaciones de precedencia, es decir, no es, ni tiene precedentes, simplemente se elimina y se termina la ejecución.

En caso de que la tarea sea precedente de otra, pero no tenga precedentes en sí misma, se elimina de la lista de precedentes de las otras tareas y se elimina del mapa de todas las tareas.

En el último caso, cuando la tarea tiene precedentes y se desea marcar como completada, se muestra un mensaje preguntando si se está seguro de esta decisión. En caso de confirmar, la tarea se elimina y se eliminan las relaciones de precedencia asociadas a ella.



## Herramientas usadas para el desarrollo:
  - replit (Para desarrollar el programa)
  - Github (Para guardar un backup del programa)
  - GPT (Para redactar parcialmente el archivo readme e impresiones del programa)


## Coevaluación del aporte individual
| Integrante | Participación | Responsabilidad | Comunicación | Calidad del trabajo | Trabajo en equipo | Pje Total |
|------------|--------------|----------------|--------------|------------------|------------------|------------------|
| Carlos    | 20           | 20             |  20          | 20               | 20               | 100               |
