#include "settings.h"
#include "save.h"
#include "color.h"

unsigned char line;
unsigned char settings;
unsigned char currentVolume;
unsigned char volumeDecimal[7] = {0, 28, 50, 72, 96, 112, 128};
unsigned short color;

void settingsMenu() {
	//Touches
	unsigned char upSettings = 0;
	unsigned char downSettings = 0;
	unsigned char aSettings = 0;
	unsigned char startSettings = 0;
	unsigned char leftSettings = 0;
	unsigned char rightSettings = 0;
	
	line = 0;
	settings = 1;

	ham_DrawText(8, 2, "Volume ");
	ham_DrawText(20, 2, "/ 6");
	ham_DrawText(8, 3, "musique");
	ham_DrawText(8, 8, "Couleur");
	ham_DrawText(8, 13, "Supprimer la");
	ham_DrawText(8, 14, "sauvegarde");
	ham_DrawText(21, 16, "quitter");

	moveLineSettings(NUL, &line);
	changeVolume(NUL);

	while (settings) {
		if(F_CTRLINPUT_UP_PRESSED) {
		   upSettings = 1;
	   } else {
		   if (upSettings) {
			   line = moveLineSettings(HAUT, &line);
			   upSettings = 0;
		   }
	   }

	   if (F_CTRLINPUT_DOWN_PRESSED) {
		   downSettings = 1;
	   } else {
		   if (downSettings) {
			   line = moveLineSettings(BAS, &line);
			   downSettings = 0;
		   }
	   }
	   
	   if (F_CTRLINPUT_LEFT_PRESSED) {
		   leftSettings = 1;
	   } else {
		   if (leftSettings) {
			   if (line == 0) {
				   changeVolume(GAUCHE);
			   }
			   leftSettings = 0;
		   }
	   }

	   if (F_CTRLINPUT_RIGHT_PRESSED) {
		   rightSettings = 1;
	   } else {
		   if (rightSettings) {
			   if (line == 0) {
				   changeVolume(DROITE);
			   }
			   rightSettings = 0;
		   }
	   }

	   if (F_CTRLINPUT_A_PRESSED) {
		   aSettings = 1;
	   } else {
		   if (aSettings) {
			   switch (line) {
			   case 1 :
				   color = colorMenu();
				   //Reafficher le menu
				   ham_DrawText(8, 2, "Volume ");
					ham_DrawText(20, 2, "/ 6");
					ham_DrawText(8, 3, "musique");
					ham_DrawText(8, 8, "Couleur");
					ham_DrawText(8, 13, "Supprimer la");
					ham_DrawText(8, 14, "sauvegarde");
					ham_DrawText(21, 16, "quitter");
					moveLineSettings(NUL, &line);
					changeVolume(NUL);
				   break;
			   case 2 :
				   deleteSave();
				   ham_DrawText(15, 15, "Supprime !");
				   break;
			   case 3 :
				   settings = 0;
				   break;
				default :
					break;
			   }
			   aSettings = 0;
		   }
	   }

	   if (F_CTRLINPUT_START_PRESSED) {
		   startSettings = 1;
	   } else {
		   if (startSettings) {
			   //Comme le bouton A
			   aSettings = 1;
			   startSettings = 0;
		   }
	   }

	   //Quitter
	   if (F_CTRLINPUT_L_PRESSED) {
		   if (F_CTRLINPUT_R_PRESSED) {
			   settings = 0;
		   }
	   }
	}
	saveSettings(currentVolume, color);
}

unsigned char moveLineSettings(Sens sens, unsigned char *l) {
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

	ham_DrawText(6, 2, " ");
	ham_DrawText(24, 2, " ");
	ham_DrawText(6, 8, " ");
	ham_DrawText(24, 8, " ");
	ham_DrawText(6, 13, " ");
	ham_DrawText(24, 13, " ");
	ham_DrawText(20, 16, " ");
	ham_DrawText(28, 16, " ");

	switch (*l) {
		case 0 :
			ham_DrawText(6, 2, "-");
			ham_DrawText(24, 2, "-");
			break;
		case 1 :
			ham_DrawText(6, 8, "-");
			ham_DrawText(24, 8, "-");
			break;
		case 2 :
			ham_DrawText(6, 13, "-");
			ham_DrawText(24, 13, "-");
			break;
		case 3 :
			ham_DrawText(20, 16, "-");
			ham_DrawText(28, 16, "-");
			break;
	}
	return *l;
}

void changeVolume(Sens sens) {
	switch (sens) {
		case GAUCHE :
			if (currentVolume != 0) {
				currentVolume--;
			}
			break;
		case DROITE :
			if (currentVolume != 6) {
				currentVolume++;
			}
			break;
		default :
			break;
	}
	
	ham_DrawText(18, 2, " ");
	ham_DrawText(18, 2, "%u", currentVolume);
	//De 0 à 128
	krapSetMusicVol(volumeDecimal[currentVolume], 0);
}

void setVolume(unsigned char v) {
	currentVolume = v;
}

unsigned char getVolume(unsigned char  decimal) {
	if (decimal) {
		return volumeDecimal[currentVolume];
	} else {
		return currentVolume;
	}
}

unsigned short getColor() {
	return color;
}

void setColor(unsigned short c) {
	color = c;
}
