#include "main.h"
#include "timers.h"

unsigned char gnewframe=0;

void vbl() {
	kramWorker();
	gnewframe=1;
}

void initMusic() {
	kragInit(KRAG_INIT_STEREO);
	kramQualityMode(KRAM_QM_HQ);

    ham_StartIntHandler(INT_TYPE_TIM1,&kradInterrupt);
    ham_StartIntHandler(INT_TYPE_VBL,&vbl);
}
