#include <mygba.h>
#include "main.h"

int main(void) {
	ham_Init();

	int showMenu = 1;

	//Démarage
	REG_TM0CNT = TIMER_FREQUENCY_SYSTEM | TIMER_ENABLE;


	while(1) {
		if(showMenu) {
			ham_SetBgMode(0);
			ham_InitText(0);

			menu();
			
			ham_DeInitText();
			ham_ResetAll();

			showMenu = 0;
		} else {
			//Video Mode 3
			REG_DISPCNT = (MODE_3 | BG2_ENABLE);

			control();

			REG_DISPCNT = 0;
			ham_ResetAll();

			showMenu = 1;
		}
   }

   return 0;
}
