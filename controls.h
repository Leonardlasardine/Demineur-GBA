#include <mygba.h>
#include "mines.h"
#include "main.h"

void control(unsigned char newGame);
void move(Sens sens, unsigned char *x, unsigned char *y);
unsigned char getX();
unsigned char getY();
void setX(unsigned char newX);
void setY(unsigned char newY);

void cursor (unsigned char x, unsigned char y, unsigned short c);
void drawCase(unsigned char x, unsigned char y);
void drawGrid();
void drawFlag(unsigned char x, unsigned char y);
void setBitmaps();

unsigned char getSizeX();
unsigned char getSizeY();
