#include <mygba.h>
#include "main.h"
#include "videoModes.h"
#include "timers.h"
#include "save.h"

int main(void) {
	ham_Init();
	
	//Video Mode 0
	setVideoMode0();

	//Démarage
	REG_TM0CNT = TIMER_FREQUENCY_SYSTEM | TIMER_ENABLE;

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

					control(1);

					endVideoMode3();
				}
				//Sinon retour menu principal
				break;
			case 1:
				
				break;
			case 2:

				break;
		}
	}
   return 0;
}

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
