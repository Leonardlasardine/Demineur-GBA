#include "save.h"
#include "videoModes.h"

unsigned char initSave() {
	TSRAMDataBlock SRAMBlock;
	unsigned char exist = ham_InitRAM(RAM_TYPE_SRAM_256K);

	//Si pas de sauvegarde, initialiser
	if (!exist) {
		SRAMBlock.gameExist = 0;
		SRAMBlock.difficulty = 2;
		SRAMBlock.mines = 20;
		SRAMBlock.minesLeft = 20;

		//Save custom structure into SRAM
		ham_SaveRawToRAM(IDENTIFIER_STRING,			//Emplacement
						(void*)&SRAMBlock,			//Données
						sizeof(TSRAMDataBlock));	//Taille

		//Sauvegarde vide 
		ham_DrawText(1, 1, "PREMIER LANCEMENT");
		ham_DrawText(4, 10, "INITIALISATION   /16");

		resetGrid();//?
		setDifficulty(2);

		saveGrid(19, 10);

		setDifficulty(0);
		setMines(20);
	} else {//Aussi charger les valeurs du menu sans sauvegarde
		ham_LoadRawFromRAM(IDENTIFIER_STRING, (void*)&SRAMBlock);
		setDifficulty(SRAMBlock.difficulty);
		setMines(SRAMBlock.mines);
	}
	return exist;
}

void saveGrid(unsigned char textX, unsigned char textY) {
	unsigned char n = 0;
	unsigned char sizeX = getSizeX()+1;
	unsigned char sizeY = getSizeY()+1;
	
	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			unsigned char value = getGridValue(posX, posY);
			ham_SaveRawToRAM(numbersStr[n], (void*)&value, sizeof(value));
			n++;
		}
		ham_DrawText(textX, textY, "%u", posX+1);
	}
}

void save() {
	endVideoMode0();
	setVideoMode0();

	TSRAMDataBlock SRAMBlock;
	ham_LoadRawFromRAM(IDENTIFIER_STRING, (void*)&SRAMBlock);

	if(SRAMBlock.gameExist) {
		ham_DrawText(1, 1, "DEJA UNE SAUVEGARDE");
		ham_DrawText(1, 2, "ECRASER");//Faire oui/non
	}

	SRAMBlock.gameExist = 1;
	SRAMBlock.difficulty = getDifficulty();
	SRAMBlock.mines = getMines();
	SRAMBlock.minesLeft = getMinesLeft();
	
	
	ham_SaveRawToRAM(IDENTIFIER_STRING,
					(void*)&SRAMBlock,
					sizeof(TSRAMDataBlock));

	ham_DrawText(1, 5, "Difficultee %u", SRAMBlock.difficulty);
	ham_DrawText(1, 6, "Mines %u", SRAMBlock.mines);
	ham_DrawText(1, 7, "Mines restatntes %u", SRAMBlock.minesLeft);
	
	unsigned char sizeX = getSizeX()+1;
	ham_DrawText(1, 3, "SAUVEGARDE   /%u", sizeX);

	//Sauvegarde de la grille
	saveGrid(12, 3);

	ham_DrawText(1, 1, "Created new DATA block");
	endVideoMode0();
	setVideoMode0();
	writePauseText();
}

unsigned char load() {
	TSRAMDataBlock SRAMBlock;

	ham_LoadRawFromRAM(IDENTIFIER_STRING, (void*)&SRAMBlock);
	
	unsigned char saveFound = SRAMBlock.gameExist;

	if(!saveFound) {//A changer
		ham_DrawText(3, 10, "Aucune sauvegarde trouvee");
	} else {
		endVideoMode0();
		setVideoMode0();

		ham_DrawText(1, 1, "SRAM inited ok");
		ham_DrawText(1, 5, "Difficultee %u", SRAMBlock.difficulty);
		ham_DrawText(1, 6, "Mines %u", SRAMBlock.mines);
		ham_DrawText(1, 7, "Mines restatntes %u", SRAMBlock.minesLeft);
		
		setDifficulty(SRAMBlock.difficulty);
		setMines(SRAMBlock.mines);
		setMinesLeft(SRAMBlock.minesLeft);
		
		resetGrid();
		unsigned char n = 0;
		unsigned char value;//Pas bseoin, de sauvegarder premiere ligne et colone
		unsigned char sizeX = getSizeX()+1;
		unsigned char sizeY = getSizeY()+1;

		ham_DrawText(1, 2, "CHARGEMENT   /%u", sizeX);

		unsigned char posY, posX;
		for (posX = 0; posX < sizeX; posX++) {
			for (posY = 0; posY < sizeY; posY++) {
				ham_LoadRawFromRAM(numbersStr[n], (void*)&value);

				setGridValue(posX, posY, value);
				
				ham_DrawText(posX*2+2, posY*2+8, "%u", value);

				n++;
			}
			ham_DrawText(12, 2, "%u", posX+1);
		}
		ham_DrawText(1, 1, "SAUVEGARDER CHARGEE");
	}
	return saveFound;
}
