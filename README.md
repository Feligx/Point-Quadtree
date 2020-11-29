# Point-Quadtree

QuadTree de puntos en C++ para la revisión de colisiones de puntos.

**Quadtree:**
  Para el funcionamiento del Quadtree se implementaron las estructuras punto y rectángulo, junto con las clases Quadtree y QuadNode. Las cuales se explicarán a continuación:
  
  * **Point:**
    Los puntos son objetos bajo los cuales se hace la inserción en el Quadtree, la revisión de colisiones del mismo. Estan compuestos por:
      * x , y: las coordenadas en las que se halla el punto.
      * radius: el radio de los puntos.
      
      - **Además de incluir los siguientes métodos:**
        * Distance: que retorna el valor de la distancia entre las coordenadas de 2 puntos.
        * Intersected: que retorna true o false, dependiendo de si un punto colisiona con otro o no.
      
  * **Rectangle:** Los rectángulos son usados para definir los límites del Quadtree y de sus hijos (QuadNodes), están conformados por:
      * x, y: las coordenadas en las que se encuentra el rectángulo.
      * w, h: la longitud de la base y altura del rectángulo.
      
      - **Además de incluir el siguiente método:**
          * contain_point: retorna true o false dependiendo de si un punto está o no dentro del área del rectángulo.
          
  * **QuadNode:** Los QuadNodes representan las subdiviones del árbol, y son los que almacenan los puntos en su región determinada por sus límites, están compuestos por:
     * capacity: la capacidad de puntos que puede almacenar el nodo.
     * NW: el nodo hijo noroeste.
     * NE: el nodo hijo noreste.
     * SW: el nodo hijo suroeste.
     * SE: el nodo hijo sureste.
     * bounds: un rectángulo que representa los límites del nodo.
     * data: arreglo donde se almacenan los puntos que se hallan en la región del nodo.
     * count: la cantidad de puntos almacenados en el nodo.
     
     - **Además de incluir los siguientes métodos:**
      * insert: inserta puntos en el nodo si aun tiene espacio para estos, sino divide el nodo y los inserta en sus hijos; retorna true si se insertó el nodo, false en caso contrario.
      * isLeaf: retorna true o false dependiendo de si el nodo es una hoja o no.
      * query_colision: hace la consulta para ver cuales de los puntos que almacena están colisionando.
      
  * **Quadtree:** El Quadtree es el árbol que almacena los nodos hijos, está conformado por:
    * root: el nodo raíz del árbol
    * capcacity: capacidad de todos los nodos del árbol para el almacenaje de puntos.
    - **Además de incluir el siguiente método:**
      * query: wrapper del método query_colision para iniciar el proceso desde la raíz del árbol.
**Visualzador: **
  - El visualizador está basado en la librería SDL2 para la creación de ventanas y formas tales como puntos y rectángulos. El visualizador funciona de 2 maneras:
    * Generando una n cantidad de puntos dada por el usuario de forma aleatoria e insertandolos en el árbol desde la raíz, y luego dibujarlos en la ventana creada.
    * Generar puntos cada vez que el usuario haga clic en la ventana en la posición del mouse, e incluyéndolos según sean insertados.
    
# Para implementación:
Para la implementación es fundamental la instalación del Visual Studio para poder incluir la librería SDL2 siguiendo los siguientes pasos:
 * https://www.youtube.com/watch?v=tmGBhM8AEj8
Además de que esto permite poder compilar y ejecutar de forma más secilla.
