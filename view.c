#include "view.h"
#include "mines.h"
#include "menu.h"

unsigned short* videoBuffer = (unsigned short*) 0x6000000;

unsigned char size = 0;
unsigned short case_Bitmap[1600] = {};
unsigned char sizeX;
unsigned char sizeY;
unsigned char pixelX;
unsigned char pixelY;

unsigned char getBitmapSize() {
	switch(getDifficulty()) {
		case 0:
			return 40;
			break;
		case 1:
			return 20;
			break;
		case 2:
			return 16;
			break;
		case 3:
			return 10;
			break;
		case 4:
			return 8;
			break;
	}
	return 40;
}

void setBitmaps() {
	size = getBitmapSize();
	setCaseBitmap();
	sizeX = getSizeX();
	sizeY = getSizeY();
	pixelX = 240/sizeX;
	pixelY = 160/sizeY;
}

void setCaseBitmap() {
	switch (getDifficulty()) {
		case 0 :
			memcpy(case_Bitmap, case_40_Bitmap, ARRAY_40);
			break;
		case 1 :
			memcpy(case_Bitmap, case_20_Bitmap, ARRAY_20);
			break;
		case 2 :
			memcpy(case_Bitmap, case_16_Bitmap, ARRAY_16);
			break;
		case 3 :
			memcpy(case_Bitmap, case_10_Bitmap, ARRAY_10);//PK
			break;
		case 4 :
			memcpy(case_Bitmap, case_8_Bitmap, ARRAY_8);
			break;
	}
}

void cursor (unsigned char x, unsigned char y, unsigned short c) {

	if (x == sizeX - 1) { //Côté droit
		if (y == sizeY - 1) { //Coin en bas à droite
			drawLine(x*pixelX - 1, y*pixelY - 1, pixelX + 1, 2, c);			//HAUT
			drawLine(x*pixelX, (y*pixelY + pixelY)-1, pixelX + 1, 1, c);	//BAS
		} else {
			if(y == 0) { //Côté en haut à droite
				drawLine(x*pixelX, 0, pixelX + 1, 1, c);					//HAUT
			} else { //Côté droit
				drawLine(x*pixelX - 1, y*pixelY - 1, pixelX + 1, 2, c);		//HAUT
			}
			drawLine(x*pixelX, (y*pixelY + pixelY)-1, pixelX, 2, c);	//BAS
		}
		drawLine(x*pixelX - 1, y*pixelY, 2, pixelY + 1, c);					//GAUCHE
		drawLine((x*pixelX + pixelX)-1, y*pixelY, 1, pixelY, c);			//DROITE
	} else if (x == 0) { //Côté gauche
		if (y == sizeY - 1) { //Coin en bas à gauche
			drawLine(0, y*pixelY - 1, pixelX + 1, 2, c);				//HAUT
			drawLine(0, (y*pixelY + pixelY)-1, pixelX + 1, 1, c);		//BAS
		} else {
			if(y == 0) { //Côté en haut à gauche
				drawLine(0, 0, pixelX + 1, 1, c);						//HAUT
			} else { //Côté gauche
				drawLine(0, y*pixelY - 1, pixelX + 1, 2, c);			//HAUT
			}
			drawLine(0, (y*pixelY + pixelY)-1, pixelX + 1, 2, c);		//BAS
		}
		drawLine(0, y*pixelY, 1, pixelY + 1, c);						//GAUCHE
		drawLine(pixelX - 1, y*pixelY, 2, pixelY, c);					//DROITE
	} else {
		if (y == sizeY - 1) { //Côté Bas
			drawLine(x*pixelX, (y*pixelY + pixelY)-1, pixelX + 1, 1, c);	//BAS
			drawLine(x*pixelX - 1, y*pixelY - 1, pixelX + 2, 2, c);			//HAUT
		} else {
			if (y == 0) { //Côté haut
				drawLine(x*pixelX - 1, y*pixelY, pixelX + 2, 1, c);			//HAUT
			} else { //Millieu
				drawLine(x*pixelX - 1, y*pixelY - 1, pixelX + 2, 2, c);		//HAUT
			}
				drawLine(x*pixelX, (y*pixelY + pixelY)-1, pixelX + 1, 2, c);//BAS
		}
		drawLine(x*pixelX - 1, y*pixelY, 2, pixelY + 1, c);					//GAUCHE
		drawLine((x*pixelX + pixelX)-1, y*pixelY, 2, pixelY, c);			//DROITE
	}
}

void drawPixel(unsigned char x, unsigned char y, unsigned short c) {
	videoBuffer[y * 240 + x] = c;
}

void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c) {
	unsigned char i, j;
	for (i = y; i < (y + h); i++) {
		for (j = x; j < (x + l); j++) {
			videoBuffer[i * 240 + j] = c;
		}
	}
}

//Rectangle avec les bords autour de la zone à encadrer
void drawRectangle(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned char e, unsigned short c) {
	//		Pos X		Pos Y,	Largeur,	Longueur,	Couleur
	drawLine(x - e,		y - e,	l + e,		e,			c);			//HAUT
	drawLine(x,			y + h,	l + e,		e,			c);			//BAS
	drawLine(x + l,		y - e,	e,			h + e,		c);			//DROITE
	drawLine(x - e,		y,		e,			h + e,		c);			//GAUCHE
}

unsigned char drawCase(unsigned char x, unsigned char y) {

	unsigned char gridValue = getGridValue(x+1, y+1);

	//Case non révélée
	if (gridValue < 10) {
		
		unsigned char n = checkMines(x+1, y+1);

		if (n == 0) {
			drawEmptyCase(x, y);
			countRevealedCase();
		} else if (n < 9) {
			drawNumber(x*pixelX, y*pixelY, n);
			countRevealedCase();
		} else {
			drawMine(x*pixelX, y*pixelY);
			setMinesLeft(100);//PERDU //PROBLEME
		}

		return n;

	//Révéler case avec drapeau
	} else if (gridValue == 29) {
		setGridValue(x+1, y+1, 19);
		drawMine(x*pixelX, y*pixelY);
		setMinesLeft(100);//PROBLEME
		return 9;
	} else if (gridValue == 20) {
		unsigned char n = checkMines(x+1, y+1);
		countRevealedCase();
		setWrongFlags(getWrongFlags() - 1);
		if (n == 0) {
			drawEmptyCase(x, y);
		} else  {
			drawNumber(x*pixelX, y*pixelY, n);
		}
		return n;
	}
	return gridValue;
}

void drawCaseFromSave(unsigned char x, unsigned char y) {

	//Case révélée
	if (getGridValue(x+1, y+1) > 9) {

		unsigned char n = getGridValue(x+1, y+1);
	
		if (n == 10) {
			drawEmptyCase(x, y);
		} else if (n < 19) {
			drawNumber(x*pixelX, y*pixelY, n - 10);
		} else if (n == 19) {
			drawMine(x*pixelX, y*pixelY);
		} else if (n > 19) {
			drawFlag(x, y);
		}
	}
}

unsigned short checkPixel(int x, int y) {
	return videoBuffer[y * 240 + x];
}

void drawMine(unsigned char x, unsigned char y) {
	switch (getDifficulty()) {
		case 0 :
			drawBitmap(x, y, mine_40_Bitmap, 40);
			break;
		case 1 :
			drawBitmap(x, y, mine_20_Bitmap, 20);
			break;
		case 2 :
			drawBitmap(x, y, mine_16_Bitmap, 16);
			break;
		case 3 :
			drawBitmap(x, y, mine_10_Bitmap, 10);
			break;
		case 4 :
			drawBitmap(x, y, mine_8_Bitmap, 8);
			break;
	}
}

void drawBitmap(unsigned char x, unsigned char y, const unsigned short bitmap[1600], unsigned char size) {
	unsigned char i, j;
	for (i = y; i < size + y; i++) {
		for (j = x; j < size + x; j++) {
			drawPixel(j, i, bitmap[(i - y) * size + (j - x)]);
		}
	}
}

void drawGrid() {

	unsigned char i, j;
	for (i = 0; i < sizeX; i++) {
		for (j = 0; j < getSizeY(); j++) {
			drawBitmap(i*pixelX, j*pixelY, case_Bitmap, size);
		}
	}
}

void drawUnrevealedCase(unsigned char x, unsigned char y) {
	drawBitmap(x*pixelX, y*pixelY, case_Bitmap, size);
}

//+ Point d'interrogation ?
void drawFlag(unsigned char x, unsigned char y) {

	switch (getDifficulty()) {
		case 0 :
			drawBitmap(x*pixelX, y*pixelY, flag_40_Bitmap, 40);
			break;
		case 1 :
			drawBitmap(x*pixelX, y*pixelY, flag_20_Bitmap, 20);
			break;
		case 2 :
			drawBitmap(x*pixelX, y*pixelY, flag_16_Bitmap, 16);
			break;
		case 3 :
			drawBitmap(x*pixelX, y*pixelY, flag_10_Bitmap, 10);
			break;
		case 4 :
			drawBitmap(x*pixelX, y*pixelY, flag_8_Bitmap, 8);
			break;
	}
}

void drawNumber(unsigned char x, unsigned char y, unsigned char n) {

	unsigned char i, j;

	switch (getDifficulty()) {
		case 0 :
			for(i = y; i < y + 40; i++) {
				for(j = x; j < x + 40; j++) {
					drawPixel(j, i, numbers_40_Bitmap[(i - y) * 320 + (j - x + (40*(n-1)))]);
				}
			}
			break;
		case 1 :
			for(i = y; i < y + 20; i++) {
				for(j = x; j < x + 20; j++) {
					drawPixel(j, i, numbers_20_Bitmap[(i - y) * 160 + (j - x+ (20*(n-1)))]);
				}
			}
			break;
		case 2 :
			for(i = y; i < y + 16; i++) {
				for(j = x; j < x + 16; j++) {
					drawPixel(j, i, numbers_16_Bitmap[(i - y) * 128 + (j - x+ (16*(n-1)))]);
				}
			}
			break;
		case 3 :
			for(i = y; i < y + 10; i++) {
				for(j = x; j < x + 10; j++) {
					drawPixel(j, i, numbers_10_Bitmap[(i - y) * 80 + (j - x+ (10*(n-1)))]);
				}
			}
			break;
		case 4 :
			for(i = y; i < y + 8; i++) {
				for(j = x; j < x + 8; j++) {
					drawPixel(j, i, numbers_8_Bitmap[(i - y) * 64 + (j - x+ (8*(n-1)))]);
				}
			}
			break;
	}
}

void drawEmptyCase(unsigned char x, unsigned char y) {

	unsigned char i, j;

	for(i = y*pixelY + 1; i < y*pixelY + size - 1; i++) {
		for(j = x*pixelX + 1; j < x*pixelX + size - 1; j++) {
			drawPixel(j, i, RGB(192, 192, 192));
		}
	}
	cursor(x, y, RGB(115, 115, 115));
}

void drawScreen(const unsigned short screen[38400]) {
	unsigned char i, j;
	for (i = 0; i < 160; i++) {
		for (j = 0; j < 240; j++) {
			drawPixel(j, i, screen[i * 240 + j]);
		}
	}
}
