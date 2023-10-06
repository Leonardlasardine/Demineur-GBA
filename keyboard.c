#include "main.h"
#include "keyboard.h"
#include "bitmaps.h"
#include "font.h"
#include "view.h"

unsigned char x, y, pos;

unsigned char *keyboard(unsigned char *pseudo) { //Tableau
	//Touches
	unsigned char upPressed = 0;
	unsigned char downPressed = 0;
	unsigned char leftPressed = 0;
	unsigned char rightPressed = 0;
	unsigned char aPressed = 0;
	unsigned char bPressed = 0;
	
	//unsigned char pseudo[8] = {};
	unsigned char writting = 1;
	x = 0;
	y = 0;
	pos = 0;

	drawKeyboard();

	//Ecrire le pseudo
	writePseudo(pseudo, &pos);

	while(writting) {
		if(F_CTRLINPUT_UP_PRESSED) {
		   upPressed = 1;
		} else {
		   if (upPressed) {
			   moveKey(HAUT, &x, &y);
			   upPressed = 0;
		   }
	   }

	   if(F_CTRLINPUT_DOWN_PRESSED) {
		   downPressed = 1;
	   } else {
		   if (downPressed) {
			   moveKey(BAS, &x, &y);
			   downPressed = 0;
		   }
	   }

	   if(F_CTRLINPUT_LEFT_PRESSED) {
		   leftPressed = 1;
	   } else {
		   if (leftPressed) {
			   moveKey(GAUCHE, &x, &y);
			   leftPressed = 0;
		   }
	   }

	   if(F_CTRLINPUT_RIGHT_PRESSED) {
		   rightPressed = 1;
	   } else {
		   if (rightPressed) {
			   moveKey(DROITE, &x, &y);
			   rightPressed = 0;
		   }
	   }

	   //ECRIRE
	   if(F_CTRLINPUT_A_PRESSED) {
		   aPressed = 1;
	   } else {
		   if (aPressed) {
			   unsigned char key = keyPressed(x, y, &pos);
			   if (key < 40) {
				   pseudo[pos-1] = key;
			   } else if (key == 40){
				   pseudo[pos] = 39;
			   } else {
				   writting = 0;
			   }
			   aPressed = 0;
		   }
	   }

	   //SUPPRIMER
	   if(F_CTRLINPUT_B_PRESSED) {
		   bPressed = 1;
	   } else {
		   if (bPressed) { 
			   if (pos > 0) {
				  remove(&pos);
				  pseudo[pos] = 39;
				}
			   bPressed = 0;
		   }
	   }
	   if(F_CTRLINPUT_L_PRESSED) {
		   if(F_CTRLINPUT_R_PRESSED) {
			   writting = 0;
		   }
	   }
	}

	return pseudo;
}

void drawKeyboard() {
	
	//Fond
	drawScreen(pseudo_Bitmap);
	drawKeys();
	keyCursor(0, 0, RGB(0, 0, 150));
}

//Beaucoup d'instructions si/sinon, c'est seulement pour passer
//d'une ligne à l'autre du clavier et la barre espace
void moveKey(Sens sens, unsigned char *x, unsigned char *y) {
	
	keyCursor(*x, *y, RGB(0, 0, 0));

	switch (sens) {
		case HAUT :
			if (*y > 0) {
				*y -= 1;
				if (*x == 11 && *y == 0) {
					*x = 10; 
				}
			} else {
				*y = 3;
				if (*x > 3 && *x < 8) {
					*x = 3;
				}
			}
			break;
		case BAS :
			if (*y < 3) {
				*y += 1;
				if (*y == 3) {
					if (*x > 3 && *x < 8) {
						*x = 3;
					}
					if (*x == 11) {
						*x = 10; 
					}
				}
			} else {
				*y = 0;
				if (*x == 11) {
					*x = 10; 
				}
			}
			break;
		case GAUCHE :
			if (*x > 0) {
				*x -= 1;
				if (*y == 3) {
					if (*x > 3 && *x < 8) {
						*x = 3;
					}
				}
			} else { //Passage de l'autre côté
				if ((*y == 0) | (*y == 3)) {
					*x = 10;
				} else {
					*x = 11;
				}
			}
			break;
		case DROITE :
			if (*y == 0) {
				if (*x < 10) {
					*x += 1;
				} else {
					*x = 0;
				}
			} else if (*y == 3) {
				if (*x < 3 ) {
					*x += 1;
				} else if (*x == 3) {
					*x += 5;
				} else if (*x < 10) {
					*x += 1;
				} else {
					*x = 0;
				}
			} else {
				if (*x < 11) {
					*x += 1;
				} else {
					*x = 0;
				} 
			}
			break;
		default :
			break;
	}
	keyCursor(*x, *y, RGB(*y*16 + *x*16, *y*16, (150 - *x*16)));
}

void keyCursor(unsigned char x, unsigned char y, unsigned short c) {

	x *= 16;

	if (y == 0 || y == 2) { //Décalage d'une ligne sur l'autre
		x += 25;
	} else {
		x += 29;
	}
	
	y *= 20;
	y += 66;

	//Touches spéciales
	if (y == 66 && x == 185) {
		//Supprimer
		drawRectangle(x, y, 30, 14, 2, c);
	} else if (y == 126 && x == 189) {
		//Valider
		drawRectangle(x, y, 30, 14, 2, c);
	} else if (y == 126 && x == 77) {
		//Espace
		drawRectangle(x, y, 78, 14, 2, c);
	} else {
		//Cases normales
		drawRectangle(x, y , 14, 14, 2, c);
	}
}

//Ecrire dernier pseudo si il existe
void writePseudo(unsigned char *pseudo, unsigned char *pos) {
	unsigned char exist = 0;
	unsigned char i;
	for (i = 0; i < 8; i++) {
		if (pseudo[i] != 39) {
			drawChar(28 + i*24, 14, pseudo[i]);
			exist = 1;
		}
	}
	if (exist) {
		*pos = 8;
	}
}
