#include "pause.h"
#include "mines.h"
#include "save.h"
#include "password.h"
#include "menu.h"
#include "timers.h"
#include "videoModes.h"

unsigned char pauseMenu;
unsigned char quitPlaying;
unsigned char line;

unsigned char s_H=0, s_M=0, s_S=0;

unsigned char pauseGame() {
	endVideoMode3();
	setVideoMode0();

	stopTimer3();
	
	pauseMenu = 1;
	quitPlaying = 1;
	line = 0;

	unsigned char upPause = 0;
	unsigned char downPause = 0;
	unsigned char aPause = 0;
	unsigned char bPause = 0;
	unsigned char startPause = 0;

	writePauseText();
	Timer3Function();

	while (pauseMenu) {
		if(F_CTRLINPUT_UP_PRESSED) {
		   upPause = 1;
	   } else {
		   if (upPause) {
			   line = moveLinePause(HAUT, &line);
			   upPause = 0;
		   }
	   }

	   if(F_CTRLINPUT_DOWN_PRESSED) {
		   downPause = 1;
	   } else {
		   if (downPause) {
			   line = moveLinePause(BAS, &line);
			   downPause = 0;
		   }
	   }

		if (F_CTRLINPUT_A_PRESSED) {
		   aPause = 1;
	   } else {
		   if (aPause) {
			   aPressedAction(&line);
			   aPause = 0;
		   }
	   }

		if (F_CTRLINPUT_B_PRESSED) {
		   bPause = 1;
	   } else {
		   if (bPause) {
			   //Continuer
			   line = 0;
			   aPressedAction(&line);
			   bPause = 0;
		   }
	   }

		if (F_CTRLINPUT_START_PRESSED) {
		   startPause = 1;
		} else {
		   if (startPause) {
			   line = 0;
			   aPressedAction(&line);
			   startPause = 0;
			}
		}
	}

	return quitPlaying;
}

void writePauseText() {
	ham_DrawText(13, 2, "PAUSE");
	ham_DrawText(5, 5,  "Temps     :");
	if (getMinesLeft() != 100) {
		ham_DrawText(2, 7, "Drapeaux restants : %d / %u", getFlagsLeft(), getMines());
	} else {
		ham_DrawText(9, 7, "Partie perdue");
	}
	//ham_DrawText(4, 8, "Mines restantes : %u / %u", getMinesLeft(), getMines());
	ham_DrawText(10, 11, " CONTINUER");
	ham_DrawText(10, 13, "SAUVEGARDER");
	ham_DrawText(10, 15, "  QUITTER");
	ham_DrawText(10, 17, "MOT DE PASSE");
	
	moveLinePause(DROITE, &line);
}

unsigned char moveLinePause(Sens sens, unsigned char *l) {
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

	ham_DrawText(8, 11, " ");
	ham_DrawText(22, 11, " ");
	ham_DrawText(8, 13, " ");
	ham_DrawText(22, 13, " ");
	ham_DrawText(8, 15, " ");
	ham_DrawText(22, 15, " ");
	ham_DrawText(8, 17, " ");
	ham_DrawText(22, 17, " ");

	switch (*l) {
		case 0 :
			ham_DrawText(8, 11, "-");
			ham_DrawText(22, 11, "-");
			break;
		case 1 :
			ham_DrawText(8, 13, "-");
			ham_DrawText(22, 13, "-");
			break;
		case 2 :
			ham_DrawText(8, 15, "-");
			ham_DrawText(22, 15, "-");
			break;
		case 3 :
			ham_DrawText(8, 17, "-");
			ham_DrawText(22, 17, "-");
			break;
	}
	return *l;
}

void aPressedAction(unsigned char *l) {
	switch (*l) {
		case 0 :
			//Continuer
			endVideoMode0();
			setVideoMode3();

			drawSave();
			//drawCursor
			restartTimer3();

			quitPlaying = 0;
			pauseMenu = 0;
			break;
		case 1 :
			//Sauvegarder
			save();
			ham_DrawText(6, 14, "PARTIE SAUVEGARDEE");
			//Re afficher le temps
			Timer3Function();
			break;
		case 2 :
			//Quitter
			s_H=0;
			s_M=0;
			s_S=0;
			quitPlaying = 1;
			pauseMenu = 0;
			break;
		case 3 :
			//AFFICHER MOT DE PASSE
			//Ou alors en quittant
			endVideoMode0();
			setVideoMode3();

			writePassword();

			unsigned char aPassword = 0;
			unsigned char startPassword = 0;
			unsigned char showPassword = 1;

			while (showPassword) {
				if (F_CTRLINPUT_A_PRESSED) {
					aPassword = 1;
				} else {
					if (aPassword) {
						aPassword = 0;
						showPassword = 0;
					}
				}
				if (F_CTRLINPUT_START_PRESSED) {
				   startPassword = 1;
				} else {
					if (startPassword) {
						//Comme le bouton A
						aPassword = 1;
						startPassword = 0;
					}
				}
			}
			endVideoMode3();
			setVideoMode0();
			writePauseText();
			//Re afficher le temps
			Timer3Function();
			break;
	}
}

void startTimer3() {
	ham_StartIntHandler(INT_TYPE_TIM3,               // The Interrupts ID you want to start.
					   (void *)&Timer3Function);     // The adress of a function that should be called when the interrupt is fired

	
	// Selects the speed of timer3
	M_TIM3CNT_SPEED_SELECT_SET(10)

	// Enable IRQ for timer3
	M_TIM3CNT_IRQ_ENABLE

	// Start timer3
	M_TIM3CNT_TIMER_START
}

void Timer3Function(void) {
   if(++s_S > 59) {
	  if(++s_M > 59)  {
		 if(++s_H > 11)  {
			s_H=0;
		 }
		 s_M=0;
	  }
	  s_S = 0;
   }
   if (pauseMenu && quitPlaying) {
	   ham_DrawText(17, 5, "%.2d:%.2d:%.2d ", s_H, s_M, s_S);
   }
}

void stopTimer3() {
	M_TIM3CNT_TIMER_STOP
}

void restartTimer3() {
	M_TIM3CNT_TIMER_START
}

unsigned char getHours() {
	return s_H;
}

unsigned char getMinutes() {
	return s_M;
}

unsigned char getSeconds() {
	return s_S;
}

void setTime(unsigned char hours, unsigned char minutes, unsigned char seconds) {
	s_H = hours;
	s_M = minutes;
	s_S = seconds;
}
