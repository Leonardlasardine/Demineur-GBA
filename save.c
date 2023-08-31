#include "save.h"
#include "videoModes.h"

void save() {
	endVideoMode0();
	setVideoMode0();

	TSRAMDataBlock SRAMBlock;
	unsigned char exist = ham_InitRAM(RAM_TYPE_SRAM_256K);

	if(exist) {
		ham_DrawText(1, 1, "DEJA UNE SAUVEGARDE");
		ham_DrawText(1, 2, "ECRASER");//Faire oui/non
	}

	// Init structure
	SRAMBlock.difficulty = getDifficulty();
	SRAMBlock.mines = getMines();
	SRAMBlock.minesLeft = getMinesLeft();
	
	// Save custom structure into SRAM
	ham_SaveRawToRAM(IDENTIFIER_STRING,       // Specify an identifier string for the integer 
											  // to be retrieved.
					(void*)&SRAMBlock,       // pointer to the structure you want to load 
											  // the retrieved data into
					sizeof(TSRAMDataBlock)); // Length in bytes of the structure to store

	ham_DrawText(1, 5, "Difficultee %u", SRAMBlock.difficulty);
	ham_DrawText(1, 6, "Mines %u", SRAMBlock.mines);
	ham_DrawText(1, 7, "Mines restatntes %u", SRAMBlock.minesLeft);
	
	//Sauvegarde de la grille
	unsigned char n = 0;
	unsigned char sizeX = getSizeX()+1;
	unsigned char sizeY = getSizeY()+1;
	
	ham_DrawText(1, 2, "SAUVEGARDE   /%u", sizeX);

	unsigned char posY, posX;
	for (posX = 0; posX < sizeX; posX++) {
		for (posY = 0; posY < sizeY; posY++) {
			unsigned char value = getGridValue(posX, posY);
			ham_SaveIntToRAM(numbersStr[n], value);
			n++;
		}
		ham_DrawText(12, 2, "%u", posX+1);
	}

	ham_DrawText(1, 1, "Created new DATA block");
	endVideoMode0();
	setVideoMode0();
	writePauseText();
}

unsigned char load() {//Marche que la deuxieme fois
	TSRAMDataBlock SRAMBlock;
	unsigned char saveFound = ham_InitRAM(RAM_TYPE_SRAM_256K);

	if(!saveFound) {
		ham_DrawText(3, 10, "Aucune sauvegarde trouvee");
	} else {
		endVideoMode0();
		setVideoMode0();

		ham_LoadRawFromRAM(IDENTIFIER_STRING,	// Specify an identifier string for the integer 
												// to be retrieved.
						 (void*)&SRAMBlock);	// pointer to the structure you want to load 
												// the retrieved data into

		ham_DrawText(1, 1, "SRAM inited ok");
		ham_DrawText(1, 5, "Difficultee %u", SRAMBlock.difficulty);
		ham_DrawText(1, 6, "Mines %u", SRAMBlock.mines);
		ham_DrawText(1, 7, "Mines restatntes %u", SRAMBlock.minesLeft);
		
		setDifficulty(SRAMBlock.difficulty);
		setMines(SRAMBlock.mines);
		setMinesLeft(SRAMBlock.minesLeft);
		
		resetGrid();
		unsigned char n = 0;
		int value;//Pas bseoin, de sauvegarder premiere ligne et colone
		unsigned char sizeX = getSizeX()+1;
		unsigned char sizeY = getSizeY()+1;

		ham_DrawText(1, 2, "CHARGEMENT   /%u", sizeX);

		unsigned char posY, posX;
		for (posX = 0; posX < sizeX; posX++) {
			for (posY = 0; posY < sizeY; posY++) {
				ham_LoadIntFromRAM(numbersStr[n], &value);
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
