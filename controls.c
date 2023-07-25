#include "controls.h"

//Touches
unsigned char upPressed = 0;
unsigned char downPressed = 0;
unsigned char leftPressed = 0;
unsigned char rightPressed = 0;
unsigned char aPressed = 0;

unsigned char x = 0;
unsigned char y = 0;


int control() {
	
	int alive = 1;
	cursor(x, y, RGB(y*10 + x*10, y*10, (150 - x*5)));

	while(alive) {
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

	   if(F_CTRLINPUT_A_PRESSED) {
		   aPressed = 1;
	   } else {
		   if (aPressed) {
			   drawCase(x, y);
			   aPressed = 0;
		   }
	   }
	   if(F_CTRLINPUT_B_PRESSED) {
		   reveal();
	   }

	   if (F_CTRLINPUT_L_PRESSED) {
		   if (F_CTRLINPUT_R_PRESSED) {
			   alive = 0;
		   }
	   }
   }
	return 0;
}

void move(Sens sens, unsigned char *x, unsigned char *y) {
	cursor(*x, *y, RGB(0, 0, 0));
	switch (sens) {
		case HAUT :
			*y -= 1;
			break;
		case BAS :
			*y += 1;
			break;
		case GAUCHE :
			*x -= 1;
			break;
		case DROITE :
			*x += 1;
			break;
	}
	cursor(*x, *y, RGB(*y*10 + *x*10, *y*10, (150 - *x*5)));
}
