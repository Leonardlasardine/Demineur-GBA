#include <mygba.h>

//Pointeurs emplacement mémoire de sauvegarde
//Taille 9 octets par variable

//100 de sureté
#define GRID_LOCATION 226 //Après toutes las autres variables

//PARTIE
unsigned char *gameExist = (unsigned char *)MEM_SRAM + 118;
unsigned char *difficulty_Save = (unsigned char *)MEM_SRAM + 127;
unsigned char *mines_Save = (unsigned char *)MEM_SRAM + 136;
unsigned char *minesLeft_Save = (unsigned char *)MEM_SRAM + 145;
//Curseur
unsigned char *cursorX = (unsigned char *)MEM_SRAM + 154;
unsigned char *cursorY = (unsigned char *)MEM_SRAM + 163;
//Temps
unsigned char *H = (unsigned char *)MEM_SRAM + 172;
unsigned char *M = (unsigned char *)MEM_SRAM + 181;
unsigned char *S = (unsigned char *)MEM_SRAM + 190;


//MENU
unsigned char *menuDifficulty = (unsigned char *)MEM_SRAM + 199;
unsigned char *menuMines = (unsigned char *)MEM_SRAM + 208;
unsigned char *saveExist = (unsigned char *)MEM_SRAM + 217;
