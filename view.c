#include <mygba.h>
#include "view.h"
#include "mines.h"

void cursor (unsigned char x, unsigned char y, unsigned short c) {
	drawLine(x*PIXEL_X, y*PIXEL_Y, PIXEL_X, 1, c);
	drawLine(x*PIXEL_X, y*PIXEL_Y, 1, PIXEL_Y, c);
	drawLine(x*PIXEL_X, y*PIXEL_Y + PIXEL_Y, PIXEL_X+1, 1, c);
	drawLine(x*PIXEL_X + PIXEL_X, y*PIXEL_Y, 1, PIXEL_Y, c);
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
	unsigned char n = checkMines(x, y);
	switch (n) {
		case 0 :
			drawLine(x*PIXEL_X, y*PIXEL_Y, PIXEL_X, PIXEL_Y, RGB(50,100,255));
			break;
		case 1 :
			drawLine(x*PIXEL_X, y*PIXEL_Y, PIXEL_X, PIXEL_Y, RGB(0,100,100));
			break;
		case 2 :
			drawLine(x*PIXEL_X, y*PIXEL_Y, PIXEL_X, PIXEL_Y, RGB(0,255,255));
			break;
		case 3 :
			drawLine(x*PIXEL_X, y*PIXEL_Y, PIXEL_X, PIXEL_Y, RGB(200,0,255));
			break;
		case 4 :
			drawLine(x*PIXEL_X, y*PIXEL_Y, PIXEL_X, PIXEL_Y, RGB(255,100,50));
			break;
		case 9 :
			drawLine(x*PIXEL_X, y*PIXEL_Y, PIXEL_X, PIXEL_Y, RGB(255,0,0));
			break;
	}
}
