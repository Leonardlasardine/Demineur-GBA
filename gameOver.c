#include "main.h"
#include "gameOver.h"
#include "bitmaps.h"
#include "view.h"
#include "timers.h"

unsigned char gameOver() {
	drawScreen(game_over_Bitmap);

	unsigned char time = getSeconds();
	unsigned char aGameOver = 0;
	unsigned char gameOverPicture = 1;

	while(gameOverPicture) {
		//attendrre 3 secondes
		if (getSeconds() > time + 2) {
			gameOverPicture = 0;
		}

		//Boutton A pour passer avant
		if(F_CTRLINPUT_A_PRESSED) {
		   aGameOver = 1;
		} else {
		   if (aGameOver) {
			   gameOverPicture = 0;
			   aGameOver = 0;
		   }
		}
	}
	return continueMenu();
}

//temps score....
unsigned char continueMenu() {
	//Continuer ou quitter ou voir la grille
	drawScreen(continue_Bitmap);

	//Touches
	unsigned char leftContinue = 0;
	unsigned char rightContinue = 0;
	unsigned char aContinue = 0;
	unsigned char startContinue = 0;

	unsigned char continueMenu = 1;
	unsigned char lineContinue = 0;

	moveLineContinue(HAUT, &lineContinue);

	while(continueMenu) {
	   if(F_CTRLINPUT_LEFT_PRESSED) {
		   leftContinue = 1;
	   } else {
		   if (leftContinue) {
			   moveLineContinue(GAUCHE, &lineContinue);
			   leftContinue = 0;
		   }
	   }

	   if(F_CTRLINPUT_RIGHT_PRESSED) {
		   rightContinue = 1;
	   } else {
		   if (rightContinue) {
			   moveLineContinue(DROITE, &lineContinue);
			   rightContinue = 0;
		   }
	   }

	   if(F_CTRLINPUT_A_PRESSED) {
		   aContinue = 1;
	   } else {
		   if (aContinue) {
			   continueMenu = 0;
			   aContinue = 0;
		   }
	   }

	   if (F_CTRLINPUT_START_PRESSED) {
		   startContinue = 1;
	   } else {
		   if (startContinue) {
			   //Comme le bouton A
			   aContinue = 1;
			   startContinue = 0;
		   }
	   }
	}
	return lineContinue;
}

unsigned char moveLineContinue(Sens sens, unsigned char *l) {
	switch (sens) {
		case GAUCHE :
			if (*l == 0) {
				*l = 2;
			} else {
				*l -= 1;
			}
			break;
		case DROITE :
			if (*l == 2) {
				*l = 0;
			} else {
				*l += 1;
			}
			break;
		default :
			break;
	}
	
	drawRectangle(5, 135, 40, 15, 2, RGB(255, 255, 255));
	drawRectangle(52, 135, 83, 15, 2, RGB(255, 255, 255));
	drawRectangle(142, 135, 90, 15, 2, RGB(255, 255, 255));

	switch (*l) {
		case 0 :
			drawRectangle(5, 135, 40, 15, 2, RGB(255, 0, 0));
			break;
		case 1 :
			drawRectangle(52, 135, 83, 15, 2, RGB(255, 0, 0));
			break;
		case 2 :
			drawRectangle(142, 135, 90, 15, 2, RGB(255, 0, 0));
			break;
	}
	return *l;
}
