#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <locale>

#define FILAS 10
#define COLUMNAS 10

using namespace std;

// Funci�n para imprimir el tablero de juego
void imprimirTablero(char tablero[FILAS][COLUMNAS]) {
    printf("   ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf(" %d", j);
    }
    printf("\n");

    for (int i = 0; i < FILAS; i++) {
        printf("%2d ", i);
        for (int j = 0; j < COLUMNAS; j++) {
            printf("|%c", tablero[i][j]);
        }
        printf("|\n");
    }
}

// Funci�n para imprimir el gr�fico de los barcos en el tablero
void imprimirGrafico(char tablero[FILAS][COLUMNAS]) {
    printf("\nGrafico de barcos:\n");
    printf("  ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf(" %d", j);
    }
    printf("\n");

    for (int i = 0; i < FILAS; i++) {
        printf("%2d", i);
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == 'B') {
                printf("|O");
            } else {
                printf("| ");
            }
        }
        printf("|\n");
    }
}

// Funci�n para que el usuario coloque sus barcos en el tablero
void colocarBarcosUsuario(char tablero[FILAS][COLUMNAS]) {
    printf("Coloque sus barcos en el tablero.\n");

    int barcos[6][2] = {
        {2, 1}, {2, 1}, {2, 1},    // Barcos de 2x1
        {3, 1}, {3, 1},             // Barcos de 3x1
        {4, 1}                      // Barco de 4x1
    };

    for (int i = 0; i < 6; i++) {
        int fila, columna;
        int tamano = barcos[i][0];

        printf("\nIngrese la fila inicial (0-9) para el barco de tamano %dx1: ", tamano);
        scanf("%d", &fila);

        printf("Ingrese la columna inicial (0-9) para el barco de tamano %dx1: ", tamano);
        scanf("%d", &columna);

        char orientacion;
        printf("Ingrese la orientacion \n\n(V para vertical(si lo coloca de forma vertical el barco se extendera hacia abajo)\n(H para horizontal(si lo coloca de forma horizontal el barco se extendera hacia la derecha): ");
        scanf(" %c", &orientacion);

        // Verificar si las coordenadas y la orientaci�n son v�lidas
        if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
            printf("Coordenadas no v�lidas. Vuelva a intentarlo.\n");
            i--;  // Decrementar i para repetir la iteraci�n actual
            continue;  // Volver al inicio del bucle
        }

        int valido = 1;
        if (orientacion == 'V' || orientacion == 'v') {
            if (fila + tamano > FILAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila + j][columna] == 'B') {
                        valido = 0;
                        break;
                    }
                }
            }
        } else if (orientacion == 'H' || orientacion == 'h') {
            if (columna + tamano > COLUMNAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila][columna + j] == 'B') {
                        valido = 0;
                        break;
                    }
                }
            }
        } else {
            valido = 0;
        }

        // Si las coordenadas u orientaci�n no son v�lidas, se solicita nuevamente al usuario
        if (!valido) {
            printf("Posici�n no v�lida. Vuelva a intentarlo.\n");
            i--;  // Decrementar i para repetir la iteraci�n actual
            continue;  // Volver al inicio del bucle
        }

        // Colocar el barco en el tablero seg�n las coordenadas y la orientaci�n dadas
        if (orientacion == 'V' || orientacion == 'v') {
            for (int j = 0; j < tamano; j++) {
                tablero[fila + j][columna] = 'B';
            }
        } else if (orientacion == 'H' || orientacion == 'h') {
            for (int j = 0; j < tamano; j++) {
                tablero[fila][columna + j] = 'B';
            }
        }

        imprimirGrafico(tablero);
    }
}

// Funci�n para que la m�quina coloque sus barcos en el tablero
void colocarBarcosMaquina(char tablero[FILAS][COLUMNAS]) {
    int barcos[6][2] = {
        {2, 1}, {2, 1}, {2, 1},    // Barcos de 2x1
        {3, 1}, {3, 1},             // Barcos de 3x1
        {4, 1}                      // Barco de 4x1
    };

    srand(time(NULL));

    for (int i = 0; i < 6; i++) {
        int fila, columna;
        int tamano = barcos[i][0];

        // Generar coordenadas aleatorias para la posici�n del barco
        fila = rand() % FILAS;
        columna = rand() % COLUMNAS;

        // Generar orientaci�n aleatoria (0 para vertical, 1 para horizontal)
        int orientacion = rand() % 2;

        int valido = 1;
        if (orientacion == 0) {
            if (fila + tamano > FILAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila + j][columna] == 'B') {
                        valido = 0;
                        break;
                    }
                }
            }
        } else if (orientacion == 1) {
            if (columna + tamano > COLUMNAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila][columna + j] == 'B') {
                        valido = 0;
                        break;
                    }
                }
            }
        }

        // Si las coordenadas y orientaci�n generadas no son v�lidas, se repite el ciclo
        if (!valido) {
            i--;  // Decrementar i para repetir la iteraci�n actual
            continue;  // Volver al inicio del bucle
        }

        // Colocar el barco en el tablero seg�n las coordenadas y la orientaci�n generadas
        if (orientacion == 0) {
            for (int j = 0; j < tamano; j++) {
                tablero[fila + j][columna] = 'B';
            }
        } else if (orientacion == 1) {
            for (int j = 0; j < tamano; j++) {
                tablero[fila][columna + j] = 'B';
            }
        }
    }
}
int bomba=40;
// Funci�n para que el usuario realice un turno de disparo
void jugarTurnoUsuario(char tableroMaquina[FILAS][COLUMNAS], char tableroDisparosMaquina[FILAS][COLUMNAS], int *contadorUsuario) {
    int fila, columna;
	printf("la bomba va a caer dentro de %d turnos",bomba--);
    printf("\nEs tu turno. Ingresa las coordenadas del disparo:\n");
    printf("Fila: ");
    scanf("%d", &fila);
    printf("Columna: ");
    scanf("%d", &columna);

    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
        printf("Coordenadas no v�lidas. Intenta nuevamente.\n");
        return;
    }

    if (tableroMaquina[fila][columna] == 'B') {
        printf("�Le diste a uno de los barcos enemigos!\n");
        tableroDisparosMaquina[fila][columna] = 'X';
        (*contadorUsuario)++;
    } else {
        printf("Disparo fallido.\n");
        tableroDisparosMaquina[fila][columna] = 'O';
    }

    imprimirTablero(tableroDisparosMaquina);
}

// Funci�n para que la m�quina realice un turno de disparo
void jugarTurnoMaquina(char tableroUsuario[FILAS][COLUMNAS], char tableroDisparosUsuario[FILAS][COLUMNAS], int *contadorMaquina) {
    int fila, columna;

    printf("\nTurno de la m�quina...\n");

    do {
        // Generar coordenadas aleatorias para el disparo de la m�quina
        fila = rand() % FILAS;
        columna = rand() % COLUMNAS;
    } while (tableroUsuario[fila][columna] == 'X' || tableroUsuario[fila][columna] == 'O');

    if (tableroUsuario[fila][columna] == 'B') {
        printf("�La m�quina le dio a uno de tus barcos!\n");
        tableroUsuario[fila][columna] = 'X';
        (*contadorMaquina)++;
    } else {
        printf("La m�quina dispar� y fall�.\n");
        tableroUsuario[fila][columna] = 'O';
    }

    imprimirTablero(tableroUsuario);
}

int main() {
    system("color 02");
    printf("los barcos disponibles son: 3 barcos de 2 m�dulos, 2 barcos de 3 m�dulos y un barco de 4 m�dulos \n\n");

    // Crear tablero de juego
    char tableroUsuario[FILAS][COLUMNAS];
    char tableroMaquina[FILAS][COLUMNAS];
    char tableroDisparosUsuario[FILAS][COLUMNAS];
    char tableroDisparosMaquina[FILAS][COLUMNAS];

    // Inicializar tableros
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tableroUsuario[i][j] = ' ';
            tableroMaquina[i][j] = ' ';
            tableroDisparosUsuario[i][j] = ' ';
            tableroDisparosMaquina[i][j] = ' ';
        }
    }

    // Colocar barcos del usuario
    colocarBarcosUsuario(tableroUsuario);

    // Colocar barcos de la m�quina
    colocarBarcosMaquina(tableroMaquina);

    int contadorUsuario = 0;
    int contadorMaquina = 0;
	int seleccion;
    while (contadorUsuario < 12 || contadorMaquina < 12 || bomba!=0) {
        jugarTurnoUsuario(tableroMaquina, tableroDisparosMaquina, &contadorUsuario);

        if (contadorUsuario >= 12) {
            break;
        }
        
        if(bomba==0)
        {
        	srand(time(NULL));  // Inicializar la semilla aleatoria

    		// Generar un n�mero aleatorio entre 1 y 2
   			 seleccion = rand() % 2 + 1;
   			 
   			 break;
		}

        jugarTurnoMaquina(tableroUsuario, tableroDisparosUsuario, &contadorMaquina);
    }

    if (contadorUsuario >= 12 || seleccion==1) {
        printf("�Felicidades! Has ganado el juego.\n");
    } 
	
	if(contadorMaquina >= 12 || seleccion==2)
	{
        printf("La m�quina ha ganado el juego. �Int�ntalo de nuevo!\n");
    }
    
    if(seleccion==1)
    {
    	printf("la bomba atomica cayo en el tablero rival\n");
	}

     if(seleccion==2)
    {
    	printf("la bomba atomica cayo tu tablero\n");
	}
   

    return 0;
}

