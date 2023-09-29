#include <limits.h>
#include "main.h"
#include "videoModes.h"
#include "timers.h"
#include "save.h"

unsigned int timerCount;

int main(void) {
	//Démarage
	ham_Init();
	
	//Video Mode 0
	setVideoMode0();

	//Timer
	timerCount = 0;
	startTimer0();

	initSave();
	endVideoMode0();

	unsigned char pseudo[8] = {39, 39, 39, 39, 39, 39, 39, 39};

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


				//while(1) {
				unsigned char newGame = menu();
				//}
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
				endVideoMode0();
				setVideoMode3();

				//Pour tester
				memcpy(pseudo, keyboard(pseudo), sizeof(pseudo));
				
				endVideoMode3();
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

//Timer nombre alétoire
void startTimer0() {
	ham_StartIntHandler(INT_TYPE_TIM0,               // The Interrupts ID you want to start.
					   (void *)&Timer0Function);     // The adress of a function that should be called when the interrupt is fired

	
	// Selects the speed of timer0
	M_TIM0CNT_SPEED_SELECT_SET(TIMER_FREQUENCY_SYSTEM)

	// Enable IRQ for timer0
	M_TIM0CNT_IRQ_ENABLE

	// Start timer0
	M_TIM0CNT_TIMER_START
}

void Timer0Function(void) {
   if(timerCount > UINT_MAX - 1) {
	   timerCount = 0;
   }
   timerCount++;
}

unsigned int getTimerCount() {
	return timerCount;
}
