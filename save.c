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

unsigned char initSave() {
	//Si pas de sauvegarde, initialiser
	if (!*saveExist) {

		setDifficulty(0);
		setMines(10);
		setPos(0, 0);
		*saveExist = 1;

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

	*gameExist = 1;
	*difficulty_Save = getDifficulty();
	*mines_Save = getMines();
	*minesLeft_Save = getMinesLeft();
	*cursorX = getX();
	*cursorY = getY();
	*H = getHours();
	*M = getMinutes();
	*S = getSeconds();
	*seed_Save = getSeed();//MARCHE PAS

	//Sauvegarde de la grille
	saveGrid();

	endVideoMode3();
	setVideoMode0();
	writePauseText();
}

unsigned char load() { //Ralentir ?

	unsigned char saveFound = *gameExist;

	if(!saveFound) {
		ham_DrawText(3, 10, "Aucune sauvegarde trouvee");
	} else {
		endVideoMode0();
		setVideoMode3();

		//Fond
		drawScreen(load_Bitmap);

		setDifficulty(*difficulty_Save);
		setMines(*mines_Save);
		setMinesLeft(*minesLeft_Save);
		setPos(*cursorX, *cursorY);
		setTime(*H, *M, *S);
		setSeed(*seed_Save);
		
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
	}
	return saveFound;
}

void saveMenu() {
	*menuDifficulty = getDifficulty();
	*menuMines = getMines();
	*saveExist = 1;
}
