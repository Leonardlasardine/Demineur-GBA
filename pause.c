#include "pause.h"

unsigned char pauseGame() {

	//Sauvegarder grille écran
	//Changer mode vidéo
	//Ecrire le menu pause

	save_screen();

	return 1;
}

void save_screen() {
	
}


//TIMER
/*

	ham_StartIntHandler(INT_TYPE_TIM3,               // The Interrupts ID you want to start.
					   (void *)&Timer3Function);   // The adress of a function that should be called when the interrupt is fired

   
   // Selects the speed of timer3
   M_TIM3CNT_SPEED_SELECT_SET(10)

   // Enable IRQ for timer3
   M_TIM3CNT_IRQ_ENABLE

   // Start timer3
   M_TIM3CNT_TIMER_START

   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(6, 2, "ham timer example");
   


void Timer3Function(void) {
   static u8 s_H=0, s_M=0, s_S=0;

   if(++s_S > 59) {
	  if(++s_M > 59)  {
		 if(++s_H > 11)  {
			s_H=0;
		 }
		 s_M=0;
	  }
	  s_S = 0;
   }

   // Draws Text. Be aware that this function is SLOW.
   // It should only be used for debug purposes.
   ham_DrawText(6, 6, "HH:MM:SS %.2d:%.2d:%.2d ", s_H, s_M, s_S);
}

*/
