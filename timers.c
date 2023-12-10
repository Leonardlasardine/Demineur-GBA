#include <limits.h>
#include "main.h"
#include "timers.h"

unsigned int timerCount;
unsigned int seed;
unsigned short delayCount;

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

void stopTimer0() {
	M_TIM0CNT_TIMER_STOP
}

void restartTimer0() {
	M_TIM0CNT_TIMER_START
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
