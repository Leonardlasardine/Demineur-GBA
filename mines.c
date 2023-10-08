#include <mygba.h>
#include "mines.h"
#include "menu.h"
#include "view.h"

//Grille vide
unsigned char g[31][21];
//Le nombre de mines plac�es moins les drapeaux (m�me si mals plac�s)
unsigned char minesLeft;

void resetGrid() {
	unsigned char posY, posX;
	for (posX = 0; posX < 31; posX++) {
		for (posY = 0; posY < 21; posY++) {
			g[posX][posY] = 0;
		}
	}
}

void grid(unsigned int seed, unsigned char x, unsigned char y) {
	unsigned char sizeX = getSizeX() + 1;
	unsigned char sizeY = getSizeY() + 1;
	unsigned char mines = getMines();
	minesLeft = mines;

	//Reset
	resetGrid();

	//Al�atoire
	srand(seed);

	//Mines
	unsigned char minesPlaced = 0;
	while (minesPlaced != mines) {
		unsigned char mX = 1 + rand() % (sizeX - 1);
		unsigned char mY = 1 + rand() % (sizeY - 1);

		if (g[mX][mY] != 9) {
			if (mY*sizeX + mX != y*sizeX + x) { //Pas la premi�re case
				g[mX][mY] = 9;
				minesPlaced++;
			}
		}
	}
}

/*
 * 0			==>		Vide
 * 9			==>		Mine ici-m�me
 * 10			==>		Case vide r�v�l�e
 * 11 - 18		==>		Nombre r�v�l�
 * 19			==>		Mine r�v�l�e
 * 21			==>		Drapeau sur une mine
 * 22			==>		Drapeau sur une case pas r�v�l�e
*/
unsigned char checkMines(unsigned char x, unsigned char y) {
	unsigned char n = 0;

	if (g[x][y] == 9 || g[x][y] == 21) {
		n = 9;
		g[x][y] = 19;
	}
	
	else {
		unsigned char i, j;

		for (i = x - 1; i < x + 2; i++) {
			for (j = y - 1; j < y + 2; j++) {
				if (g[i][j] == 9 || g[i][j] == 19 || g[i][j] == 21) {
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

//R�v�ler tout
void reveal() {
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();

	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			if(getGridValue(posX + 1, posY + 1) < 10) {
				drawCase(posX, posY);
			} else {
				drawCaseFromSave(posX, posY);
			}
		}
	}
}

void drawSave() {
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();

	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			if(getGridValue(posX + 1, posY + 1) < 10) {
				drawUnrevealedCase(posX, posY);
			} else {
				drawCaseFromSave(posX, posY);
			}
		}
	}
}

unsigned char getMinesLeft() {
	return minesLeft;
}

void setMinesLeft(unsigned char value) {
	minesLeft = value;
}
