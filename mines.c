#include <mygba.h>
#include "mines.h"
#include "menu.h"
#include "view.h"
#include "gameOver.h"

#include "font.h"
#include "keyboard.h"

//Grille vide
unsigned char g[31][21];

//Cases non-révélées moins les mines (pour éviter de recalculer à chaque fois)
unsigned short unrevealedCase;
//Le nombre de mines sans drapeaux
unsigned char minesLeft;
//Le nombre de fautes
unsigned short wrongFlags;

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
	unrevealedCase = (sizeX - 1) * (sizeY - 1) - mines;
	wrongFlags = 0;

	//Reset
	resetGrid();

	//Aléatoire
	srand(seed);

	//Mines
	unsigned char minesPlaced = 0;
	while (minesPlaced != mines) {
		unsigned char mX = 1 + rand() % (sizeX - 1);
		unsigned char mY = 1 + rand() % (sizeY - 1);

		if (g[mX][mY] != 9) {
			if (mY*sizeX + mX != y*sizeX + x) { //Pas la première case
				g[mX][mY] = 9;
				minesPlaced++;
			}
		}
	}
}

/*
 * 0			==>		Vide
 * 9			==>		Mine ici-même
 * 10			==>		Case vide révélée
 * 11 - 18		==>		Nombre révélé
 * 19			==>		Mine révélée
 * 20			==>		Drapeau sur une case pas révélée
 * 29			==>		Drapeau sur une mine
*/
unsigned char checkMines(unsigned char x, unsigned char y) {
	unsigned char n = 0;

	if (g[x][y] == 9 || g[x][y] == 29) {
		n = 9;
		g[x][y] = 19;
	}
	
	else {
		unsigned char i, j;

		for (i = x - 1; i < x + 2; i++) {
			for (j = y - 1; j < y + 2; j++) {
				if (g[i][j] == 9 || g[i][j] == 19 || g[i][j] == 29) {
					n++;
				}
			}
		}
	}
	g[x][y] = 10 + n;

	return n;
}

//Révéler tout
void reveal() {
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();

	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			unsigned char n = getGridValue(posX + 1, posY + 1);
			if(n < 10) {
				drawCase(posX, posY);
			} else if (n == 20) {
				//Bitmap drapeaux faux
				setGridValue(posX + 1, posY + 1, 18);
				drawCaseFromSave(posX, posY);
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

//Compte le nombre de cases d'une certaine valeur
unsigned short countCases(unsigned char value) {
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();
	unsigned char n = 0;

	unsigned char i, j;
	for (i = 0; i < sizeX; i++) {
		for (j = 0; j < sizeY; j++) {
			if (getGridValue(i + 1, j + 1) == value) {
				n ++;
			}
		}
	}
	return n;
}

//Compte le nombre de cases non-révélées
unsigned short countUnrevealed() {
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();
	unsigned char n = 0;
	unsigned char v = 0;

	unsigned char i, j;
	for (i = 0; i < sizeX; i++) {
		for (j = 0; j < sizeY; j++) {
			v = getGridValue(i + 1, j + 1);
			if (v > 9 && v < 20) {
				n ++;
			}
		}
	}
	return sizeX * sizeY - getMines() - n;
}

//Vérifier si la partie est gagnée
void checkWon() {

	//Affichage temporaire
	/*unsigned char m = getMinesLeft();
	if (m != 0) {
		m -= 1;
	} else {
		m = 9;
	}
	//Mines restantes
	drawChar(0, 0, 39);
	drawChar(0, 0, m);

	//Cases restantes
	drawChar(0, 36, 39);
	drawChar(0, 36, countCases(0));
	
	//PAs reveles
	drawChar(0, 75, 39);
	drawChar(0, 75, unrevealedCase);

	
	//erreurs
	drawChar(0, 96, 39);
	drawChar(0, 96, wrongFlags);*/

	//Si aucun mauvais drapeaux
	if (wrongFlags == 0) {
		//Si tous les drapeaux placés OU toutes les cases révélées
		if (minesLeft == 0 || unrevealedCase == 0) {
			//GAGNE
			unsigned char winText [8] = {16, 10, 16, 23, 14, 36, 36, 36};
			unsigned char pos = 0; //Varaible inutile mais nécessaire
			writePseudo(winText, &pos);
		}
	}
}

void setGridValue(unsigned char x, unsigned char y, unsigned char value) {
	g[x][y] = value;
}

unsigned char getGridValue(unsigned char x, unsigned char y) {
	return g[x][y];
}

unsigned char getMinesLeft() {
	return minesLeft;
}

void setMinesLeft(unsigned char value) {
	minesLeft = value;
}

//Pour le menu pause (joueur)
signed short getFlagsLeft() {
	return getMines() - countCases(20) - countCases(29);
}

void countRevealedCase() {
	unrevealedCase -= 1;
}

void setUnrevealedCase(unsigned short value) {
	unrevealedCase = value;
}

void setWrongFlags(unsigned short value) {
	wrongFlags = value;
}

unsigned short getWrongFlags() {
	return wrongFlags;
}
