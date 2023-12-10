#include "menu.h"
#include "main.h"
#include "timers.h"
#include "mines.h"

int timers;

unsigned char difficulty;
unsigned char mines;

unsigned char menu() {
	//Touches
	unsigned char upMenu = 0;
	unsigned char downMenu = 0;
	unsigned char leftMenu = 0;
	unsigned char rightMenu = 0;
	unsigned char LMenu = 0;
	unsigned char RMenu = 0;
	unsigned char aMenu = 0;
	unsigned char startMenu = 0;

	unsigned char choose = 1;
	unsigned char newGame = 0;
	unsigned char line = 0;

	ham_DrawText(11, 3, "DEMINEUR");
	ham_DrawText(3, 7,  "Difficulte      :");
	ham_DrawText(3, 11, "Nombre de mines :");
	ham_DrawText(12, 15, "JOUER");
	
	changeDifficulty(HAUT);
	changeMines(HAUT);
	moveLine(NUL, &line);

	while (choose) {
		if(F_CTRLINPUT_UP_PRESSED) {
		   upMenu = 1;
	   } else {
		   if (upMenu) {
			   line = moveLine(HAUT, &line);
			   upMenu = 0;
		   }
	   }

	   if(F_CTRLINPUT_DOWN_PRESSED) {
		   downMenu = 1;
	   } else {
		   if (downMenu) {
			   line = moveLine(BAS, &line);
			   downMenu = 0;
		   }
	   }

	   if(F_CTRLINPUT_LEFT_PRESSED) {
		   leftMenu = 1;
	   } else {
		   if (leftMenu) {
			   changeValue(GAUCHE, &line);
			   leftMenu = 0;
		   }
	   }

	   if(F_CTRLINPUT_RIGHT_PRESSED) {
		   rightMenu = 1;
	   } else {
		   if (rightMenu) {
			   changeValue(DROITE, &line);
			   rightMenu = 0;
		   }
	   }

	   if (F_CTRLINPUT_L_PRESSED) {
		   LMenu = 1;
		   //Quitter Menu
		   if (F_CTRLINPUT_R_PRESSED) {
			   choose = 0;
			   newGame = 0;
		   }
	   } else {
		   if (LMenu) {
			   changeValue(SUPER_GAUCHE, &line);
			   LMenu = 0;
		   }
	   }

	   if (F_CTRLINPUT_R_PRESSED) {
		   RMenu = 1;
	   } else {
		   if (RMenu) {
			   changeValue(SUPER_DROITE, &line);
			   RMenu = 0;
		   }
	   }

	   if(F_CTRLINPUT_A_PRESSED) {
		   aMenu = 1;
	   } else {
		   if (aMenu) {
			   if (line == 2) {
				   if (mines < (getSizeX() * getSizeX())) {
					   choose = 0;
					   newGame = 1;

					   
						ham_DrawText(1, 1, "                  ");

				   } else {
					   ham_DrawText(7, 18, "TROP DE MINES !"); //MARCHE PLUS
				   }
			   }
			   aMenu = 0;
		   }
	   }

	   if (F_CTRLINPUT_START_PRESSED) {
		   startMenu = 1;
	   } else {
		   if (startMenu) {
			   //Comme le bouton A
			   aMenu = 1;
			   startMenu = 0;
		   }
	   }
	}

	if (newGame) {
		unsigned int seed = getTimerCount();
		setSeed(seed);
		ham_DrawText(1, 1, "seed : %u", seed);

		setTime(0,0,0);
		startTimer3();
		while (getSeconds() < 1);//Afficher seed
		setTime(0,0,0);
	}

	return newGame;
}

unsigned char getSizeX() {
	switch (difficulty) {
		case 0:
			return 6;
			break;
		case 1:
			return 12;
			break;
		case 2:
			return 15;
			break;
		case 3:
			return 24;
			break;
		case 4:
			return 30;
			break;
	}
	return 0;
}

unsigned char getSizeY() {
	switch (difficulty) {
		case 0:
			return 4;
			break;
		case 1:
			return 8;
			break;
		case 2:
			return 10;
			break;
		case 3:
			return 16;
			break;
		case 4:
			return 20;
			break;
	}
	return 0;
}

unsigned char getMines() {
	return mines;
}

void setMines(unsigned char minesSave) {
	mines = minesSave;
}
unsigned char getDifficulty() {
	return difficulty;
}

void setDifficulty(unsigned char difSave) {
	difficulty = difSave;
}

unsigned char moveLine(Sens sens, unsigned char *l) {
	switch (sens) {
		case HAUT :
			if (*l == 0) {
				*l = 2;
			} else {
				*l -= 1;
			}
			break;
		case BAS :
			if (*l == 2) {
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
	ham_DrawText(10, 15, " ");
	ham_DrawText(18, 15, " ");

	switch (*l) {
		case 0 :
			ham_DrawText(1, 7, "-");
			ham_DrawText(27, 7, "-");
			break;
		case 1 :
			ham_DrawText(1, 11, "-");
			ham_DrawText(27, 11, "-");
			break;
		case 2 :
			ham_DrawText(10, 15, "-");
			ham_DrawText(18, 15, "-");
			break;
	}
	return *l;
}

void changeValue(Sens sens, unsigned char *l) {
	switch (*l) {
		case 0 :
			changeDifficulty(sens);
			break;
		case 1 :
			changeMines(sens);
			break;
	}
}

void changeDifficulty(Sens sens) {
	switch (sens) {
		case GAUCHE :
			if (difficulty == 0) {
				difficulty = 4;
			} else {
				difficulty -= 1;
			}
			break;
		case DROITE :
			if (difficulty == 4) {
				difficulty = 0;
			} else {
				difficulty += 1;
			}
			break;
		default :
			break;
	}
	
	ham_DrawText(21, 7, "     ");
	ham_DrawText(21, 7, "%ux%u", getSizeX(), getSizeY());
}

void changeMines(Sens sens) {
	switch (sens) {
		case GAUCHE :
			if (mines == 0) {
				mines = 99;
			} else {
				mines -= 1;
			}
			break;
		case DROITE :
			if (mines == 99) {
				mines = 1;
			} else {
				mines += 1;
			}
			break;
		case SUPER_GAUCHE :
			if (mines < 5) {
				mines = 99;
			} else {
				mines -= 5;
			}
			break;
		case SUPER_DROITE :
			if (mines > 94) {
				mines = 1;
			} else {
				mines += 5;
			}
			break;
		default :
			break;
	}

	if (mines < 10 ) {
		ham_DrawText(21, 11, " ", mines);
		ham_DrawText(22, 11, "%u", mines);
	} else {
		ham_DrawText(21, 11, "%u", mines);
	}
}
