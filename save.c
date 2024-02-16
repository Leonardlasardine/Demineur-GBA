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
		setMines(2);
		saveMenu();

		setVolume(4);
		setColor(RGB(255, 0, 100));
		saveSettings(4, RGB(255, 0, 100));

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

		//Régler les paramètres
		setVolume(*volume_Save);
		//Ne pas oublier les 0
		unsigned short colorSave = *color_Save_3;
		if (*color_Save_2 < 10) {
			colorSave = concatenate(colorSave, 0);
		}
		colorSave = concatenate(colorSave, *color_Save_2);
		if (*color_Save_1 < 10) {
			colorSave = concatenate(colorSave, 0);
		}
		colorSave = concatenate(colorSave, *color_Save_1);
		setColor(colorSave);
	}
	return *saveExist;
}

//Video mode 3
void saveGrid(unsigned char saveNumber) {
	unsigned short n = 0;
	unsigned char bar = 0; //TOTAL 188
	unsigned char sizeX = getSizeX()+2;//Pas obliger d'enregistrer les bordures
	unsigned char sizeY = getSizeY()+2;

	float barSize = (float)188 / (sizeX * sizeY);
	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			unsigned char value = getGridValue(posX, posY);

			//Pointeur emplacement mémoire de sauvegarde
			unsigned char *p = (unsigned char *)MEM_SRAM + 9*n + GRID_LOCATION + 6336*saveNumber; //+Autres varaibles stockées avant
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

void save(unsigned char saveNumber) {
	endVideoMode0();
	setVideoMode3();
	
	//Fond
	drawScreenV(save_Bitmap);

	if(*gameExist) {
		//Faire oui/non
	}

	//*gameExist = 7;
	*gameExist |= power(2, saveNumber);
	*(difficulty_Save + 135*saveNumber) = getDifficulty();
	*(mines_Save + 135*saveNumber) = getMines();
	*(cursorX + 135*saveNumber) = getX();
	*(cursorY + 135*saveNumber) = getY();
	*(H + 135*saveNumber) = getHours();
	*(M + 135*saveNumber) = getMinutes();
	*(S + 135*saveNumber) = getSeconds();

	unsigned int seedSave = getSeed();
	*(seed_Save_1 + 135*saveNumber) = seedSave % 100;
	*(seed_Save_2 + 135*saveNumber) = (seedSave / 100) % 100;
	*(seed_Save_3 + 135*saveNumber) = (seedSave / 10000) % 100;
	*(seed_Save_4 + 135*saveNumber) = (seedSave / 1000000) % 100;

	unsigned short fc = getFirstCase();
	*(fc_Save_1 + 135*saveNumber) = fc % 100;
	*(fc_Save_2 + 135*saveNumber) = (fc /100) % 100;

	//Sauvegarde de la grille
	saveGrid(saveNumber);

	endVideoMode3();
	setVideoMode0();
	writePauseText();
}

unsigned char load(unsigned char saveNumber) { //Ralentir ?
	//unsigned char saveFound = *gameExist;
	//Masque pour savoir la sauvegarde existe
	unsigned char saveFound = (*gameExist & power(2, saveNumber)) > 0;

	if(/*saveFound != 7*/ !saveFound) {
		ham_DrawText(3, 10, "Aucune sauvegarde trouvee");
	} else {
		endVideoMode0();
		setVideoMode3();

		//Fond
		drawScreenV(load_Bitmap);

		setDifficulty(*(difficulty_Save + 135*saveNumber));
		setMines(*(mines_Save + 135*saveNumber));
		setPos(*(cursorX + 135*saveNumber), 
			*(cursorY + 135*saveNumber));
		setTime(*(H + 135*saveNumber), 
			*(M + 135*saveNumber), 
			*(S + 135*saveNumber));

		unsigned int seedSave = *(seed_Save_4 + 135*saveNumber);
		//Ne pas oublier les 0
		if (*(seed_Save_3 + 135*saveNumber) < 10) {
			seedSave = concatenate(seedSave, 0);
		}
		seedSave = concatenate(seedSave, *seed_Save_3);
		if (*(seed_Save_2 + 135*saveNumber) < 10) {
			seedSave = concatenate(seedSave, 0);
		}
		seedSave = concatenate(seedSave, *seed_Save_2);
		if (*(seed_Save_1 + 135*saveNumber) < 10) {
			seedSave = concatenate(seedSave, 0);
		}
		seedSave = concatenate(seedSave, *seed_Save_1);
		setSeed(seedSave);

		unsigned short fcSave = *(fc_Save_2 + 135*saveNumber);
		if (*(fc_Save_1 + 135*saveNumber) < 10) {
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

				unsigned char *p = (unsigned char *)MEM_SRAM + 9*n + GRID_LOCATION + 6336*saveNumber;
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

void saveSettings(unsigned char volume, unsigned short color) {
	*volume_Save = volume;

	unsigned int colorSave = getColor();
	*color_Save_1 = colorSave % 100;
	*color_Save_2 = (colorSave / 100) % 100;
	*color_Save_3 = (colorSave / 10000) % 100;
}

//Demander confirmation
void deleteSave() {
	unsigned short i;
	for (i = 9; i += 9; i < 29691) {//calculer la fin
		unsigned char *p = (unsigned char *)MEM_SRAM + i;
		*p = 0;
	}
}

//Obtenir le score
//Lignes de 0 à 4
unsigned char *getScorePseudo(unsigned char difficulty, unsigned char line, unsigned char *pseudo) {
	unsigned char i;
	for (i = 0; i < 8; i++) {
		unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 +i*9;
		pseudo[i] = *p;
	}
	return pseudo;
}

unsigned char getScoreH(unsigned char difficulty, unsigned char line) {
	unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 + 72;
	return *p;
}

unsigned char getScoreM(unsigned char difficulty, unsigned char line) {
	unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 + 81;
	return *p;
}

unsigned char getScoreS(unsigned char difficulty, unsigned char line) {
	unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 + 90;
	return *p;
}

//Ecrire le score
void setScorePseudo(unsigned char difficulty, unsigned char line, unsigned char *pseudo) {
	unsigned char i;
	for (i = 0; i < 8; i++) {
		unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 + i*9;
		*p = pseudo[i];
	}
}

void setScoreH(unsigned char difficulty, unsigned char line, unsigned char value) {
	unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 + 72;
	*p = value;
}

void setScoreM(unsigned char difficulty, unsigned char line, unsigned char value) {
	unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 + 81;
	*p = value;
}

void setScoreS(unsigned char difficulty, unsigned char line, unsigned char value) {
	unsigned char *p = (unsigned char *)MEM_SRAM + SCORE_LOCATION + difficulty*495 + line*99 + 90;
	*p = value;
}
