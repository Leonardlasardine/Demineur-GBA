#include "selectionMenu.h"


unsigned char gameMode = 0;

unsigned char selectionMenu() {
	//Touches
	unsigned char upMenu = 0;
	unsigned char downMenu = 0;
	unsigned char aMenu = 0;
	unsigned char startMenu = 0;

	unsigned char chooseMode = 1;
	unsigned char line = 0;

	ham_DrawText(8, 5,  "NOUVELLE PARTIE");
	ham_DrawText(12, 10, "CHARGER");
	ham_DrawText(12, 15, "SCORES");
	
	moveLineSelection(DROITE, &line);

	while (chooseMode) {
		if(F_CTRLINPUT_UP_PRESSED) {
		   upMenu = 1;
	   } else {
		   if (upMenu) {
			   line = moveLineSelection(HAUT, &line);
			   upMenu = 0;
		   }
	   }

	   if(F_CTRLINPUT_DOWN_PRESSED) {
		   downMenu = 1;
	   } else {
		   if (downMenu) {
			   line = moveLineSelection(BAS, &line);
			   downMenu = 0;
		   }
	   }

	   if(F_CTRLINPUT_A_PRESSED) {
		   aMenu = 1;
	   } else {
		   if (aMenu) {
			   aPressedSelection(&line);
			   chooseMode = 0;
			   aMenu = 0;
		   }
	   }

	   if (F_CTRLINPUT_START_PRESSED) {
		   startMenu = 1;
	   } else {
		   if (startMenu) {
			   //Comme le bouton A
			   aMenu = 1;
			   startMenu = 0;
		   }
	   }
	}
	return gameMode;
}

unsigned char moveLineSelection(Sens sens, unsigned char *l) {
	switch (sens) {
		case HAUT :
			if (*l == 0) {
				*l = 2;
			} else {
				*l -= 1;
			}
			break;
		case BAS :
			if (*l == 2) {
				*l = 0;
			} else {
				*l += 1;
			}
			break;
		default :
			break;
	}

	ham_DrawText(6, 5, " ");
	ham_DrawText(24, 5, " ");
	ham_DrawText(10, 10, " ");
	ham_DrawText(20, 10, " ");
	ham_DrawText(10, 15, " ");
	ham_DrawText(19, 15, " ");

	switch (*l) {
		case 0 :
			ham_DrawText(6, 5, "-");
			ham_DrawText(24, 5, "-");
			break;
		case 1 :
			ham_DrawText(10, 10, "-");
			ham_DrawText(20, 10, "-");
			break;
		case 2 :
			ham_DrawText(10, 15, "-");
			ham_DrawText(19, 15, "-");
			break;
	}
	return *l;
}

void aPressedSelection(unsigned char *l) {
	switch (*l) {
		case 0 :
			gameMode = 0;
			break;
		case 1 :
			gameMode = 1;
			break;
		case 2 :
			gameMode = 2;
			break;
	}
}
