#include <mygba.h>
#include "mines.h"
#include "main.h"

int control();
void move(Sens sens, unsigned char *x, unsigned char *y);

void cursor (unsigned char x, unsigned char y, unsigned short c);
void drawCase(unsigned char x, unsigned char y);
