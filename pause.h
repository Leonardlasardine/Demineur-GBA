#include <mygba.h>
#include "main.h"
#include "videoModes.h"

unsigned short checkPixel (int x, int y);
void drawScreen(const unsigned short screen[38400]);

unsigned char getMines();

unsigned char pauseGame();
unsigned char moveLinePause(Sens sens, unsigned char *l);
void aPressedAction(unsigned char *l);
void writePauseText();

unsigned char getHours();
unsigned char getMinutes();
unsigned char getSeconds();
void setTime(unsigned char hours, unsigned char minutes, unsigned char seconds);
