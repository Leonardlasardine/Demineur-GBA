#include <mygba.h>
#include "mines.h"
#include "menu.h"

//Grille vide
unsigned char g[99][99];

void grid(unsigned int seed) {

	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();
	unsigned char mines = getMines();

	//Reset
	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			g[posX][posY] = 0;
		}
	}

	//Al�atoire
	srand(seed);

	//Mines
	unsigned char minesPlaced = 0;
	while (minesPlaced != mines) {
		unsigned char mX = rand() % sizeX;
		unsigned char mY = rand() % sizeY;

		if (g[mX][mY] != 1) {
			g[mX][mY] = 1;
			minesPlaced++;
		}
	}
}

/*
 * 0		==>		Vide
 * 1 - 8	==>		Nombre de mines autour
 * 9		==>		Mine ici-m�me
*/
unsigned char checkMines(unsigned char x, unsigned char y) {
	unsigned char n = 0;

	if (g[x][y] == 1) {
		n = 9;
	}
	
	else {//PROBLEME PREMIERE LIGNE ET COLONE
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

//R�v�ler tout
void reveal () {
	
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();

	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			drawCase(posX, posY);
		}
	}
}
