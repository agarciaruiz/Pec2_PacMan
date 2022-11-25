PAC1 - PACMAN - Alberto García

A continuación se detallan las partes más importantes de la implemnentación de la práctica:

- Gestión de pantallas:
	
	Se define un enum que contiene información sobre todos los tipos de pantallas a los que podemos acceder y la pantalla en la que 
	estamos actualmente. Nada más empezar la ejecución, inicializamos la pantalla de logo. A partir de aquí, llamamos a UpdateDrawFrame,
	que se encarga de gestionar las transiciones de una pantalla a otra. Para ello, definimos un booleano que determina si estamos o no
	transicionando. En el caso de estar transicionando, llamamos a UpdateTransition, que realiza un fundido de una pantalla a otra a la 
	vez que hace un Unload de la actual y un Init de la siguiente. Si no estamos transicionando, llamamos al método Update de la pantalla
	actual hasta que cambia el valor de FinishScreen y nos vemos obligados a transicionar a la siguiente pantalla estipulada.

	Hay 5 tipos de pantalla: Logo, Title, Options, Game y Finish. Todas ellas heredan de una clase principal definida en Screen.h. Esta 
	definición incluye métodos virtuales para la inicialización, la actualización, el pintado y el unload de las pantallas.

	Logo Screen: 
		- Init: Posiciona el logo en el centro e inicializa valores de frames, texturas, etc. 

		- Update: Incrementa los frames y cambia finish screen a 2 (equivalente a Title Screen) pasado cierto tiempo.

		- Draw: Pinta la textura del logo en el centro de la pantalla.

	Title Screen:
		- Init: Inicializa frames, pantalla de carga, texturas y música.

		- Update: Incrementa los frames, actualiza la música y tiene en cuenta el input del usuario para cambiar a la siguiente pantalla.
			    KEY ENTER->finishScreen = 4 (GAME SCREEN) // KEY O -> finishScreen = 3 (OPTIONS)

		- Draw: Pinta en pantalla la textura de Paratrooper, el nombre del autor y textos indicativos de las instrucciones para el
			  cambio de pantalla.

	Options Screen:
		- Init: Inicializa los valores de los textos con las instrucciones del juego.

		- Update: Comprueba el input del usuario para cambiar de pantalla. KEY O -> finishScreen = 2 (TITLE)

		- Draw: Pinta en pantalla los textos en las posiciones especificadas.

	Game Screen:
		- Init: Inicializa la clase game manager, que se encargará de la gestión del juego en sí.

		- Update: Actualiza la clase game manager y comprueba la condición de fin de partida para transicionar a FINISH SCREEN.

		- Draw: Llama al método Draw de game manager para pintar los elementos del juego.

		- Reset Screen: Llama al método ResetGame del game manager para reinicializar las variables al empezar un nuevo juego.

- Managers:

	Game Manager: Clase principal del juego, encargada de gestionar el workflow general. Para esta PEC el GameManager se ha convertido
			  en un signleton y es accesible desde todas partes dentro del ciclo de vida de la aplicación.

		- GetInstance: Si la instancia del Game Manager es null, crea una nueva instancia. En cualquier caso, devuelve el valor de la
				   única instancia creada.

		- Init: Inicializa las variables de juego y de condición de finalizacón. Inicializa las imagenes y texturas de la UI, carga el
			  tilemap, inicializa el player y el fantasma.

		- Update: Comprueba input del usuario para pausar la partida con la tecla P. Si la partida no está pausada, se ejecuta todo
			    con normalidad. Esto quiere decir que actualizamos la clase Player y el Enemy Manager, así como comprobamos la condición
			    de victoria o derrota para determinar si el juego ha terminado.

		- Draw: Pinta la UI, el tilemap, el player y los enemigos llamando a los correspondientes Draw de las demás clases. 
 
		- Unload: Reinicia los valores de juego para empezar una nueva partida, incluyendo el player y los enemigos.

		- DrawUI: Pinta, arriba a la izquierda en pantalla, la puntuación del usuario y, arriba a la derecha, las vidas de PACMAN.

	Sound Manager: Gestiona la música y los sonidos del juego. De la misma forma que el Game Manager, sigue un patrón singleton para
			   asegurar que sólo existe uno en todo el ciclo de vida de la aplicación.

		- GetInstance: Si la instancia del Sound Manager es null, crea una nueva instancia. En cualquier caso, devuelve el valor de la
				   única instancia creada.

		- PlayMusic: Carga un stream de música, configura el volumen y lo hace sonar.

		- UpdateMusic: Actualiza el stream de música.

		- UnloadMusic: Da de baja el stream de música cargado.

		- PlaySoundStream: Carga un sonido pasandole un sound stream por parámetro y lo hace sonar.

 
- Player: Gestiona el input del jugador. Sigue también un patrón de singleton, puesto que sólo puede haber uno en juego.

	- GetInstance: Si la instancia del Player es null, crea una nueva instancia. En cualquier caso, devuelve el valor de la
			   única instancia creada.

	- Init: Inicializa la puntuación, la posición y direción iniciales, el estado actual, carga las texturas y recoge las instancias
		  de los singletons del tilemap y el sound manager.

	- Update: Inicializa un contador de frames que usa para actualizar los sprites. En función de si está muerto o no, 
		    el contador tarda más o menos en reinicializar.

		    Comprueba el estado actual llamando al método CheckState. Escucha el input del usuario para modificar la
		    dirección de movimiento y cambiar el estado actual a LEFT, RIGHT, UP o DOWN en función de dónde miramos.
		    Llama al método Move() y a CheckCollisions() pasándole la posición del frame anterior.

	- Draw: Pinta en pantalla los sprites correspondientes a la textura de muerte si estamos muertos o a los de movimiento normal.

	- Reset: Hace unload de los recursos inicializados y resetea la puntuación.

	- CheckState: Comprueba el estado actual y actualiza el rectangulo de la textura a las coordenadas que le corresponden del 
			  rectángulo original que contiene los sprites de PACMAN. Anima, en función del currentFrame configurado en Update
			  los dos sprites correspondientes a cada estado de movimiento y todos los sprites correspondientes al estado DEAD.

	- Move: Actualiza la posición en función de la dirección recibida del input y la velocidad de movimiento.

	- CheckCollisions: Itera sobre el tilemap y comprueba la colisión de los bordes del jugador con los colliders inicializados en
				 el tilemap. Si choca contra un muro, se devuelve al jugador a su posición en el frame anterior.

				 Comprueba las colisiones con los objetos pintados en el mapa. Si el objeto con el que se colisiona es una 
				 píldora normal, se suma 10 a la puntuación, se borra el objeto y se decrementa el número de píldoras totales.
				 Si se colisiona con una píldora grande, se suma 50 a la puntuación y se sigue el mismo proceso anterior. Esta
				 vez, también se añade el sonido "EatingPowerPill" de los recursos.

	- GetBounds: Devuelve el rectangulo correspondiente a las medidas de la textura del player.

	- Die: Método que es llamado desde la clase Ghost cuando el jugador muere. Para evitar errores, se hace una comprobación del 
		 estado del jugador; si está muerto, no se ejecuta.

		 Lanza el sonido de muerte, configura la variable _isDead a true, pone el estado actual a DEAD y decrementa las vidas.

	- GhostEaten: Lanza el sonido "EatingGhost" y suma 200 a la puntuación.

- Ghost: Gestiona la IA de los enemigos de PACMAN.

	- Init: Recoge las instancias del tilemap y el player, inicializa dirección, tile, posición y bounds, así como velocidad, texturas, etc.

	- Update: Comprueba si el jugador ha comido una píldora grande para pasar al estado FRIGHTENED. Si está en el estado FRIGHTENED pero
		    no ha sido comido, ponemos en marcha un contador de 10 segundos y, si no ocurre nada, volvemos al estado CHASE. En el caso
		    de ser comidos, comprobamos si el fantasma ha llegado a la casilla inicial y volvemos al estado CHASE.

		    Se llama a CheckState para realizar acciones en función del estado actual.

	- Draw: Pinta por pantalla la textura del fanstasma.

	- Reset: Da de baja las texturas cargadas. 

	- CheckState: Comprueba el estado actual y configura la textura en función de cuál es. Además, siempre y cuando el jugador no esté
			  muerto, se llama al método move, en cargado de hacer una cosa u otra en función del estado.

	- Move: Comprobamos la dirección de la casilla marcada como target. Si nos encontramos en dicha casilla, actualizamos el tile actual y
		  calculamos la nueva dirección que debemos seguir.

		  Por último, comprobamos colisiones con el Player. Si nos encontramos en estado CHASE, se llama a Player->Die; si nos encontramos
		  en estado FRIGHENTED, pasamos a estado EATEN y se llama a Player->GhostEaten para informar de que hemos sido comidos.

	- GetNewDirection: Genera un vector de posibles direcciones en función de la dirección actual. Llama a CheckCollisions para determinar 
				 cuáles de esas son válidas. En función del estado actual, se configura un target u otro y se llama a 
				 CheckDistanceWithTarget.

				 En el caso del estado CHASE, el target es PACMAN; en el caso del estado FRIGHTENED, el target es la casilla superior 
				 izquierda del tilemap; y, en el caso del estado EATEN, el target es el centro del tilemap. Devuelve la nueva dirección
				 calculada para asignarla a la dirección actual del fantasma.

	- CheckCollisions: Itera sobre las posibles direcciones que puede tomar el fantasma. Si alguna de ellas supone una colisión, se descarta
				 y se devuelve un nuevo vector sin dicha dirección.

	- CheckDistanceWithTarget: Itera sobre las direcciones válidas para determinar cuál es el mejor movimiento posible. Para ello, calcula
					   la distancia al target para saber el camino más corto y devolver la dirección que debe tomar.

	- CheckCollisionWithPlayer: Comprueba si existe colisión entre los bordes de la textura del fantasma y los del player. Si esto ocurre y
					    nos encontramos en estado CHASE, reseteamos la posición al inicio del tilemap para empezar una nueva ronda.
					    
					    Devuelve true o false en función de si se detecta o no colisión.

	- ResetPosition: Manada al fantasma al centro del tilemap.

- Tilemap: Singleton correspondiente al mapa de juego. Accesible desde todas las clases como una única instancia durante el ciclo de vida 
	     de la aplicación.

	- GetInstance: Si la instancia del Tilemap es null, crea una nueva instancia. En cualquier caso, devuelve el valor de la
			   única instancia creada.
	
	- Load: Recibe por parámetro los ficheros de valores, colliders y objetos del mapa para inicializarlos en su posición correspondiente.
		  Asigna las variables del tilemap conforme va escaneando los archivos.

	- Init: Inicializa el tamaño de los tiles y la posición del tilemap.

	- Unload: Si los tiles son diferente a NULL, borra los punteros relacionados con los tiles.

	- Draw: Itera sobre todos los tiles y pinta los rectangulos correspondientes de las texturas donde toca, en función de la información
		  leída en el Load.
