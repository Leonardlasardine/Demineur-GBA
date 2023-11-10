#include "font.h"
#include "bitmaps.h"
#include "view.h"

//Mot stocké sous forme d'entiers de 0 à 38 et non sous forme de texte
//Caractères dans l'ordre du fichier font.bmp

void drawChar(unsigned char x, unsigned char y, unsigned char character) {

	unsigned char i, j;
	for (i = y; i < 16 + y; i++) {
		for (j = x; j < 16 + x; j++) {
			unsigned short pixel = font_Bitmap[(i - y) * 16 + (j - x)+character*256];
			if (pixel != 0x0000) {
				drawPixel(j, i, pixel);
			}
		}
	}
}

void drawKeys() {
	unsigned char i, j, n, decal, firstLine;
	n = 0;
	decal = 0;
	firstLine = 32;
	for (i = 65; i < 125; i+=20) {//Hauteur
		for (j = 24; j < 216 - firstLine; j+=16) {//Longueur
			drawChar(j + decal, i, n);
			n++;
		}
		firstLine = 0;
		if (n < 13) {
			decal+= 4;
		} else {
			decal-= 4;
		}
	}
	//Dernière ligne
	for (j = 28; j < 186; j+=16) {//Longueur
		if (j == 76) {
			j += 80;
		}
		drawChar(j, i, n);
		n++;
	}
}

unsigned char keyPressed(unsigned char x, unsigned char y, unsigned char *pos) {

	unsigned char key = 39;	//Aucune
	unsigned char decal = 0;

	//Actions
	if (y == 0 && x == 10) {
		//SUPPRIMER
		if (*pos > 0) {
			remove(pos);
			key = 40;
		}
	} else if (y == 3 && x == 3) {
		//ESPACE
		if (*pos < 8) {
			emptySquare(*pos + 1);
			*pos += 1;
		} else {
			remove(pos);
			*pos += 1;
		}
	} else if (y == 3 && x == 10) {
		//VALIDER
		key = 41;
	}

	//LETTRES
	else {
		if (y > 0 ){
			decal += 2;
		}
		if (y == 3 && x > 7){
			decal += 5;
		}

		key = y*12 + x - decal;

		if (*pos == 8) {
			remove(pos);
		} else {
			emptySquare(*pos + 1);
		}

		drawChar(28 + *pos*24, 14, key);
		*pos += 1;
	}
	return key;
}

//SUPPRIMER
void remove(unsigned char *pos) {
	emptySquare(*pos);
	*pos -= 1;
}

void emptySquare(unsigned char pos) {
	//Carré vide 14*14
	unsigned short square[1600];
	unsigned char i, j;
	unsigned char posStart = 28 + (pos - 1)*24;
	unsigned short n = 0;
	for (i = 14; i < 28; i++) {
		for (j = posStart; j < posStart + 14; j++) {
			square[n] = pseudo_Bitmap[i * 240 + j];
			n++;
		}
	}
	drawBitmap(posStart, 14, square, 14);
}
