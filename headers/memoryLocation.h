#include <mygba.h>

//Pointeurs emplacement m�moire de sauvegarde
//Taille 9 octets par variable

//PARTIE
unsigned char *gameExist = (unsigned char *)MEM_SRAM + 18; //Contient si les parties de 1 � 5 existent
unsigned char *difficulty_Save = (unsigned char *)MEM_SRAM + 27;
unsigned char *mines_Save = (unsigned char *)MEM_SRAM + 36;
//Curseur
unsigned char *cursorX = (unsigned char *)MEM_SRAM + 45;
unsigned char *cursorY = (unsigned char *)MEM_SRAM + 54;
//Temps
unsigned char *H = (unsigned char *)MEM_SRAM + 63;
unsigned char *M = (unsigned char *)MEM_SRAM + 72;
unsigned char *S = (unsigned char *)MEM_SRAM + 81;
//Seed pour obtenir un mot de passe d'une partie sauvegard�e
//Coup�e en 4 partie, � concat�ner
unsigned char *seed_Save_1 = (unsigned char *)MEM_SRAM + 90;
unsigned char *seed_Save_2 = (unsigned char *)MEM_SRAM + 99;
unsigned char *seed_Save_3 = (unsigned char *)MEM_SRAM + 108;
unsigned char *seed_Save_4 = (unsigned char *)MEM_SRAM + 117;
unsigned char *fc_Save_1 = (unsigned char *)MEM_SRAM + 126;
unsigned char *fc_Save_2 = (unsigned char *)MEM_SRAM + 135;

			//TOTAL 126 par emplacement (sans la grille)
			//5 emplacements de sauvegarde
			//Donc 630

//MENU
unsigned char *menuDifficulty = (unsigned char *)MEM_SRAM + 648;
unsigned char *menuMines = (unsigned char *)MEM_SRAM + 657;
unsigned char *saveExist = (unsigned char *)MEM_SRAM + 666;

//OPTIONS
unsigned char *volume_Save = (unsigned char *)MEM_SRAM + 675;
unsigned char *color_Save_1 = (unsigned char *)MEM_SRAM + 684;
unsigned char *color_Save_2 = (unsigned char *)MEM_SRAM + 693;
unsigned char *color_Save_3 = (unsigned char *)MEM_SRAM + 702;

//SCORES
#define SCORE_LOCATION 711
			//TOTAL ?

#define GRID_LOCATION 3186 //Apr�s toutes les autres variables
			//Par grille max de 32*22 ==> 6336

//Total tient sur 31ko
