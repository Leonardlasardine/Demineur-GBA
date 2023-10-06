#include <mygba.h>

//Pointeurs emplacement mémoire de sauvegarde
//Taille 9 octets par variable

#define GRID_LOCATION 270 //Après toutes las autres variables

//PARTIE
unsigned char *gameExist = (unsigned char *)MEM_SRAM + 18;
unsigned char *difficulty_Save = (unsigned char *)MEM_SRAM + 27;
unsigned char *mines_Save = (unsigned char *)MEM_SRAM + 36;
unsigned char *minesLeft_Save = (unsigned char *)MEM_SRAM + 45;
//Curseur
unsigned char *cursorX = (unsigned char *)MEM_SRAM + 54;
unsigned char *cursorY = (unsigned char *)MEM_SRAM + 63;
//Temps
unsigned char *H = (unsigned char *)MEM_SRAM + 72;
unsigned char *M = (unsigned char *)MEM_SRAM + 81;
unsigned char *S = (unsigned char *)MEM_SRAM + 90;
//Seed pour obtenir un mot de passe d'une partie sauvegardée
unsigned int *seed_Save = (unsigned int *)MEM_SRAM + 99;


//MENU
unsigned char *menuDifficulty = (unsigned char *)MEM_SRAM + 243;
unsigned char *menuMines = (unsigned char *)MEM_SRAM + 252;
unsigned char *saveExist = (unsigned char *)MEM_SRAM + 261;
