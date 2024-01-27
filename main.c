#include "main.h"
#include "videoModes.h"
#include "timers.h"
#include "save.h"
#include "password.h"
#include "music.h"
#include "settings.h"

int main(void) {
	//Démarage
	ham_Init();
	
	//Video Mode 0
	setVideoMode0();

	//Timer
	setTimerCount(0);
	startTimer2();
	initTimer3();

	initSave();
	endVideoMode0();

	//Music
	initMusic();
	krapSetMusicVol(getVolume(1), 0);

	while(1) {
		//Video Mode 0
		setVideoMode0();

		/*
		 * 0	==>		Nouvelle partie
		 * 1	==>		Charger
		 * 2	==>		Scores
		*/
		
		//Musique de fond en boucle
		krapPlay(&mod_rois_mages, KRAP_MODE_LOOP, 0);

		unsigned char gamemode = selectionMenu();
		
		//Clic au choix d'un menu
		krapPlay(&mod_aqua, KRAP_MODE_JINGLE, 0);

		switch (gamemode) {
			case 0:
				endVideoMode0();
				setVideoMode0();

				unsigned char newGame = menu();
				saveMenu();

				if(newGame) {
					endVideoMode0();
					setVideoMode3();
					
					
					krapPlay(&mod_adagio, KRAP_MODE_LOOP, 0);
					control(0);
					krapStop();

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
				setVideoMode3();
				drawScoreBackground();
				while(scoreMenu() == 2);
				endVideoMode3();
				setVideoMode0();
				break;
			case 3:
				endVideoMode0();
				setVideoMode0();
				settingsMenu();
				break;
		}
	}
	return 0;
}

//Modes vidéos
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
