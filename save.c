#include <math.h>
#include "save.h"
#include "videoModes.h"
#include "bitmaps.h"
#include "font.h"
#include "memoryLocation.h"

unsigned char initSave() {

	//ham_InitRAM(RAM_TYPE_SRAM_256K);

	//Si pas de sauvegarde, initialiser
	if (!*saveExist) {

		setDifficulty(0);
		setMines(20);//MENU plutot
		setMinesLeft(20);
		setX(0);
		setY(0);//Ou les deux en même temps
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
void saveGrid(unsigned char textX, unsigned char textY) {
	unsigned short n = 0;
	unsigned char bar = 0; //TOTAL 188
	unsigned char sizeX = getSizeX()+1;
	unsigned char sizeY = getSizeY()+1;

	float barSize = (float)188 / ((sizeX-1) * (sizeY-1));//factoriser
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
		//ham_DrawText(1, 1, "DEJA UNE SAUVEGARDE");
		//ham_DrawText(1, 2, "ECRASER");					//Faire oui/non
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

	//Sauvegarde de la grille
	saveGrid(12, 3);

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
		setX(*cursorX);
		setY(*cursorY);//Ou les deux en même temps
		setTime(*H, *M, *S);
		
		//Grille
		resetGrid();
		unsigned short n = 0;
		unsigned char bar = 0;
		unsigned char value;
		unsigned char sizeX = getSizeX()+1;
		unsigned char sizeY = getSizeY()+1;
		
		float barSize = (float)188 / ((sizeX-1) * (sizeY-1));//factoriser

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
