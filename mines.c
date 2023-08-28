#include <mygba.h>
#include "mines.h"
#include "menu.h"

//Grille vide
unsigned char g[30][20];

void grid(unsigned int seed) {

	unsigned char sizeX = getSizeX() + 1;
	unsigned char sizeY = getSizeY() + 1;
	unsigned char mines = getMines();

	//Reset
	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			g[posX][posY] = 0;
		}
	}

	//Aléatoire
	srand(seed);

	//Mines
	unsigned char minesPlaced = 0;
	while (minesPlaced != mines) {
		unsigned char mX = 1 + rand() % (sizeX - 1);
		unsigned char mY = 1 + rand() % (sizeY - 1);

		if (g[mX][mY] != 9) {
			if (mX + mY != 2) { //Pas la première case
				g[mX][mY] = 9;
				minesPlaced++;
			}
		}
	}
}

/*
 * 0			==>		Vide
 * 1 - 8		==>		Nombre de mines autour
 * 9			==>		Mine ici-même
 * 10			==>		Case vide révélée
 * 11 - 18		==>		Nombre révélé
 * 19			==>		Mine révélée
 * 20 + valeur	==>		Drapeau
*/
unsigned char checkMines(unsigned char x, unsigned char y) {
	unsigned char n = 0;

	if (g[x][y] == 9) {
		n = 9;
		g[x][y] = 19;
	}
	
	else {
		unsigned char i, j;

		for (i = x - 1; i < x + 2; i++) {
			for (j = y - 1; j < y + 2; j++) {
				if (g[i][j] == 9 || g[i][j] == 19) {
					n++;
				}
			}
		}
	}
	g[x][y] = 10 + n;

	return n;
}

void setGridValue(unsigned char x, unsigned char y, unsigned char value) {
	g[x][y] = value;
}

unsigned char getGridValue(unsigned char x, unsigned char y) {
	return g[x][y];
}

//Révéler tout
void reveal() {
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();

	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			drawCase(posX, posY);
		}
	}
}

void drawSave() {
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();

	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			drawCaseFromSave(posX, posY);
		}
	}
}
