#include "view.h"
#include "mines.h"
#include "menu.h"

void cursor (unsigned char x, unsigned char y, unsigned short c) {
	
	unsigned char pixelX = 240/getSizeX();
	unsigned char pixelY = 160/getSizeY();

	drawLine(x*pixelX, y*pixelY, pixelX, 1, c);
	drawLine(x*pixelX, y*pixelY, 1, pixelY, c);
	drawLine(x*pixelX, (y*pixelY + pixelY)-1, pixelX, 1, c);
	drawLine((x*pixelX + pixelX)-1, y*pixelY, 1, pixelY-1, c);
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

void drawCase(unsigned char x, unsigned char y) {
	
	unsigned char pixelX = 240/getSizeX();
	unsigned char pixelY = 160/getSizeY();

	unsigned char n = checkMines(x+1, y+1);
	switch (n) {
		case 0 :
			drawLine(x*pixelX, y*pixelY, pixelX, pixelY, RGB(50,100,255));
			break;
		case 1 :
			drawLine(x*pixelX, y*pixelY, pixelX, pixelY, RGB(0,100,100));
			break;
		case 2 :
			drawLine(x*pixelX, y*pixelY, pixelX, pixelY, RGB(0,255,255));
			break;
		case 3 :
			drawLine(x*pixelX, y*pixelY, pixelX, pixelY, RGB(200,0,255));
			break;
		case 4 :
			drawLine(x*pixelX, y*pixelY, pixelX, pixelY, RGB(255,100,50));
			break;
		case 9 :
			//drawLine(x*pixelX, y*pixelY, pixelX, pixelY, RGB(255,0,0));
			drawMine(x*pixelX, y*pixelY);
			break;
	}
}

unsigned short checkPixel(int x, int y) {
	return videoBuffer[y * 240 + x];
}

void drawMine(unsigned char x, unsigned char y) {
	unsigned short flag_Bitmap[1600] = {};
	unsigned char size = 0;
	
	switch (getDifficulty()) {
		case 0 :
			memcpy(flag_Bitmap, flag_40_Bitmap, sizeof(flag_40_Bitmap));
			size = 40;
			break;
		case 1 :
			memcpy(flag_Bitmap, flag_20_Bitmap, sizeof(flag_20_Bitmap));
			size = 20;
			break;
		case 2 :
			memcpy(flag_Bitmap, flag_16_Bitmap, sizeof(flag_16_Bitmap));
			size = 16;
			break;
		case 3 :
			memcpy(flag_Bitmap, flag_10_Bitmap, sizeof(flag_10_Bitmap));//PK
			size = 10;
			break;
		case 4 :
			memcpy(flag_Bitmap, flag_8_Bitmap, sizeof(flag_8_Bitmap));
			size = 8;
			break;
	}
	drawBitmap(x, y, flag_Bitmap, size);
}

void drawBitmap(unsigned char x, unsigned char y, unsigned short bitmap[1600], unsigned char size) {
	
	unsigned char i, j;
	for (i = y; i < size + y; i++) {
		for (j = x; j < size + x; j++) {
			if (bitmap[(i - y) * size + (j - x)] != 0x0000) {
				drawPixel(j, i, bitmap[(i - y) * size + (j - x)]);
			}
		}
	}
}

void drawGrid() {
	unsigned char pixelX = 240/getSizeX();
	unsigned char pixelY = 160/getSizeY();

	unsigned short case_Bitmap[1600] = {};
	unsigned char size = 0;
	
	switch (getDifficulty()) {
		case 0 :
			memcpy(case_Bitmap, case_40_Bitmap, sizeof(case_40_Bitmap));
			size = 40;
			break;
		case 1 :
			memcpy(case_Bitmap, case_20_Bitmap, sizeof(case_20_Bitmap));
			size = 20;
			break;
		case 2 :
			memcpy(case_Bitmap, case_16_Bitmap, sizeof(case_16_Bitmap));
			size = 16;
			break;
		case 3 :
			memcpy(case_Bitmap, case_10_Bitmap, sizeof(case_10_Bitmap));//PK
			size = 10;
			break;
		case 4 :
			memcpy(case_Bitmap, case_8_Bitmap, sizeof(case_8_Bitmap));
			size = 8;
			break;
	}

	unsigned char i, j;
	for (i = 0; i < getSizeX(); i++) {
		for (j = 0; j < getSizeY(); j++) {
			drawBitmap(i*pixelX, j*pixelY, case_Bitmap, size);
		}
	}
}
