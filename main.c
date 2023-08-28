#include <mygba.h>
#include "main.h"
#include "videoModes.h"
#include "timers.h"

int main(void) {
	ham_Init();

	unsigned char showMenu = 1;

	//Démarage
	REG_TM0CNT = TIMER_FREQUENCY_SYSTEM | TIMER_ENABLE;

	while(1) {
		if(showMenu) {
			//Video Mode 0
			setVideoMode0();

			menu();
			
			endVideoMode0();

			showMenu = 0;
		} else {
			//Video Mode 3
			setVideoMode3();

			control();

			showMenu = 1;
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
