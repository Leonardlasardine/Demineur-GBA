#include "bitmaps.h"

unsigned short* videoBuffer = (unsigned short*) 0x6000000;

void drawPixel(unsigned char x, unsigned char y, unsigned short c);
void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c);
void drawCase(unsigned char x, unsigned char y);
unsigned short checkPixel (int x, int y);
void drawMine(unsigned char x, unsigned char y);
void drawBitmap(unsigned char x, unsigned char y, const unsigned short bitmap[1600], unsigned char size);
void drawGrid();
void drawFlag(unsigned char x, unsigned char y);
void drawNumber(unsigned char x, unsigned char y, unsigned char n);
void drawEmptyCase(unsigned char x, unsigned char y);
void drawCaseFromSave(unsigned char x, unsigned char y);
unsigned char getBitmapSize();
void setCaseBitmap();
void setBitmaps();
void drawScreen(const unsigned short screen[38400]);
