# Tarea 3

# Guía de compilación y ejecución del programa:

## Pasos para compilar y ejecutar el programa

Sigue estos pasos para compilar y ejecutar el programa:

1. Clona el repositorio desde GitHub ejecutando el siguiente comando en tu terminal:
   ```
   git clone https://github.com/CarlosAbarza/Tarea-3.git
   ```

2. Abre una terminal en el directorio raíz del proyecto, donde se encuentran los archivos `.c`, `.h` y otros archivos.

3. Ejecuta el siguiente comando para compilar el programa utilizando el archivo `CMakeLists.txt`:
   ```bash
   cmake .
   make
   ```

   Esto generará los archivos de objeto y el ejecutable del programa.

4. Una vez compilado con éxito, ejecuta el programa con el siguiente comando:
   ```bash
   ./main
   ```

   Esto ejecutará el programa y mostrará los resultados en la terminal.


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
