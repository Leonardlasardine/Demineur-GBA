#include "main.h"
#include "load.h"
#include "save.h"
#include "password.h"
#include "timers.h"
#include "mines.h"
#include "videoModes.h"
#include "menu.h"
#include "view.h"
#include "controls.h"
#include "music.h"
#include "keyboard.h"

void loadMenu() {
	//Touches
	unsigned char upLoad = 0;
	unsigned char downLoad = 0;
	unsigned char leftLoad = 0;
	unsigned char rightLoad = 0;
	unsigned char aLoad = 0;
	unsigned char startLoad = 0;
	unsigned char slot = 0;

	unsigned char wait = 1;
	unsigned char lineLoad = 0;

	ham_DrawText(8, 3, "CHARGER PARTIE");
	ham_DrawText(3, 7, "MEMOIRE 1");
	ham_DrawText(3, 11, "MOT DE PASSE");

	moveLineLoad(NUL, &lineLoad);
	
	while (wait) {
		if (F_CTRLINPUT_UP_PRESSED) {
		   upLoad = 1;
	   } else {
		   if (upLoad) {
			   lineLoad = moveLineLoad(HAUT, &lineLoad);
			   upLoad = 0;
		   }
	   }

	   if (F_CTRLINPUT_DOWN_PRESSED) {
		   downLoad = 1;
	   } else {
		   if (downLoad) {
			   lineLoad = moveLineLoad(BAS, &lineLoad);
			   downLoad = 0;
		   }
	   }

	   if (F_CTRLINPUT_LEFT_PRESSED) {
		   leftLoad = 1;
	   } else {
		   if (leftLoad) {
			   if (slot > 0) {
				   slot--;
				   ham_DrawText(11, 7, " ");
				   ham_DrawText(11, 7, "%u", slot + 1);
			   }
			   leftLoad = 0;
		   }
	   }

	   if (F_CTRLINPUT_RIGHT_PRESSED) {
		   rightLoad = 1;
	   } else {
		   if (rightLoad) {
			   if (slot < 4) {
				   slot++;
				   ham_DrawText(11, 7, " ");
				   ham_DrawText(11, 7, "%u", slot + 1);
			   }
			   rightLoad = 0;
		   }
	   }

	   if (F_CTRLINPUT_A_PRESSED) {
		   aLoad = 1;
	   } else {
		   if (aLoad) {
			   if (lineLoad) {
				   if (!loadFromPassword()) {
						ham_DrawText(8, 3, "CHARGER PARTIE");
						ham_DrawText(3, 7, "MEMOIRE");
						ham_DrawText(3, 11, "MOT DE PASSE");
						ham_DrawText(6, 15, "Mot de passe incorecte");
				   } else {
					   wait = 0;
				   }
			   } else {
				   if (loadFromSave(slot)/* == 7*/) {
					   wait = 0;
				   }
			   }
			   aLoad = 0;
		   }
	   }

	   if (F_CTRLINPUT_START_PRESSED) {
		   startLoad = 1;
	   } else {
		   if (startLoad) {
			   //Comme le bouton A
			   aLoad = 1;
			   startLoad = 0;
		   }
	   }

	   if (F_CTRLINPUT_L_PRESSED) {
		   //Quitter Menu
		   if (F_CTRLINPUT_R_PRESSED) {
			   wait = 0;
		   }
	   }
	}
}

unsigned char loadFromSave(unsigned char saveNumber) {
	unsigned char saveExist = load(saveNumber);

	if(saveExist/* == 7*/) {
		krapPlay(&mod_adagio, KRAP_MODE_LOOP, 0);
		control(1);
		endVideoMode3();
	}
	return saveExist;
}

unsigned char loadFromPassword() {
	unsigned char succes = 0;

	endVideoMode0();
	setVideoMode3();
	
	unsigned char password[8] = {39, 39, 39, 39, 39, 39, 39, 39};
	keyboard(password);
	
	endVideoMode3();
	setVideoMode0();
	
	//Vérifier qu'il n'y ait pas d'espace
	unsigned char i;
	for(i = 0; i < 8; i++) {
		if (password[i] == 39) {
			return succes;
		}
	}

	unsigned long long n = convertToBase10(password);
	unsigned int seed = getPasswordSeed(n);
	unsigned char d = getPasswordDifficulty(n);
	unsigned char m = getPasswordMines(n);
	unsigned short fc = getPasswordFirstCase(n);

	//Verifier que le mot de passe est possible
	if (d > 4 || m > 99 || seed > 5352007) {
		return succes;
	}

	unsigned short maxFc = 0;
	switch (d) {
	case 0 :
		maxFc = 26;
		break;
	case 1 :
		maxFc = 102;
		break;
	case 2 :
		maxFc = 158;
		break;
	case 3 :
		maxFc = 398;
		break;
	case 4 :
		maxFc = 618;
		break;
	}
	if (fc > maxFc) {
		return succes;
	} else {
		succes = 1;
	}

	setSeed(seed);
	setDifficulty(d);
	setMines(m);

	/*ham_DrawText(1, 1, "%u", seed);
	ham_DrawText(1, 4, "%u", d);
	ham_DrawText(1, 7, "%u", m);*/
	
	//Retrouver première case
	unsigned char x = 0;
	unsigned char y = 0;
	unsigned short j;
	unsigned char sizeX = getSizeX();
	for (j = 0; j < fc; j++) {
		x++;
		if (x > sizeX) {
			x = 0;
			y++;
		}
	}

	/*ham_DrawText(1, 13, "X:%d  Y:%d", x, y);

	wait();*/

	endVideoMode0();
	setVideoMode3();

	grid(seed, x+1, y+1);
	setTime(0, 0, 0);
	startTimer3();
	
	setPos(x, y);
	control(2);

	endVideoMode3();
	setVideoMode0();

	return succes;
}

unsigned char moveLineLoad(Sens sens, unsigned char *l) {
	switch (sens) {
		case HAUT :
			if (*l == 0) {
				*l = 1;
			} else {
				*l -= 1;
			}
			break;
		case BAS :
			if (*l == 1) {
				*l = 0;
			} else {
				*l += 1;
			}
			break;
		default :
			break;
	}

	ham_DrawText(1, 7, " ");
	ham_DrawText(27, 7, " ");
	ham_DrawText(1, 11, " ");
	ham_DrawText(27, 11, " ");

	switch (*l) {
		case 0 :
			ham_DrawText(1, 7, "-");
			ham_DrawText(27, 7, "-");
			break;
		case 1 :
			ham_DrawText(1, 11, "-");
			ham_DrawText(27, 11, "-");
			break;
	}
	return *l;
}
