#include <limits.h>
#include "main.h"
#include "timers.h"

unsigned int timerCount;
unsigned int seed;
unsigned short delayCount;

//Timer nombre alétoire
void startTimer2() {
	ham_StartIntHandler(INT_TYPE_TIM2,               // The Interrupts ID you want to start.
					   (void *)&Timer2Function);     // The adress of a function that should be called when the interrupt is fired

	
	// Selects the speed of timer2
	M_TIM2CNT_SPEED_SELECT_SET(TIMER_FREQUENCY_SYSTEM)

	// Enable IRQ for timer2
	M_TIM2CNT_IRQ_ENABLE

	// Start timer2
	M_TIM2CNT_TIMER_START
}

//5 352 008 possibilitées pour que le mot de passe fasse 8 caractères
//Pourrait utiliser UINT_MAX : 4 294 967 295 mais 11 caractères
void Timer2Function(void) {
   if(timerCount > 5352007) {
	   timerCount = 0;
   }
   timerCount += 1;
}

void stopTimer2() {
	M_TIM2CNT_TIMER_STOP
}

void restartTimer2() {
	M_TIM2CNT_TIMER_START
}

unsigned int getTimerCount() {
	return timerCount;
}

void setTimerCount(unsigned int v) {
	timerCount = v;
}

unsigned int getSeed() {
	return seed;
}

void setSeed(unsigned int newSeed) {
	seed = newSeed;
}


//Pour des délais courts
void waitTime(unsigned short time) {
	unsigned int delay = getTimerCount();
	setTimerCount(0);
	while (getTimerCount() < time);
	setTimerCount(delay);
}

unsigned short getDelay() {
	return delayCount;
}
