#include "menu.h"
#include "mines.h"
#include "pause.h"
#include "controls.h"

void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c);
void drawScreen(const unsigned short screen[38400]);

unsigned char initSave();
void saveGrid(unsigned char textX, unsigned char textY);
void save();
unsigned char load();
void saveMenu();


//SCORES D'UN NIVEAU
typedef struct SRAM_SCORE {
	char pseudo[20]; //Changer taille
	unsigned char s_H, s_M, s_S;;
}SRAM_SCORE;
