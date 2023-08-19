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
	
	if (n == 0) {
		drawEmptyCase(x, y);
	} else if (n < 9) {
		drawNumber(x*pixelX, y*pixelY, n);
	} else {
		drawMine(x*pixelX, y*pixelY);
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
			//if (bitmap[(i - y) * size + (j - x)] != 0x0000) {
				drawPixel(j, i, bitmap[(i - y) * size + (j - x)]);
			//}
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
			memcpy(case_Bitmap, case_40_Bitmap, ARRAY_40);
			size = 40;
			break;
		case 1 :
			memcpy(case_Bitmap, case_20_Bitmap, ARRAY_20);
			size = 20;
			break;
		case 2 :
			memcpy(case_Bitmap, case_16_Bitmap, ARRAY_16);
			size = 16;
			break;
		case 3 :
			memcpy(case_Bitmap, case_10_Bitmap, ARRAY_10);//PK
			size = 10;
			break;
		case 4 :
			memcpy(case_Bitmap, case_8_Bitmap, ARRAY_8);
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

void drawFlag(unsigned char x, unsigned char y) {
	unsigned char pixelX = 240/getSizeX();
	unsigned char pixelY = 160/getSizeY();

	x = x * pixelX;
	y = y * pixelY;

	switch (getDifficulty()) {
		case 0 :
			drawBitmap(x, y, flag_40_Bitmap, 40);
			break;
		case 1 :
			drawBitmap(x, y, flag_20_Bitmap, 20);
			break;
		case 2 :
			drawBitmap(x, y, flag_16_Bitmap, 16);
			break;
		case 3 :
			drawBitmap(x, y, flag_10_Bitmap, 10);
			break;
		case 4 :
			drawBitmap(x, y, flag_8_Bitmap, 8);
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
	
	unsigned char pixelX = 240/getSizeX();
	unsigned char pixelY = 160/getSizeY();

	unsigned char size = 0;
	unsigned char i, j;

	switch (getDifficulty()) {
		case 0 :
			size = 40;
			break;
		case 1 :
			size = 20;
			break;
		case 2 :
			size = 16;
			break;
		case 3 :
			size = 10;
			break;
		case 4 :
			size = 8;
			break;
	}
	for(i = y*pixelY; i < y*pixelY + size; i++) {
		for(j = x*pixelX; j < x*pixelX + size; j++) {
			drawPixel(j, i, RGB(192, 192, 192));
		}
	}
	cursor(x, y, RGB(115, 115, 115));
}
