#include <mygba.h>
#include "flags.h"
#include "cases.h"

unsigned short* videoBuffer = (unsigned short*) 0x6000000;

void drawPixel(unsigned char x, unsigned char y, unsigned short c);
void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c);
void drawCase(unsigned char x, unsigned char y);
unsigned short checkPixel (int x, int y);
void drawMine(unsigned char x, unsigned char y);
void drawBitmap(unsigned char x, unsigned char y, unsigned short bitmap[1600], unsigned char size);
void drawGrid();
