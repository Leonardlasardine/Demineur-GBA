#include <mygba.h>
#include "main.h"

int main(void) {
	ham_Init();

	if (TEXT_MODE) {
		ham_SetBgMode(0);
		ham_InitText(0);
	} else {
		//Video Mode 3
		REG_DISPCNT = (MODE_3 | BG2_ENABLE);
	}

	unsigned char upPressed = 0;
	unsigned char downPressed = 0;
	unsigned char leftPressed = 0;
	unsigned char rightPressed = 0;
	unsigned char aPressed = 0;

	unsigned char x = 0;
	unsigned char y = 0;
	
	//Démarage
	grid();


	cursor(x, y, RGB(y*10 + x*10, y*10, (150 - x*5)));



	unsigned char posY, posX;
	for (posX = 0; posX < 16; posX++) {
		for (posY = 0; posY < 16; posY++) {
			drawCase(posX, posY);
		}
	}



   while(1) {
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
	//ham_DrawText(*x, *y, "X");
}
