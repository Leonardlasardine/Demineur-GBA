#include <math.h>
#include "save.h"
#include "videoModes.h"
#include "bitmaps.h"
#include "font.h"
#include "memoryLocation.h"
#include "view.h"
#include "menu.h"
#include "mines.h"
#include "pause.h"
#include "controls.h"
#include "timers.h"
#include "password.h"

unsigned char initSave() {
	//Si pas de sauvegarde, initialiser
	if (*saveExist != 7) {

		setDifficulty(0);
		setMines(10);
		saveMenu();

		endVideoMode0();
		setVideoMode3();
	
		//Fond
		drawScreen(load_Bitmap);//Changer

		endVideoMode3();
		setVideoMode0();
	} else {//Charger les valeurs du menu

		setDifficulty(*menuDifficulty);
		setMines(*menuMines);
	}
	return *saveExist;
}

//Video mode 3
void saveGrid() {
	unsigned short n = 0;
	unsigned char bar = 0; //TOTAL 188
	unsigned char sizeX = getSizeX()+1;
	unsigned char sizeY = getSizeY()+1;

	float barSize = (float)188 / ((sizeX-1) * (sizeY-1));
	unsigned char posY, posX;
	for (posX = 1; posX < sizeX; posX++) {
		for (posY = 1; posY < sizeY; posY++) {
			unsigned char value = getGridValue(posX, posY);

			//Pointeur emplacement mémoire de sauvegarde
			unsigned char *p = (unsigned char *)MEM_SRAM + 9*n + GRID_LOCATION; //+Autres varaibles stockées avant
			*p = value;
			
			//Barre de chargement
			if (bar < floor(barSize*(n+1))) {
				do {
				drawLine(26 + bar, 120, 1, 20, RGB(130, 226, 65));
				bar++;
				}
				while (bar < floor(barSize*(n+1)));
			}
			n++;
		}
	}
}

void save() {
	endVideoMode0();
	setVideoMode3();
	
	//Fond
	drawScreen(save_Bitmap);

	if(*gameExist) {
		//Faire oui/non
	}

	*gameExist = 7;
	*difficulty_Save = getDifficulty();
	*mines_Save = getMines();
	*cursorX = getX();
	*cursorY = getY();
	*H = getHours();
	*M = getMinutes();
	*S = getSeconds();

	unsigned int seedSave = getSeed();
	*seed_Save_1 = seedSave % 100;
	*seed_Save_2 = (seedSave / 100) % 100;
	*seed_Save_3 = (seedSave / 10000) % 100;
	*seed_Save_4 = (seedSave / 1000000) % 100;

	unsigned short fc = getFirstCase();
	*fc_Save_1 = fc % 100;
	*fc_Save_2 = (fc /100) % 100;

	//Sauvegarde de la grille
	saveGrid();

	endVideoMode3();
	setVideoMode0();
	writePauseText();
}

unsigned char load() { //Ralentir ?

	unsigned char saveFound = *gameExist;

	if(saveFound != 7) {
		ham_DrawText(3, 10, "Aucune sauvegarde trouvee");
	} else {
		endVideoMode0();
		setVideoMode3();

		//Fond
		drawScreen(load_Bitmap);

		setDifficulty(*difficulty_Save);
		setMines(*mines_Save);
		setPos(*cursorX, *cursorY);
		setTime(*H, *M, *S);

		unsigned int seedSave = concatenate(*seed_Save_4, *seed_Save_3);
		seedSave = concatenate(seedSave, *seed_Save_2);
		seedSave = concatenate(seedSave, *seed_Save_1);
		setSeed(seedSave);
		setFirstCase(concatenate(*fc_Save_2, *fc_Save_1));
		
		//Grille
		resetGrid();
		unsigned short n = 0;
		unsigned char bar = 0;
		unsigned char value;
		unsigned char sizeX = getSizeX()+1;
		unsigned char sizeY = getSizeY()+1;
		
		float barSize = (float)188 / ((sizeX-1) * (sizeY-1));

		unsigned char posY, posX;
		for (posX = 1; posX < sizeX; posX++) {
			for (posY = 1; posY < sizeY; posY++) {

				unsigned char *p = (unsigned char *)MEM_SRAM + 9*n + GRID_LOCATION;
				value = *p;

				setGridValue(posX, posY, value);

				//Barre de chargement
				if (bar < floor(barSize*(n+1))) {
					do {
					drawLine(26 + bar, 120, 1, 20, RGB(130, 226, 65));
					bar++;
					}
					while (bar < floor(barSize*(n+1)));
				}
				n++;
			}
		}
		setMinesLeft(countCases(9));
		setUnrevealedCase(countUnrevealed());
		setWrongFlags(countCases(20));
	}
	return saveFound;
}

void saveMenu() {
	*menuDifficulty = getDifficulty();
	*menuMines = getMines();
	*saveExist = 7; //Au pif mais une valeur
}
