#include <mygba.h>
#include "main.h"
#include "videoModes.h"

unsigned short checkPixel (int x, int y);

unsigned char getMines();

unsigned char pauseGame();
unsigned char moveLinePause(Sens sens, unsigned char *l);
void aPressedAction(unsigned char *l);
