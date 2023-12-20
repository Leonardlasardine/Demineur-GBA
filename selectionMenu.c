#include "selectionMenu.h"
#include "videoModes.h"
#include "save.h"

unsigned char chooseMode;
unsigned char line;

unsigned char selectionMenu() {
	//Touches
	unsigned char upMenu = 0;
	unsigned char downMenu = 0;
	unsigned char aMenu = 0;
	unsigned char startMenu = 0;

	chooseMode = 1;
	line = 0;

	ham_DrawText(8, 5,  "NOUVELLE PARTIE");
	ham_DrawText(12, 10, "CHARGER");
	ham_DrawText(12, 15, "SCORES");
	ham_DrawText(19, 18, "OPTIONS");
	
	moveLineSelection(NUL, &line);

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
	return line;
}

unsigned char moveLineSelection(Sens sens, unsigned char *l) {
	switch (sens) {
		case HAUT :
			if (*l == 0) {
				*l = 3;
			} else {
				*l -= 1;
			}
			break;
		case BAS :
			if (*l == 3) {
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
	ham_DrawText(18, 18, " ");
	ham_DrawText(26, 18, " ");

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
		case 3 :
			ham_DrawText(18, 18, "-");
			ham_DrawText(26, 18, "-");
			break;
	}
	return *l;
}
