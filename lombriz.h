#define ANCHO 20
#define ALTURA 20



bool gameover;
int x, y, frutaX, frutaY, puntaje;
int colaX[100], colaY[100];
int largoCola;
enum Direcciones { ARRIBA, ABAJO, IZQUIERDA, DERECHA };
enum Direcciones direccion;
int mayorPunto = 0;


void Configuracion();
void Dibujar();
void Input();
void Logica();
void juego();
//int mayorPuntaje(int);
void menu();

/*void mayorPuntaje(int pPuntaje){
	if(pPuntaje < mayorPunto){
		mayorPunto = pPuntaje;
	}
	
}*/



void Configuracion() {
    gameover = false;
    direccion = DERECHA;
    x = ANCHO / 2;
    y = ALTURA / 2;
    frutaX = rand() % ANCHO;
    frutaY = rand() % ALTURA;
    puntaje = 0;
}

void Dibujar() {
    system("cls");
    for (int i = 0; i < ANCHO + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < ANCHO; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == frutaY && j == frutaX)
                printf("F");
            else {
                bool printCola = false;
                for (int k = 0; k < largoCola; k++) {
                    if (colaX[k] == j && colaY[k] == i) {
                        printf("o");
                        printCola = true;
                    }
                }
                if (!printCola)
                    printf(" ");
            }

            if (j == ANCHO - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < ANCHO + 2; i++)
        printf("#");
    printf("\n");
    printf("Puntaje: %d", puntaje);
    
    
    
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
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

void Logica() {
    int prevX = colaX[0];
    int prevY = colaY[0];
    int tempX, tempY;
    colaX[0] = x;
    colaY[0] = y;
    for (int i = 1; i < largoCola; i++) {
        tempX = colaX[i];
        tempY = colaY[i];
        colaX[i] = prevX;
        colaY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch (direccion) {
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

    if (x >= ANCHO || x < 0 || y >= ALTURA || y < 0)
        gameover = true;

    for (int i = 0; i < largoCola; i++) {
        if (colaX[i] == x && colaY[i] == y)
            gameover = true;
    }

    if (x == frutaX && y == frutaY) {
        puntaje += 10;
        frutaX = rand() % ANCHO;
        frutaY = rand() % ALTURA;
        largoCola++;
    }
}

void juego(){
	
	while (!gameover) {
		
        Dibujar();
        Input();
        Logica();
        Sleep(100); // Retraso para el movimiento, puedes ajustarlo para cambiar la velocidad
    }
    printf("\nGame Over!\n");
    if(mayorPunto<puntaje){
    	mayorPunto = puntaje;
	}
    Configuracion();
}

void menu(){
	int opcion;
	
	do{
		printf("\n----El Gloton----\n");
		printf("1 - jugar\n");
		printf("2 - Ver mayor Puntuacion\n");
		printf("3 - Salir\n");
		scanf("%d", &opcion);
		
		switch(opcion){
			case 1:
				juego();
				break;
			case 2:
				printf("\nLa mejor puntuacion es: %d", mayorPunto);
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