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
#include "settings.h"

unsigned char initSave() {
	//Si pas de sauvegarde, initialiser
	if (*saveExist != 7) {

		setDifficulty(0);
		setMines(10);
		saveMenu();

		setVolume(4);
		saveSettings(4);

		endVideoMode0();
		setVideoMode3();
	
		//Fond
		drawScreenV(load_Bitmap);//Changer

		endVideoMode3();
		setVideoMode0();
	} else {
		//Charger les valeurs du menu
		setDifficulty(*menuDifficulty);
		setMines(*menuMines);

		//R�gler les param�tres
		setVolume(*volume_Save);
	}
	return *saveExist;
}

//Video mode 3
void saveGrid() {
	unsigned short n = 0;
	unsigned char bar = 0; //TOTAL 188
	unsigned char sizeX = getSizeX()+2;
	unsigned char sizeY = getSizeY()+2;

	float barSize = (float)188 / (sizeX * sizeY);
	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			unsigned char value = getGridValue(posX, posY);

			//Pointeur emplacement m�moire de sauvegarde
			unsigned char *p = (unsigned char *)MEM_SRAM + 9*n + GRID_LOCATION; //+Autres varaibles stock�es avant
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
	drawScreenV(save_Bitmap);

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
		drawScreenV(load_Bitmap);

		setDifficulty(*difficulty_Save);
		setMines(*mines_Save);
		setPos(*cursorX, *cursorY);
		setTime(*H, *M, *S);

		unsigned int seedSave = *seed_Save_4;
		//Ne pas oublier les 0
		if (*seed_Save_3 < 10) {
			seedSave = concatenate(seedSave, 0);
		}
		seedSave = concatenate(seedSave, *seed_Save_3);
		if (*seed_Save_2 < 10) {
			seedSave = concatenate(seedSave, 0);
		}
		seedSave = concatenate(seedSave, *seed_Save_2);
		if (*seed_Save_1 < 10) {
			seedSave = concatenate(seedSave, 0);
		}
		seedSave = concatenate(seedSave, *seed_Save_1);
		setSeed(seedSave);

		unsigned short fcSave = *fc_Save_2;
		if (*fc_Save_1 < 10) {
			fcSave = concatenate(fcSave, 0);
		}
		fcSave = concatenate(fcSave, *fc_Save_1);
		setFirstCase(fcSave);
		
		//Grille
		resetGrid();
		unsigned short n = 0;
		unsigned char bar = 0;
		unsigned char value;
		unsigned char sizeX = getSizeX()+2;
		unsigned char sizeY = getSizeY()+2;
		
		float barSize = (float)188 / (sizeX * sizeY);

		unsigned char posY, posX;
		for (posX = 0; posX < sizeX; posX++) {
			for (posY = 0; posY < sizeY; posY++) {

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

void saveSettings(unsigned char volume) {
	*volume_Save = volume;
}

//Demander confirmation
void deleteSave() {
	unsigned short i;
	for (i = 9; i += 9; i < 6516) {
		unsigned char *p = (unsigned char *)MEM_SRAM + i;
		*p = 0;
	}
}
