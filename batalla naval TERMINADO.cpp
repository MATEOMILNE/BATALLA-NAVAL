#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <locale>

#define FILAS 10
#define COLUMNAS 10

using namespace std;

// Función para imprimir el tablero de juego
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

// Función para imprimir el gráfico de los barcos en el tablero
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

// Función para que el usuario coloque sus barcos en el tablero
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

        // Verificar si las coordenadas y la orientación son válidas
        if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
            printf("Coordenadas no válidas. Vuelva a intentarlo.\n");
            i--;  // Decrementar i para repetir la iteración actual
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

        // Si las coordenadas u orientación no son válidas, se solicita nuevamente al usuario
        if (!valido) {
            printf("Posición no válida. Vuelva a intentarlo.\n");
            i--;  // Decrementar i para repetir la iteración actual
            continue;  // Volver al inicio del bucle
        }

        // Colocar el barco en el tablero según las coordenadas y la orientación dadas
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

// Función para que la máquina coloque sus barcos en el tablero
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

        // Generar coordenadas aleatorias para la posición del barco
        fila = rand() % FILAS;
        columna = rand() % COLUMNAS;

        // Generar orientación aleatoria (0 para vertical, 1 para horizontal)
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

        // Si las coordenadas y orientación generadas no son válidas, se repite el ciclo
        if (!valido) {
            i--;  // Decrementar i para repetir la iteración actual
            continue;  // Volver al inicio del bucle
        }

        // Colocar el barco en el tablero según las coordenadas y la orientación generadas
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
// Función para que el usuario realice un turno de disparo
void jugarTurnoUsuario(char tableroMaquina[FILAS][COLUMNAS], char tableroDisparosMaquina[FILAS][COLUMNAS], int *contadorUsuario) {
    int fila, columna;
	printf("la bomba va a caer dentro de %d turnos",bomba--);
    printf("\nEs tu turno. Ingresa las coordenadas del disparo:\n");
    printf("Fila: ");
    scanf("%d", &fila);
    printf("Columna: ");
    scanf("%d", &columna);

    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
        printf("Coordenadas no válidas. Intenta nuevamente.\n");
        return;
    }

    if (tableroMaquina[fila][columna] == 'B') {
        printf("¡Le diste a uno de los barcos enemigos!\n");
        tableroDisparosMaquina[fila][columna] = 'X';
        (*contadorUsuario)++;
    } else {
        printf("Disparo fallido.\n");
        tableroDisparosMaquina[fila][columna] = 'O';
    }

    imprimirTablero(tableroDisparosMaquina);
}

// Función para que la máquina realice un turno de disparo
void jugarTurnoMaquina(char tableroUsuario[FILAS][COLUMNAS], char tableroDisparosUsuario[FILAS][COLUMNAS], int *contadorMaquina) {
    int fila, columna;

    printf("\nTurno de la máquina...\n");

    do {
        // Generar coordenadas aleatorias para el disparo de la máquina
        fila = rand() % FILAS;
        columna = rand() % COLUMNAS;
    } while (tableroUsuario[fila][columna] == 'X' || tableroUsuario[fila][columna] == 'O');

    if (tableroUsuario[fila][columna] == 'B') {
        printf("¡La máquina le dio a uno de tus barcos!\n");
        tableroUsuario[fila][columna] = 'X';
        (*contadorMaquina)++;
    } else {
        printf("La máquina disparó y falló.\n");
        tableroUsuario[fila][columna] = 'O';
    }

    imprimirTablero(tableroUsuario);
}

int main() {
    system("color 02");
    printf("los barcos disponibles son: 3 barcos de 2 módulos, 2 barcos de 3 módulos y un barco de 4 módulos \n\n");

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

    // Colocar barcos de la máquina
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

    		// Generar un número aleatorio entre 1 y 2
   			 seleccion = rand() % 2 + 1;
   			 
   			 break;
		}

        jugarTurnoMaquina(tableroUsuario, tableroDisparosUsuario, &contadorMaquina);
    }

    if (contadorUsuario >= 12 || seleccion==1) {
        printf("¡Felicidades! Has ganado el juego.\n");
    } 
	
	if(contadorMaquina >= 12 || seleccion==2)
	{
        printf("La máquina ha ganado el juego. ¡Inténtalo de nuevo!\n");
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

