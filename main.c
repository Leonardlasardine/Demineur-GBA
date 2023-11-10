#include <limits.h>
#include "main.h"
#include "videoModes.h"
#include "timers.h"
#include "save.h"
#include "password.h"

unsigned int timerCount;
unsigned int seed;

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

//5 352 008 possibilitées pour que le mot de passe fasse 8 caractères
//Pourrait utiliser UINT_MAX : 4 294 967 295 mais 11 caractères
void Timer0Function(void) {
   if(timerCount > 5352007) {
	   timerCount = 0;
   }
   timerCount += 1;
}

unsigned int getTimerCount() {
	return timerCount;
}

unsigned int getSeed() {
	return seed;
}

void setSeed(unsigned int newSeed) {
	seed = newSeed;
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
