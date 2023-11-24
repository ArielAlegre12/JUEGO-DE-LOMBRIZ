/*este es un archivo .h que contiene todas las funciones del juego, luego
las llamo en otro archivo .c donde tiene incluida todas las otras librerias
*/

//los tipos de datos "enum" sirven para definir un tipo de dato con un conjunto de constantes con nombres
//son constantes ennumeradas que representan un valor finito de valores
#define ANCHO 20
#define ALTURA 20



bool gameover; //booleano para el gameOver
int x, y, frutaX, frutaY, puntaje; //variables de posicionamiento del gusano y fruta, y variable de puntos
int colaX[100], colaY[100]; //usamos estos arreglos para saber el posicionamiento del gusano y poder dibujarlo
int largoCola; //variable para el largo de la cola del gusano
enum Direcciones { ARRIBA, ABAJO, IZQUIERDA, DERECHA };//lista de constantes en las cuales se les asignara la direccion del gusano
enum Direcciones direccion;
int mayorPunto = 0;


void Configuracion();
void Dibujar();
void Input();
void Logica();
void juego();
void menu();




void Configuracion() {
    gameover = false;
    direccion = DERECHA;
    x = ANCHO / 2;
    y = ALTURA / 2;
    frutaX = rand() % ANCHO;
    frutaY = rand() % ALTURA;
    puntaje = 0;
    largoCola = 0; // Reiniciar la longitud del gusano
}

void Dibujar() {
    system("cls"); //esto lo que hace es limpiar la pantalla para cargar la "imagen" del juego
    for (int i = 0; i < ANCHO + 2; i++)
        printf("#");//este for va ir imprimiendo "#" en el borde superior del juego
    printf("\n");
//aca entra un for anidado para darle el cuerpo al juego
//para cada posicion del bucle se consideran condiciones.
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < ANCHO; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)//cuando la posicion de i y j es igual a y y x, entonces se imprime
                printf("O");    //O en representacion de la cabeza del gusano, porque es la posicion
            else if (i == frutaY && j == frutaX) //aqui basicamente es cuando la posicion es igual a la asignacion de la "F" 
                printf("F");                     //que significa la "fruta"
            else {
                bool printCola = false;
                for (int k = 0; k < largoCola; k++) {//aca si ninguna de las otras coincide, se comprueba si no es parte de la cola
                    if (colaX[k] == j && colaY[k] == i) { 
                        printf("o");//imprime parte del cuerpo
                        printCola = true; 
                    }
                }
                if (!printCola) //si no es asi
                    printf(" ");//imprime un espacio en blanco
            }

            if (j == ANCHO - 1)//esta line lo que hace es ir dibujando los bordes de la izquierda y derecha
                printf("#");// una vez pregunto si esta al final de la linea del juego, imprime "#"
        }
        printf("\n");
    }

    for (int i = 0; i < ANCHO + 2; i++)//aca basicamente lo que hago es generar el borde inferior
        printf("#");
    printf("\n");
    printf("Puntaje: %d", puntaje);//muestro el puntaje, y este ira incrementando cada que el gusano coma una fruta
    
    
    
}

void Input() { //esta funcion es para asignar los botones con los cuales se jugaran
    if (_kbhit()) {//esta es una funcion de la libreria conio, es basicamente para leer el teclado de windows o eso entendi
        switch (_getch()) {//aca uso getch para que lea la tecla presionada sin el ENTER 
            case 'w': //luego por cada caso se le asigna la direccion al movimiento del gusano
                direccion = ARRIBA;
                break;
            case 's':
                direccion = ABAJO;
                break;
            case 'a':
                direccion = IZQUIERDA;
                break;
            case 'd':
                direccion = DERECHA;
                break;
            case 'x':
                gameover = true;
                break;
        }
    }
}

void Logica() { //esta funcion es fundamental, ya que es la que actualiza el estado del gusano dependiendo de sus movimientos
    int prevX = colaX[0]; //o de si comio o no la fruto, decide si el juego continua o no.
    int prevY = colaY[0];
    int tempX, tempY;
    colaX[0] = x;
    colaY[0] = y;
    for (int i = 1; i < largoCola; i++) { //en este bucle lo que hace es ir actualizando la cola, entonces 
        tempX = colaX[i];                //en el juego da la sensacion de que el gusano se arrastra, 
        tempY = colaY[i];               //pero en realidad cada segmento de la cola se mueve a la 
        colaX[i] = prevX;              //posicion del segmento anterior
        colaY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch (direccion) {//segun sea el movimiento del gusano, se actualizan sus coordenadas
        case ARRIBA:
            y--;
            break;
        case ABAJO:
            y++;
            break;
        case IZQUIERDA:
            x--;
            break;
        case DERECHA:
            x++;
            break;
        default:
            break;
    }

    if (x >= ANCHO || x < 0 || y >= ALTURA || y < 0) //verifica si la cabeza del gusano alcanzo los limites del juego
        gameover = true;

    for (int i = 0; i < largoCola; i++) {
        if (colaX[i] == x && colaY[i] == y) //se verifica si el cuerpo del gusano choco consigo mismo
            gameover = true;
    }

    if (x == frutaX && y == frutaY) { //aca se comprueba si la cabeza del gusano alcanzo la fruta
        puntaje += 10; 
        frutaX = rand() % ANCHO; //genera una nueva 
        frutaY = rand() % ALTURA;//posicion aleatoria
        largoCola++; 
    }
}

void juego(){
	
	while (!gameover) {//un bucle para darle continuidad al juego mientras no sea gameOver
		
        Dibujar(); //actualiza y muestra el estado actual del juego, dibujando el area del juego, la pos del gusano, la fruta y el puntaje
        Input(); //captura la entrada por teclado 
        Logica();//actualiza la posicion del gusano, y va verificando las colisiones y limites del juego
        Sleep(100); // Retraso para el movimiento, se puede ajustar para cambiar la velocidad del juego
    }
    printf("\nGame Over!\n");
    if(mayorPunto<puntaje){ //va recolectando el mayor puntaje
    	mayorPunto = puntaje;
	}
    Configuracion();
}

void menu(){ //menu de interaccion para el usuario
	int opcion;
	
	do{
		printf("\n----El Gloton----\n");
		printf("1 - jugar\n");
		printf("2 - Ver mayor Puntuacion\n");
		printf("3 - Salir\n");
		printf(" ");
		scanf("%d", &opcion);
		
		
		switch(opcion){
			case 1:
				juego();
				break;
			case 2:
				printf("\nLa mejor puntuacion es: %d\n\n", mayorPunto);
				break;
			case 3:
				printf("\nSaliendo***__***\n");
				break;
			default:
				printf("\nOpcion incorrecta. Intenta de nuevo\n");
				break;
		}
	}while(opcion != 3);
}
