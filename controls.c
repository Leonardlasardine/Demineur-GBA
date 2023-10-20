#include "mines.h"
#include "main.h"
#include "controls.h"
#include "pause.h"
#include "view.h"
#include "gameOver.h"
#include "timers.h"

#include "font.h"

unsigned char x;
unsigned char y;
unsigned short fistClick;

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

	switch (newGame) {
	case 0://Nouvelle partie
		x = 0;
		y = 0;
		drawGrid();
		//Jamais généré
		fistClick = 0;
		break;
	case 1 ://Depuis la sauvegarde
		drawSave();
		break;
	case 2 ://Depuis un mot de passe
		drawGrid();
		drawCase(x, y); //Afficher première case
		fistClick = y*(getSizeX()+1) + x + 1;
	}
	
	cursor(x, y, RGB(0, 0, 150));

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

	   //Révéler
	   if(F_CTRLINPUT_A_PRESSED) {
		   aPressed = 1;
	   } else {
		   if (aPressed) {
			   if (fistClick == 0) { //Générer la grille au premier click
				   grid(getSeed(), x + 1, y + 1);
				   fistClick = y*(getSizeX()+1) + x + 1;
			   }
			   if (drawCase(x, y) == 9) {
				   switch (gameOver()) {
				   case 0 ://Continuer
					   drawSave();//Ré-afficher à chaque fois ?
					   break;
				   case 1 ://Quitter
					   alive = 0;
					   break;
				   case 2://Réveler
					   reveal();
					   break;
				   }
			   }
			   move(NUL, &x, &y);
			   checkWon();
			   aPressed = 0;
		   }
	   }

	   //PAS DE DRAPEAUX AVANT DE GENERER LA GRILLE
	   if(F_CTRLINPUT_B_PRESSED) {
		   bPressed = 1;
	   } else {
		   if (bPressed) {
			   unsigned char n = getGridValue(x+1, y+1);

			   //Case pas révélée
			   if (n < 10) {
				   if (n == 9) {
					   setGridValue(x+1, y+1, 29);
					   setMinesLeft(getMinesLeft() - 1);
				   } else {
					   setGridValue(x+1, y+1, 20);
					   setWrongFlags(getWrongFlags() + 1);
				   }
				   drawFlag(x, y);
			   } else if (n > 19) { //Enlever drapeaux
				   drawUnrevealedCase(x, y);
				   setGridValue(x + 1, y + 1, n - 20);
				   if (n == 20) {
					   setWrongFlags(getWrongFlags() - 1);
				   }
				   if (n == 29) {
					   setMinesLeft(getMinesLeft() + 1);
				   }
			   }
			   checkWon();
			   drawChar(0, 0, fistClick);
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
	unsigned char pixelX = 240/sizeX;
	unsigned char pixelY = 160/sizeY;

	cursor(*x, *y, RGB(*y*pixelY + *x*pixelX, *y*pixelY, (150 - *x*pixelX)));
}

unsigned char getX() {
	return x;
}

unsigned char getY() {
	return y;
}

void setPos(unsigned char newX, unsigned char newY) {
	x = newX;
	y = newY;
}

unsigned short getFirstCase() {
	return fistClick;
}

void setFirstCase(unsigned short fc) {
	fistClick = fc;
}
