#include <mygba.h>
#include "mines.h"
#include "main.h"

unsigned char y[SIZE_X+2][SIZE_Y+2];

int grid()  {
	
	//Grille vide
	//unsigned char y [SIZE_X+2][SIZE_Y+2] = {0};

	//Mines
	unsigned char mines = 0;
	while (mines != MINES) {
		unsigned char mX = rand() % SIZE_Y+2;//PAS BON
		unsigned char mY = rand() % SIZE_X+2;

		if (y[mX][mY] != 1) {
			y[mX][mY] = 1;
			mines++;
		}
	}

	//Print
	if(TEXT_MODE) {
		unsigned char posY, posX;
		for (posX = 0; posX < SIZE_X; posX++) {
			for (posY = 0; posY < SIZE_Y; posY++) {
				ham_DrawText(posX, posY, "%d", y[posY][posX]);
			}
		}
		
		return 0;
	}
}

/*
 * 0		==>		Vide
 * 1 - 8	==>		Nombre de mines autour
 * 9		==>		Mine ici-même
*/
unsigned char checkMines(unsigned char x, unsigned char y) { //PROBLEME ICI POUR LIRE LE TABLEAU
	unsigned char n = 0;

	if (/*y[x][y] == */1) {
		n = 0;
	}
	
	
	/* else {
		unsigned char i, j;

		for (i = x - 1; i < x + 2; i++) {
			for (j = y - 1; j < y + 2; j++) {
				if (y[&i][&j] == 1) {
					n++;
				}
			}
		}
	}*/

	return n;
}
