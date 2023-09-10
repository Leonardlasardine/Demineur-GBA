#include "controls.h"
#include "pause.h"

unsigned char x;
unsigned char y;

void control(unsigned char newGame) {
	//Touches
	unsigned char upPressed = 0;
	unsigned char downPressed = 0;
	unsigned char leftPressed = 0;
	unsigned char rightPressed = 0;
	unsigned char aPressed = 0;
	unsigned char bPressed = 0;
	unsigned char startPressed = 0;
	
	unsigned char alive = 1;

	setBitmaps();

	if(newGame) {//A remettre bien
		x = 2;
		y = 2;
		drawGrid();
	} else {
		drawSave();
	}

	cursor(x, y, RGB(y*10 + x*10, y*10, (150 - x*5)));//Faire *pixelX

	while(alive) {
		//Directions
		if(F_CTRLINPUT_UP_PRESSED) {
		   upPressed = 1;
	   } else {
		   if (upPressed) {
			   move(HAUT, &x, &y);
			   upPressed = 0;
		   }
	   }

	   if(F_CTRLINPUT_DOWN_PRESSED) {
		   downPressed = 1;
	   } else {
		   if (downPressed) {
			   move(BAS, &x, &y);
			   downPressed = 0;
		   }
	   }

	   if(F_CTRLINPUT_LEFT_PRESSED) {
		   leftPressed = 1;
	   } else {
		   if (leftPressed) {
			   move(GAUCHE, &x, &y);
			   leftPressed = 0;
		   }
	   }

	   if(F_CTRLINPUT_RIGHT_PRESSED) {
		   rightPressed = 1;
	   } else {
		   if (rightPressed) {
			   move(DROITE, &x, &y);
			   rightPressed = 0;
		   }
	   }

	   //R�v�ler
	   if(F_CTRLINPUT_A_PRESSED) {
		   aPressed = 1;
	   } else {
		   if (aPressed) {
			   drawCase(x, y);
			   aPressed = 0;
		   }
	   }
	   if(F_CTRLINPUT_B_PRESSED) {
		   bPressed = 1;
	   } else {
		   if (bPressed) {
			   //Case pas r�v�l�e
			   if (getGridValue(x+1, y+1) < 10) {
				   drawFlag(x, y);
				   //AFAIRE nomnbre max de drapeaux
				   setMinesLeft(getMinesLeft() - 1);
			   }
			   bPressed = 0;
		   }
	   }

	   //Triche
	   if (F_CTRLINPUT_L_PRESSED) {
		   if (F_CTRLINPUT_R_PRESSED) {
			   alive = 0;
		   }
		   if(F_CTRLINPUT_B_PRESSED) {
			   drawSave();
		   }
		   if(F_CTRLINPUT_A_PRESSED) {
			   reveal();
		   }
	   }

	   //Pause
	   if(F_CTRLINPUT_START_PRESSED) {
		   startPressed = 1;
	   } else {
		   if (startPressed) {
			   unsigned char quitGame = pauseGame();
			   if (quitGame) {
				   alive = 0;
			   }
			   cursor(x, y, RGB(y*10 + x*10, y*10, (150 - x*5)));
			   startPressed = 0;
		   }
	   }
   }
}

void move(Sens sens, unsigned char *x, unsigned char *y) {
	
	unsigned char sizeX = getSizeX();
	unsigned char sizeY = getSizeY();
	
	cursor(*x, *y, RGB(115, 115, 115));
	switch (sens) {
		case HAUT :
			if (*y > 0) {
				*y -= 1;
			} else {
				*y = sizeY - 1;
			}
			break;
		case BAS :
			if (*y < sizeY - 1) {
				*y += 1;
			} else {
				*y = 0;
			}
			break;
		case GAUCHE :
			if (*x > 0) {
				*x -= 1;
			} else {
				*x = sizeX - 1;
			}
			break;
		case DROITE :
			if (*x < sizeX - 1) {
				*x += 1;
			} else {
				*x = 0;
			}
			break;
		default :
			break;
	}
	cursor(*x, *y, RGB(*y*10 + *x*10, *y*10, (150 - *x*5)));
}

unsigned char getX() {
	return x;
}

unsigned char getY() {
	return y;
}

void setX(unsigned char newX) {
	x = newX;
}

void setY(unsigned char newY) {
	y = newY;
}
