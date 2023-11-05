#include "bitmaps.h"

void drawPixel(unsigned char x, unsigned char y, unsigned short c);
unsigned short checkPixel (int x, int y);
void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c);
void drawRectangle(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned char e, unsigned short c);
void drawScreen(const unsigned short screen[38400]);

void drawGrid();
unsigned char drawCase(unsigned char x, unsigned char y, unsigned char reveal);
void reavealAround (unsigned char x, unsigned char y);
unsigned char countFlagsAround(unsigned char x, unsigned char y);
void drawCaseFromSave(unsigned char x, unsigned char y);

void drawMine(unsigned char x, unsigned char y);
void drawBitmap(unsigned char x, unsigned char y, const unsigned short bitmap[1600], unsigned char size);
void drawFlag(unsigned char x, unsigned char y);
void drawNumber(unsigned char x, unsigned char y, unsigned char n);
void drawEmptyCase(unsigned char x, unsigned char y);
void drawUnrevealedCase(unsigned char x, unsigned char y);

unsigned char getBitmapSize();
void setCaseBitmap();
void setBitmaps();

void cursor (unsigned char x, unsigned char y, unsigned short c);
