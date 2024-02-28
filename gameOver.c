#include <math.h>
#include "main.h"
#include "gameOver.h"
#include "view.h"
#include "timers.h"

unsigned char gameOver() {
	screenDoor(game_over_Bitmap);

	/*unsigned char time = getSeconds();
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
	}*/
	stopTimer3();
	waitTime(200);
	transition();
	//wait();
	return continueMenu();
}

//temps score....
unsigned char continueMenu() {
	//Continuer ou quitter ou voir la grille
	screenHalf(continue_Bitmap);

	//Touches
	unsigned char leftContinue = 0;
	unsigned char rightContinue = 0;
	unsigned char aContinue = 0;
	unsigned char startContinue = 0;

	unsigned char continueMenu = 1;
	unsigned char lineContinue = 0;

	moveLineContinue(HAUT, &lineContinue);

	while(continueMenu) {
	   if (F_CTRLINPUT_LEFT_PRESSED) {
		   leftContinue = 1;
	   } else {
		   if (leftContinue) {
			   moveLineContinue(GAUCHE, &lineContinue);
			   leftContinue = 0;
		   }
	   }

	   if (F_CTRLINPUT_RIGHT_PRESSED) {
		   rightContinue = 1;
	   } else {
		   if (rightContinue) {
			   moveLineContinue(DROITE, &lineContinue);
			   rightContinue = 0;
		   }
	   }

	   if (F_CTRLINPUT_A_PRESSED) {
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

/*
 * Longueur max = 50
 * Largeur max = 10
 * Décalage max = 8
*/
void transition() {//AFAIRE interrupt pour quitter l'animation
	unsigned short repetition = 350 + rand() % 300;
	unsigned short i;
	unsigned short rectangle[500];
	unsigned char x, y;
	signed char l, h, d;

	for (i = 0; i < repetition; i++) {
		//Position
		x = rand() % 240;
		y = rand() % 160;
		//Longueur
		l = 20 + rand() % 3;
		if (x + l > 240) {
			l = -l;
		}
		//Hauteur
		h = 2 + rand() % 8;
		if (y + h > 160) {
			h = -h;
		}
		//Direction : Négatif = vers la gauche
		d = 1 + rand() % 7;
		if (x + l + d > 240) {
			d = -d;
		}
		if (x + l + d > 40) {
			if (rand() % 2) {
				d = -d;
			}
		}

		//Rectangle de Pixel
		unsigned char j, k;
		unsigned char n = 0;
		for (j = y; j < y + h; j++) {
			for (k = x; k < x + l; k++) {
				rectangle[n] = checkPixel(k, j);
				n++;
			}
		}

		//Le décaler
		unsigned char f, g;
		n = 0;
		for (f = y; f < y + h; f++) {
			for (g = x + d; g < x + l + d; g++) {
				drawPixel(g, f, rectangle[n]);
				n++;
			}
		}

		//Attendre
		if (i < 15) {
			waitTime(function(i)*0.1);
		}
	}
}

unsigned short function(unsigned char x) {
	//return floor(exp(-x + 9));
	return -2*x*x+400;//Changer de courbe
}
