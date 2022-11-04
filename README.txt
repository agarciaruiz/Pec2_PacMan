PAC0 - PARATROOPER - Alberto García

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
		- Init: Inicializa frames, pantalla de carga y texturas.
		- Update: Incrementa los frames y tiene en cuenta el input del usuario para cambiar a la siguiente pantalla.
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

	Game Manager: Clase principal del juego, encargada de gestionar el workflow general.
		- Init: Inicializa el contador de tiempo de juego, la posición del player y su inicialización y llama al método Init del
			  Enemy Manager.
		- Update: Comprueba input del usuario para pausar la partida con la tecla P. Si la partida no está pausada, se ejecuta todo
			    con normalidad. Esto quiere decir que actualizamos el tiempo de juego, actualizamos la clase Player y el Enemy Manager.
		- Draw: Pinta la UI, el player y los enemigos llamando a los correspondientes Draw de las demás clases.  
		- ResetGame: Reinicia los valores de juego para empezar una nueva partida, incluyendo el player y los enemigos.
		- DrawUI: Pinta, arriba a la izquirda en pantalla, el tiempo de juego, la cantidad de tropas que han aterrizado y la 
			    puntuación del jugador.

	Enemy Manager: Gestiona la aparición de enemigos en el terreno de juego.
		- Init: Inicializa los tiempos de spawn de los helicopteros y la cantidad de tropas aterrizadas.
		- Update: Gestiona las rutinas de los helicópteros y las tropas.
		- Draw: Pinta los helicopteros y las tropas activas en pantalla.
		- Reset: Limpia las listas que contienen los helicopteros y tropas activos y devuelve los elementos a la pool en cuestión.

		- Helicopter Routine: Inicia un temporizador que spawnea un helicoptero en tiempos aleatorios entre 3 y 5 segundos. Al transcurrir
					    este tiempo, pide un elemento inactivo de la pool de helicopteros y lo inicializa. Se guarda el elemento
					    en una lista auxiliar que contiene sólo aquellos que están activos y reinicia el contador. Por último, se
					    encarga de llamar al método MoveHelicopter, que actualiza el estado de los helicópteros activos.
		- Move Helicopters: Itera desde el inicio hasta el final de la lista de helicopteros activos. Mientras estos helicopteros estén
					  vivos y dentro de la pantalla de juego, se hacen llamadas a SpawnTrooper (en el caso de que no se haya soltado
					  aún la tropa) y se llama al método Move de la clase Helicopter.
					  Si el helicoptero es destruido o se va de la pantalla, devolvemos el helicoptero a la pool para reutilizarlo
					  y borramos el elemento de la lista auxiliar.
		- Spawn Trooper: Cada cierto tiempo, si el helicóptero aún no ha soltado a su tropa, pedimos un Trooper de la pool de tropas y
				     lo inicializamos en la posición del helicoptero en el momento de soltarlo. Añadimos este trooper a la lista auxiliar
				     e indicamos que el helicóptero ha dejado de tener trooper.
		- Trooper Routine: Similar a la rutina de los helicópteros, mientras este este vivo o no haya aterrizado, llamamos al método Fall.
					 Esto nos asegura que, salvo que lo matemos o aterrice, el soldado caerá hacia abajo desde su posición inicial.
					 Para ello, iteramos la lista de los que están activos y, en caso de muerte, devolvemos el item a la pool y
					 lo borramos de la lista auxiliar.

- Player & Bullets:
 
	- Player: Gestiona el input del jugador y los disparos.
		- Init: Inicializa las texturas de la base y la torreta, la velocidad de rotación, los temporizadores, las posiciones y los 
			  sonidos.
		- Update: En función de las teclas A y D calcula la dirección en la que debe rotar la torreta y llama al método Rotate. Además,
			    si pulsamos la tecla Space, añadiendo un delay de 0.2s para evitar el spam, llama al método Shoot. Por último, gestiona
			    las balas activas que se guardan en la lista auxiliar conforme se sacan de la pool de balas. En el caso de que una bala
			    no golpee ningún elemento y se vaya de pantalla, la devolvemos a la pool y la borramos de la lista; sino, actualizamos
			    su posición y comprobamos si golpea contra algo para sumar o restar puntuación.
		- Draw: Pinta en pantalla la base y la torreta que conforman el player, así como las balas que se disparan.
		- Reset: Hace unload de los recursos inicializados y resetea la rotación de la torreta y la puntuación del jugador.

		- Rotate: En función de la dirección obtenida en el update, siempre y cuando no se supere un ángulo máximo de 70 grados, sumamos
			    a la rotación de la torreta el resultado de multiplicar la dirección de rotación por la velocidad predefinida. Si se supera
			    el ángulo máximo, este se clampea a los valores predeterminados.
		- Shoot: Lanza el sonido de disparo y guarda el resultado de la llamada a SpawnBullet en la lista de balas activas.
		- SpawnBullet: Pide los recursos a la pool de balas y le asigna a cada una de ellas la dirección inicial en función de la torreta.
				   Inicializa la bala recogida con su posición inicial y la dirección calculada.

	- Bullet: Gestiona la actualización de las balas.
		- Init: Recibe una posición inicial y una dirección para inicializar los valores. 
		- Update: Recibe una lista de helicopteros y tropas activos sobre las que itera para comprobar si se ha chocado o no. Para ello,
			    mediante el método CheckCollisionCircleRec, se comprueba si el radio de la bala ha impactado con los bounds de las texturas
			    de los enemigos. En caso de acertar un enemigo, se llama a su correspondiente método Destroy.
			    Por último, actualizamos la posición de la bala, incrementando su posicion en x,y por la dirección recibida y la velocidad
			    asignada.
		- IsOutOfScreen: Método que devuelve un booleano que permite determinar si la bala ha salido de la pantalla de juego sin chocar
				     contra nada.
		- Draw: Pinta un punto que simula la bala.

- Enemies:

	- Helicopter: Gestiona la actualización de los helicopteros.
		- Init: Inicializa la posición y la textura del helicoptero en función de valores aleatorios. Si el valor aleatorio corresponde
			  con el asignado a la izquierda, se asgina la textura y la posición inicial asociados al lado izquierdo; de lo contrario
			  se asignan los valores del lado opuesto.
			  Asigna una velocidad inicial aleatoria entre 3 y 4, así como tiempos aleatorios para soltar la tropa entre 1 y 3. Además,
			  inicializa el resto de parámetros como los bounds, el bool IsAlive y los sonidos, entre otras cosas.
		- Move: Mientras el helicóptero está vivo, actualizamos el movimiento en función de la posición inicial, actualizamos la posición
			  de los bounds y ponemos en marcha el contador que nos permite spawnear tropas. Si no está vivo, llamamos al método ReloadTexture.
		- Reload Texture: Inicia un temporizador que espera medio segundo para que se muestre la textura de muerte en pantalla. Esto sirve
					para controlar cuándo el helicóptero se pinta o no.
		- Drop Troper: Pone el bool hasTrooper a false para que no spawnee más tropas. 
		- OutOfScreen: Devuelve un bool que nos permite saber si el helicóptero está fuera de la pantalla de juego.
		- Draw: Pinta el helicóptero siempre que el bool de la textura de muerte sea false.
		- Destroy: Lanza el sonido de explosión y reemplaza la textura del helicoptero por la textura de muerte. Marca el bool isAlive 
			     como false.
		- Unload: Da de baja las texturas y el sonido para el helicóptero cuando deja de estar activo.

	- Trooper: Gestiona la actualización de las tropas.
		- Init: Inicializa la posición del soldado en función del helicóptero al que pertenece, carga la textura, settea los bounds, la
			  velocidad y los booleanos isAlive e isGrounded.
		- Fall: Mientras la tropa está viva, actualiza la posición en Y y los bounds hasta que la tropa toca el suelo. Si la tropa deja
			  de estar viva, se llama a ReloadTexture.
		- Reload Texture: Mismo funcionamiento que el helicóptero.
		- Draw: Mismo funcionamiento que el helicóptero.
		- Destroy: Carga la textura de muerte y settea isAlive a false.
		- UnloadTextures: Da de baja las texturas del trooper cuando muere.

- Pooling: Clase genérica que optimiza los objetos en pantalla para todos aquellos que se crean y se destruyen dinámicamente.
	     Con tal de mejorar el rendimiento del juego, en vez de crear y destruir punteros en tiempo real, se ha implementado un sistema
	     de pooling. Básicamente, la clase Pool contiene una lista que almacena los objetos que hay dentro de la pool para usar aquellos
	     que no están activos y sólo crear nuevos en el caso de que la cantidad de objetos en la pool sea cero.

	     Dispone únicamente de dos métodos:
			- Get Item: Devuelve un puntero al tipo de objeto que se quiere crear o coger de la pool. Comprueba el estado de la lista
					de pooled objects para determinar si debe crear o devolver uno existente. En el caso de que no haya objetos
					disponibles en la pool, creará uno nuevo y lo devolverá. Si por el contrario hay objetos disponibles en la pool,
					devolverá el objeto que se había creado anteriormente para reutilizarlo y lo borrará de la lista de pooled objects.
			- Return Item: Método que sirve para devolver un elemento a la lista de pooled objects una vez deja de estar activo.
	     Para evitar duplicidad de código, se ha creado una clase que devuelve un tipo genérico, es decir, se puede usar esta Pool para 
	     iniciar objetos de todo tipo, independientemente de la clase de la que formen parte. Esto permite usar la misma clase Pool para crear
	     una nueva Pool de helicópteros, tropas o balas indistintamente.

