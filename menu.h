#include <mygba.h>
#include "main.h"

void menu();

void grid(unsigned int seed);

unsigned char moveLine(Sens sens, unsigned char *l);
void changeValue(Sens sens, unsigned char *l);
void changeDifficulty(Sens sens);
void changeMines(Sens sens);

unsigned char getSizeX();
unsigned char getSizeY();
unsigned char getMines();
unsigned char getDifficulty();
void setDifficulty(unsigned char difSave);
void setMines(unsigned char minesSave);
