#include <mygba.h>
#include "view.h"
#include "mines.h"
#include "menu.h"

void cursor (unsigned char x, unsigned char y, unsigned short c) {
	
	unsigned char pixelX = 240/getSizeX();
	unsigned char pixelY = 160/getSizeY();

	drawLine(x*pixelX, y*pixelY, pixelX, 1, c);
	drawLine(x*pixelX, y*pixelY, 1, pixelY, c);
	drawLine(x*pixelX, y*pixelY + pixelY, pixelX+1, 1, c);
	drawLine(x*pixelX + pixelX, y*pixelY, 1, pixelY, c);
}


void drawPixel(unsigned char x, unsigned char y, unsigned short c) {
	videoBuffer[y * 240 + x] = c;
}


void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c) {
	int i, j;
	for (i = y; i < (y + h); i++) {
		for (j = x; j < (x + l); j++) {
			videoBuffer[i * 240 + j] = c;
		}
	}
}

void drawCase(unsigned char x, unsigned char y) {
	
	unsigned char pixelX = 240/getSizeX();
	unsigned char pixelY = 160/getSizeY();

	unsigned char n = checkMines(x, y);
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
			drawLine(x*pixelX, y*pixelY, pixelX, pixelY, RGB(255,0,0));
			break;
	}
}
