#include "menu.h"

int timers;

unsigned char Xsize = 10;
unsigned char Ysize = 10;
unsigned char mines = 8;

int menu() {
	//Touches
	unsigned char upMenu = 0;
	unsigned char downMenu = 0;
	unsigned char leftMenu = 0;
	unsigned char rightMenu = 0;
	unsigned char LMenu = 0;
	unsigned char RMenu = 0;
	unsigned char aMenu = 0;

	int choose = 1;
	unsigned char line = 0;

	ham_DrawText(11, 3, "DEMINEUR");
	ham_DrawText(12, 15, "JOUER");

	ham_DrawText(3, 7, "Nombre de lignes  :");
	ham_DrawText(3, 9, "Nombre de colones :");
	ham_DrawText(3, 11, "Nombre de mines   :");
	
	changeX(HAUT);
	changeY(HAUT);
	changeMines(HAUT);

	ham_DrawText(1, 7, "-");
	ham_DrawText(26, 7, "-");

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
			   if (line == 3) {
				   if (mines < (Xsize * Ysize)) {
					   choose = 0;
				   } else {
					   ham_DrawText(7, 18, "TROP DE MINES !");
				   }
			   }
			   aMenu = 0;
		   }
	   }
	}


	timers = REG_TM0D / (65536 / 1000);
	grid(timers);

	return 0;
}

unsigned char getSizeX(){
	return Xsize;
}

unsigned char getSizeY(){
	return Ysize;
}

unsigned char getMines(){
	return mines;
}

unsigned char moveLine(Sens sens, unsigned char *l) {
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

	ham_DrawText(1, 7, " ");
	ham_DrawText(26, 7, " ");
	ham_DrawText(1, 9, " ");
	ham_DrawText(26, 9, " ");
	ham_DrawText(1, 11, " ");
	ham_DrawText(26, 11, " ");
	ham_DrawText(10, 15, " ");
	ham_DrawText(18, 15, " ");

	switch (*l) {
		case 0 :
			ham_DrawText(1, 7, "-");
			ham_DrawText(26, 7, "-");
			break;
		case 1 :
			ham_DrawText(1, 9, "-");
			ham_DrawText(26, 9, "-");
			break;
		case 2 :
			ham_DrawText(1, 11, "-");
			ham_DrawText(26, 11, "-");
			break;
		case 3 :
			ham_DrawText(10, 15, "-");
			ham_DrawText(18, 15, "-");
			break;
	}
	return *l;
}

void changeValue(Sens sens, unsigned char *l) {
	switch (*l) {
		case 0 :
			changeX(sens);
			break;
		case 1 :
			changeY(sens);
			break;
		case 2 :
			changeMines(sens);
			break;
	}
}

void changeX(Sens sens) { //CHANGER TAILLE MAX
	switch (sens) {
		case GAUCHE :
			if (Xsize == 1) {
				Xsize = 30;
			} else {
				Xsize -= 1;
			}
			break;
		case DROITE :
			if (Xsize == 30) {
				Xsize = 1;
			} else {
				Xsize += 1;
			}
			break;
		case SUPER_GAUCHE :
			if (Xsize < 6) {
				Xsize = 30;
			} else {
				Xsize -= 5;
			}
			break;
		case SUPER_DROITE :
			if (Xsize > 25) {
				Xsize = 1;
			} else {
				Xsize += 5;
			}
			break;
		default :
			break;
	}

	if (Xsize < 10 ) {
		ham_DrawText(23, 7, " ", Xsize);
		ham_DrawText(24, 7, "%u", Xsize);
	} else {
		ham_DrawText(23, 7, "%u", Xsize);
	}
}

void changeY(Sens sens) {
	switch (sens) {
		case GAUCHE :
			if (Ysize == 1) {
				Ysize = 20;
			} else {
				Ysize -= 1;
			}
			break;
		case DROITE :
			if (Ysize == 20) {
				Ysize = 1;
			} else {
				Ysize += 1;
			}
			break;
		case SUPER_GAUCHE :
			if (Ysize < 6) {
				Ysize = 20;
			} else {
				Ysize -= 5;
			}
			break;
		case SUPER_DROITE :
			if (Ysize > 15) {
				Ysize = 1;
			} else {
				Ysize += 5;
			}
			break;
		default :
			break;
	}

	if (Ysize < 10 ) {
		ham_DrawText(23, 9, " ", Ysize);
		ham_DrawText(24, 9, "%u", Ysize);
	} else {
		ham_DrawText(23, 9, "%u", Ysize);
	}
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
		ham_DrawText(23, 11, " ", mines);
		ham_DrawText(24, 11, "%u", mines);
	} else {
		ham_DrawText(23, 11, "%u", mines);
	}
}
