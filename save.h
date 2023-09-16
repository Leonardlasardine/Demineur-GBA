#include "menu.h"
#include "mines.h"
#include "pause.h"
#include "controls.h"

void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c);
void drawScreen(const unsigned short screen[38400]);

char *numbersStr[600];//Se réduit

unsigned char initSave();
void saveGrid(unsigned char textX, unsigned char textY);
void save();
unsigned char load();
void saveMenu();


//PARTIE
#define IDENTIFIER_STRING_GAME	"Partie"
typedef struct SRAM_GAME {
	unsigned char gameExist;
	unsigned char difficulty;
	unsigned char mines;
	unsigned char minesLeft;
	//Curseur
	unsigned char x;
	unsigned char y;
	//Temps
	unsigned char s_H, s_M, s_S;
}SRAM_GAME;



//MENU
#define IDENTIFIER_STRING_MENU	"Menu"
typedef struct SRAM_MENU {
	unsigned char difficulty;
	unsigned char mines;
}SRAM_MENU;



//SCORES D'UN NIVEAU
typedef struct SRAM_SCORE {
	char pseudo[20]; //Changer taille
	unsigned char s_H, s_M, s_S;;
}SRAM_SCORE;
