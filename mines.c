#include <mygba.h>
#include "mines.h"
#include "main.h"

//Grille vide
unsigned char g[SIZE_X+2][SIZE_Y+2];

void grid(unsigned int seed) {

	//Reset
	unsigned char posY, posX;
	for (posX = 0; posX < 16; posX++) {
		for (posY = 0; posY < 16; posY++) {
			g[posX][posY] = 0;
		}
	}

	//Aléatoire
	srand(seed);

	//Mines
	unsigned char mines = 0;
	while (mines != MINES) {
		unsigned char mX = rand() % SIZE_Y;
		unsigned char mY = rand() % SIZE_X;

		if (g[mX][mY] != 1) {
			g[mX][mY] = 1;
			mines++;
		}
	}
}

/*
 * 0		==>		Vide
 * 1 - 8	==>		Nombre de mines autour
 * 9		==>		Mine ici-même
*/
unsigned char checkMines(unsigned char x, unsigned char y) {
	unsigned char n = 0;

	if (g[x][y] == 1) {
		n = 9;
	}
	
	else {
		unsigned char i, j;

		for (i = x - 1; i < x + 2; i++) {
			for (j = y - 1; j < y + 2; j++) {
				if (g[i][j] == 1) {
					n++;
				}
			}
		}
	}

	return n;
}

//Révéler tout
void reveal () {
	unsigned char posY, posX;
	for (posX = 0; posX < 16; posX++) {
		for (posY = 0; posY < 16; posY++) {
			drawCase(posX, posY);
		}
	}
}
