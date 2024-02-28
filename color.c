#include "color.h"
#include "settings.h"
#include "view.h"
#include "videoModes.h"

unsigned short colorMenu() {
	endVideoMode0();
	setVideoMode3();
	screenHalf(color_Bitmap);

	//Touches
	unsigned char leftColor = 0;
	unsigned char rightColor = 0;
	unsigned char aColor = 0;
	unsigned char startColor = 0;

	unsigned char ColorMenu = 1;
	unsigned char lineColor = 0;

	unsigned char colors [3];
	unsigned short rgb = getColor();
	colors[0] = RGB_GET_R_VALUE(rgb) / 4;
	colors[1] = RGB_GET_G_VALUE(rgb) / 4;
	colors[2] = RGB_GET_B_VALUE(rgb) / 4;

	//Affiche la valeur initiale sur les curseurs
	drawLine(124, 152 - colors[0], 32, colors[0], RGB(255, 0, 0));
	drawLine(164, 152 - colors[1], 32, colors[1], RGB(0, 255, 0));
	drawLine(204, 152 - colors[2], 32, colors[2], RGB(0, 0, 255));
	//Afficher la couleur finale
	drawLine(12, 28, 100, 100, RGB(colors[0]*4, colors[1]*4, colors[2]*4));

	moveLineColor(HAUT, &lineColor);

	while(ColorMenu) {
	   if (F_CTRLINPUT_LEFT_PRESSED) {
		   leftColor = 1;
	   } else {
		   if (leftColor) {
			   moveLineColor(GAUCHE, &lineColor);
			   leftColor = 0;
		   }
	   }

	   if (F_CTRLINPUT_RIGHT_PRESSED) {
		   rightColor = 1;
	   } else {
		   if (rightColor) {
			   moveLineColor(DROITE, &lineColor);
			   rightColor = 0;
		   }
	   }

	   //Pas touche relachée mais délai le temps que le carré de 100**100 se dessine
	   if (F_CTRLINPUT_UP_PRESSED) {
		   colors[lineColor] = changeColorValue(HAUT, colors[lineColor]);
		   updateCursors(HAUT, lineColor, colors[lineColor]);
		   //Afficher la couleur finale
		   drawLine(12, 28, 100, 100, RGB(colors[0]*4, colors[1]*4, colors[2]*4));
	   }

	   if (F_CTRLINPUT_DOWN_PRESSED) {
		   colors[lineColor] = changeColorValue(BAS, colors[lineColor]);
		   updateCursors(BAS , lineColor, colors[lineColor]);
		   //Afficher la couleur finale
		   drawLine(12, 28, 100, 100, RGB(colors[0]*4, colors[1]*4, colors[2]*4));
	   }

	   if (F_CTRLINPUT_A_PRESSED) {
		   aColor = 1;
	   } else {
		   if (aColor) {
			   ColorMenu = 0;
			   aColor = 0;
		   }
	   }

	   if (F_CTRLINPUT_START_PRESSED) {
		   startColor = 1;
	   } else {
		   if (startColor) {
			   //Comme le bouton A
			   aColor = 1;
			   startColor = 0;
		   }
	   }
	}
	endVideoMode3();
	setVideoMode0();

	return RGB(colors[0]*4, colors[1]*4, colors[2]*4);
}

//Change rouge vert ou bleu
unsigned char moveLineColor(Sens sens, unsigned char *l) {
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
	
	drawRectangle(124, 89, 32, 63, 2, RGB(255, 131, 43));
	drawRectangle(164, 89, 32, 63, 2, RGB(255, 131, 43));
	drawRectangle(204, 89, 32, 63, 2, RGB(255, 131, 43));

	switch (*l) {
		case 0 :
			drawRectangle(124, 89, 32, 63, 2, RGB(0, 0, 255));
			break;
		case 1 :
			drawRectangle(164, 89, 32, 63, 2, RGB(0, 0, 255));
			break;
		case 2 :
			drawRectangle(204, 89, 32, 63, 2, RGB(0, 0, 255));
			break;
	}
	return *l;
}

//Modifie l'intensité de rouge vert ou bleu
unsigned char changeColorValue(Sens sens, unsigned char intensity) {
	switch (sens) {
		case BAS :
			if (intensity > 0) {
				intensity--;
			}
			break;
		case HAUT :
			if (intensity < 63) {
				intensity++;
			}
			break;
		default :
			break;
	}
	return intensity;
}

//Affiche le changement de curseur
void updateCursors(Sens sens, unsigned char l, unsigned char intensity) {
	//Curseurs
	switch (l) {
		case 0 :
			if (sens == BAS) {
				//Ligne blanche
				drawLine(124, 152 - intensity - 1, 32, 1, RGB(255, 255, 255));
			} else {
				drawLine(124, 152 - intensity, 32, 1, RGB(255, 0, 0));
			}
			break;
		case 1 :
			if (sens == BAS) {
				drawLine(164, 152 - intensity - 1, 32, 1, RGB(255, 255, 255));
			} else {
				drawLine(164, 152 - intensity, 32, 1, RGB(0, 255, 0));
			}
			break;
		case 2 :
			if (sens == BAS) {
				drawLine(204, 152 - intensity - 1, 32, 1, RGB(255, 255, 255));
			} else {
				drawLine(204, 152 - intensity, 32, 1, RGB(0, 0, 255));
			}
			break;
		default :
			break;
	}
}
