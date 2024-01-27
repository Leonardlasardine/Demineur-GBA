#include <mygba.h>

//Pointeurs emplacement mémoire de sauvegarde
//Taille 9 octets par variable

#define GRID_LOCATION 2682 //Après toutes les autres variables

//PARTIE
unsigned char *gameExist = (unsigned char *)MEM_SRAM + 18;
unsigned char *difficulty_Save = (unsigned char *)MEM_SRAM + 27;
unsigned char *mines_Save = (unsigned char *)MEM_SRAM + 36;
//Curseur
unsigned char *cursorX = (unsigned char *)MEM_SRAM + 45;
unsigned char *cursorY = (unsigned char *)MEM_SRAM + 54;
//Temps
unsigned char *H = (unsigned char *)MEM_SRAM + 63;
unsigned char *M = (unsigned char *)MEM_SRAM + 72;
unsigned char *S = (unsigned char *)MEM_SRAM + 81;
//Seed pour obtenir un mot de passe d'une partie sauvegardée
//Coupée en 4 partie, à concaténer
unsigned char *seed_Save_1 = (unsigned char *)MEM_SRAM + 90;
unsigned char *seed_Save_2 = (unsigned char *)MEM_SRAM + 99;
unsigned char *seed_Save_3 = (unsigned char *)MEM_SRAM + 108;
unsigned char *seed_Save_4 = (unsigned char *)MEM_SRAM + 117;
unsigned char *fc_Save_1 = (unsigned char *)MEM_SRAM + 126;
unsigned char *fc_Save_2 = (unsigned char *)MEM_SRAM + 135;

//MENU
unsigned char *menuDifficulty = (unsigned char *)MEM_SRAM + 144;
unsigned char *menuMines = (unsigned char *)MEM_SRAM + 153;
unsigned char *saveExist = (unsigned char *)MEM_SRAM + 162;

//OPTIONS
unsigned char *volume_Save = (unsigned char *)MEM_SRAM + 171;
unsigned char *color_Save_1 = (unsigned char *)MEM_SRAM + 180;
unsigned char *color_Save_2 = (unsigned char *)MEM_SRAM + 189;
unsigned char *color_Save_3 = (unsigned char *)MEM_SRAM + 198;

//SCORES
#define SCORE_LOCATION 207
