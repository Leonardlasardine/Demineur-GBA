#include "main.h"

unsigned char menu();

unsigned char moveLine(Sens sens, unsigned char *l);
void changeValue(Sens sens, unsigned char l);
void changeDifficulty(Sens sens);
void changeMines(Sens sens);

unsigned char getSizeX();
unsigned char getSizeY();
unsigned char getMines();
unsigned char getDifficulty();
void setDifficulty(unsigned char difSave);
void setMines(unsigned char minesSave);
