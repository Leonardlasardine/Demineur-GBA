#include "main.h"
#include "videoModes.h"
#include "timers.h"
#include "save.h"
#include "password.h"

int main(void) {
	//Démarage
	ham_Init();
	
	//Video Mode 0
	setVideoMode0();

	//Timer
	setTimerCount(0);
	startTimer0();
	initTimer3();

	initSave();
	endVideoMode0();

	while(1) {
		//Video Mode 0
		setVideoMode0();

		/*
		 * 0	==>		Nouvelle partie
		 * 1	==>		Charger
		 * 2	==>		Scores
		*/
		unsigned char gamemode = selectionMenu();

		switch (gamemode) {
			case 0:
				endVideoMode0();
				setVideoMode0();

				unsigned char newGame = menu();
				saveMenu();

				if(newGame) {
					endVideoMode0();
					setVideoMode3();
					
					control(0);

					endVideoMode3();
				}
				//Sinon retour menu principal
				break;
			case 1:
				endVideoMode0();
				setVideoMode0();
				loadMenu();
				break;
			case 2:
				endVideoMode0();
				break;
		}
	}
   return 0;
}

//Videos modes
void setVideoMode0() {
	ham_SetBgMode(0);
	ham_InitText(0);
}

void endVideoMode0() {
	ham_DeInitText();
	ham_ResetBg();
}

void setVideoMode3() {
	REG_DISPCNT = (MODE_3 | BG2_ENABLE);
}

void endVideoMode3() {
	REG_DISPCNT = 0;
	ham_ResetBg();
}

//Attends qu'une touche soit relachée
//AFAIRE toutes les touches
void wait() {
	unsigned char spectate = 1;
	unsigned char keyPressed = 0;
	while (spectate) {
		if(F_CTRLINPUT_A_PRESSED) {
			keyPressed = 1;
		} else {
			if (keyPressed) {
				keyPressed = 0;
				spectate = 0;
			}
		}
	}
}
