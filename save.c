#include "save.h"
#include "videoModes.h"
#include "bitmaps.h"
#include <math.h>

unsigned char initSave() {
	SRAM_GAME GameBlock;
	SRAM_MENU MenuBlock;
	unsigned char exist = ham_InitRAM(RAM_TYPE_SRAM_256K);

	//Si pas de sauvegarde, initialiser
	if (!exist) {
		GameBlock.gameExist = 0;
		GameBlock.difficulty = 2;
		GameBlock.mines = 20;
		GameBlock.minesLeft = 20;
		GameBlock.x = 0;
		GameBlock.y = 0;
		GameBlock.s_H = 0;
		GameBlock.s_M = 0;
		GameBlock.s_S = 0;

		//Save custom structure into SRAM
		ham_SaveRawToRAM(IDENTIFIER_STRING_GAME,	//Emplacement
						(void*)&GameBlock,			//Données
						sizeof(SRAM_GAME));			//Taille
		
		MenuBlock.difficulty = 0;
		MenuBlock.mines = 20;

		ham_SaveRawToRAM(IDENTIFIER_STRING_MENU,
						(void*)&MenuBlock,
						sizeof(SRAM_MENU));

		//Sauvegarde vide 
		ham_DrawText(1, 1, "PREMIER LANCEMENT");
		ham_DrawText(4, 10, "INITIALISATION   /16");

		resetGrid();
		setDifficulty(2);
		
		endVideoMode0();
		setVideoMode3();
	
		//Fond
		drawScreen(load_Bitmap);//Changer

		saveGrid(19, 10);
		
		endVideoMode3();
		setVideoMode0();

		setDifficulty(0);
		setMines(20);
	} else {//Charger les valeurs du menu
		//ham_LoadRawFromRAM(IDENTIFIER_STRING_MENU, (void*)&MenuBlock);
		//setDifficulty(MenuBlock.difficulty);
		//setMines(MenuBlock.mines);
	}																			//CRASH
	return exist;
}

//Video mode 3
void saveGrid(unsigned char textX, unsigned char textY) { //Moins que 188 cases
	unsigned char n = 0;//Mettre short mais bloque quand même à 250
	unsigned char bar = 0; //TOTAL 188
	unsigned char sizeX = getSizeX()+1;
	unsigned char sizeY = getSizeY()+1;

	float barSize = (float)188 / (sizeX * sizeY);
	
	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			unsigned char value = getGridValue(posX, posY);
			ham_SaveRawToRAM(numbersStr[n], (void*)&value, sizeof(value));
			
			//Barre de chargement
			do {
				drawLine(26 + bar, 120, 1, 20, RGB(130, 226, 65));
				bar++;
			}
			while (bar < floor(barSize*(n+1)));

			n++;
		}
		//ham_DrawText(textX, textY, "%u", posX+1);
	}
}

void save() {
	endVideoMode0();
	setVideoMode3();
	
	//Fond
	drawScreen(save_Bitmap);

	SRAM_GAME GameBlock;
	ham_LoadRawFromRAM(IDENTIFIER_STRING_GAME, (void*)&GameBlock);

	if(GameBlock.gameExist) {
		//ham_DrawText(1, 1, "DEJA UNE SAUVEGARDE");
		//ham_DrawText(1, 2, "ECRASER");					//Faire oui/non
	}

	GameBlock.gameExist = 1;
	GameBlock.difficulty = getDifficulty();
	GameBlock.mines = getMines();
	GameBlock.minesLeft = getMinesLeft();
	GameBlock.x = getX();
	GameBlock.y = getY();
	GameBlock.s_H = getHours();
	GameBlock.s_M = getMinutes();
	GameBlock.s_S = getSeconds();
	
	ham_SaveRawToRAM(IDENTIFIER_STRING_GAME,
					(void*)&GameBlock,
					sizeof(SRAM_GAME));

	/*ham_DrawText(1, 5, "Difficultee %u", GameBlock.difficulty);
	ham_DrawText(1, 6, "Mines %u", GameBlock.mines);
	ham_DrawText(1, 7, "Mines restatntes %u", GameBlock.minesLeft);*/
	
	unsigned char sizeX = getSizeX()+1;
	//ham_DrawText(1, 3, "SAUVEGARDE   /%u", sizeX);

	//Sauvegarde de la grille
	saveGrid(12, 3);

	endVideoMode3();
	setVideoMode0();
	writePauseText();
}

unsigned char load() {
	SRAM_GAME GameBlock;

	ham_LoadRawFromRAM(IDENTIFIER_STRING_GAME, (void*)&GameBlock);
	
	unsigned char saveFound = GameBlock.gameExist;

	if(!saveFound) {//A changer
		ham_DrawText(3, 10, "Aucune sauvegarde trouvee");
	} else {
		endVideoMode0();
		setVideoMode3();
	
		//Fond
		drawScreen(load_Bitmap);

		/*ham_DrawText(1, 1, "SRAM inited ok");
		ham_DrawText(1, 5, "Difficultee %u", GameBlock.difficulty);
		ham_DrawText(1, 6, "Mines %u", GameBlock.mines);
		ham_DrawText(1, 7, "Mines restatntes %u", GameBlock.minesLeft);*/
		
		setDifficulty(GameBlock.difficulty);
		setMines(GameBlock.mines);
		setMinesLeft(GameBlock.minesLeft);
		setX(GameBlock.x);
		setY(GameBlock.y);//Ou les deux en même temps
		setTime(GameBlock.s_H, GameBlock.s_M, GameBlock.s_S);
		
		resetGrid();
		unsigned char n = 0;
		unsigned char bar = 0;
		unsigned char value;//Pas bseoin, de sauvegarder premiere ligne et colone
		unsigned char sizeX = getSizeX()+1;
		unsigned char sizeY = getSizeY()+1;

		
		float barSize = (float)188 / (sizeX * sizeY);
		//ham_DrawText(1, 2, "CHARGEMENT   /%u", sizeX);

		unsigned char posY, posX;
		for (posX = 0; posX < sizeX; posX++) {
			for (posY = 0; posY < sizeY; posY++) {
				ham_LoadRawFromRAM(numbersStr[n], (void*)&value);

				setGridValue(posX, posY, value);
				//Barre de chargement
				do {
					drawLine(26 + bar, 120, 1, 20, RGB(130, 226, 65));
					bar++;
				}
				while (bar < floor(barSize*(n+1)));

				//ham_DrawText(posX*2+2, posY*2+8, "%u", value);

				n++;
			}
			//ham_DrawText(12, 2, "%u", posX+1);
		}
		//ham_DrawText(1, 1, "SAUVEGARDER CHARGEE");
	}
	return saveFound;
}

void saveMenu() {
	SRAM_MENU MenuBlock;

	MenuBlock.difficulty = getDifficulty();
	MenuBlock.mines = getMines();

	ham_SaveRawToRAM(IDENTIFIER_STRING_MENU,
					(void*)&MenuBlock,
					sizeof(SRAM_MENU));
}
