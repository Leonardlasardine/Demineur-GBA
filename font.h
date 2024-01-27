#include "settings.h"

void drawChar(unsigned char x, unsigned char y, unsigned char character, unsigned short color);
void write(unsigned char *text, unsigned char length, unsigned char x, unsigned char y, signed char gap, unsigned short color);
void drawKeys();

unsigned char keyPressed(unsigned char x, unsigned char y, unsigned char *pos);
void remove(unsigned char *pos);
void emptySquare(unsigned char pos);

unsigned char numberToChar(unsigned char number);
