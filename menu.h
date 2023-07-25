#include <mygba.h>
#include "main.h"

int menu();

void grid(unsigned int seed);

unsigned char moveLine(Sens sens, unsigned char *l);
void changeValue(Sens sens, unsigned char *l);
void changeX(Sens sens);
void changeY(Sens sens);
void changeMines(Sens sens);

unsigned char getSizeX();
unsigned char getSizeY();
unsigned char getMines();
