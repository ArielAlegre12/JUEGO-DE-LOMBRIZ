//tengo que solucionar el problema el cual al reiniciar la partida la lombriz sigue con los datos de la anterior partida
//hay algun error al momento de reiniciar los valores de la partida

#include <stdio.h>
#include <conio.h>//con esta libreria podemos usar las funciones como getch o kbhit
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>//utilizo esta libreria para poder usar la funcion sleep y controlar la velocidad del juego
#include "lombriz.h"




int main(){
	Configuracion();
    menu();
    
    return 0;
}



