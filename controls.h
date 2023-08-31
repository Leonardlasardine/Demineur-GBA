#include <mygba.h>
#include "mines.h"
#include "main.h"

void control(unsigned char newGame);
void move(Sens sens, unsigned char *x, unsigned char *y);

void cursor (unsigned char x, unsigned char y, unsigned short c);
void drawCase(unsigned char x, unsigned char y);
void drawGrid();
void drawFlag(unsigned char x, unsigned char y);
void setBitmaps();

unsigned char getSizeX();
unsigned char getSizeY();
